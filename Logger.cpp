#include <mosquitto.h>
 
#include <unistd.h>

#define ID "ID_Analyse"

#include "Comm_Config.h"

#include <iostream>

void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message){
	bool match = false;
	//mosquitto_topic_matches_sub("/Sensor/Raw_Data", message->topic, &match);
	//if (match) {
	// TODO:
	//	return;
	//}
	std::cout << "Nachricht empfangen." << std::endl;
}


int main(){

	// Connect to Broker
	if (connect_To_Broker())
		std::cout << "Verbindung zu Broker hergestellt" << std::endl;
	else
	{
		std::cout << "Verbindung zu Broker fehlgeschlagen" << std::endl;
		return -1;
	}

	std::cout << mosquitto_username_pw_set( mosq, "Marvin", "Standard" ) << std::endl;

	// Subscribe to "/Sensor/Raw_Data"
	int rc = mosquitto_subscribe( 	mosq,
									NULL,
									"Test",
									qos	);
	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_subscribe erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_subscribe nicht erfolgreich" << std::endl;
		return -1;
	}


	// Callback setzen
	mosquitto_message_callback_set(mosq, message_callback);

	// Mosquitto-Thread starten	
	rc = mosquitto_loop_start(mosq);
	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_loop_start erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_loop_start nicht erfolgreich" << std::endl;
		return -1;
	}


	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////  MQTT Init abgeschlossen  /////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	while(true){
		usleep(1000000);		// 1 Millisekunde schlafen
		std::cout << mosquitto_publish( mosq, NULL, "Test", 6, "Test", 2, true ) << std::endl;
	}

}
