#include <mosquitto.h>

#define ID "ID_Analyse"

#include "Comm_Config.h"


void message_callback(struct mosquitto *mosq, void *obj, const struct mosquitto_message *message){
	bool match = false;
	mosquitto_topic_matches_sub("/Sensor/Raw_Data", message->topic, &match);
	if (match) {
    json j = json::parse(message->data);
    cout << "TimeStamp:" << j["TimeStamp"].get<uint>();
    cout << "DataLength:" << j["DataLength"].get<uint>();
    //j["Data"]
		return;
	}

	match = false;
	mosquitto_topic_matches_sub("/Analyse/Config", message->topic, &match);
	if (match) {
		if( message->payloadlen != sizeof(Sensor_Config)  ){
			std::cout << "Diskrepanz zwischen payloadlen{" << message->payloadlen << "} und sizeof(Analyse_Config){(}" << sizeof(Analyse_Config) << "}" << std::endl;
		}else{
			memcpy ( &analyse_config, message->payload, Analyse_Config );
		}
		return;
	}
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

	// Subscribe to "/Sensor/Raw_Data"
	int rc = mosquitto_subscribe( 	mosq,
									NULL,
									"/Sensor/Raw_Data",
									qos	);
	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_subscribe erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_subscribe nicht erfolgreich" << std::endl;
		return false;
	}

	// Subscribe to "/Analyse/Config"
	rc = mosquitto_subscribe( 	mosq,
									NULL,
									"/Analyse/Config",
									qos	);
	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_subscribe erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_subscribe nicht erfolgreich" << std::endl;
		return false;
	}

	


	// Callback setzen
	mosquitto_message_callback_set(mosq, message_callback);

	// Mosquitto-Thread starten	
	rc = mosquitto_loop_start(mosq);
	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_loop_start erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_loop_start nicht erfolgreich" << std::endl;
		// return false;
	}
	
		
	////////////////////////////////////////////////////////////////////////////////////////
	////////////////////////////  MQTT Init abgeschlossen  /////////////////////////////////
	////////////////////////////////////////////////////////////////////////////////////////

	while(true){
	
		if( raw_data_length == 0){
			usleep(1000);		// 1 Millisekunde schlafen
			continue;
		}

}
