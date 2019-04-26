#ifndef COMM_CONFIG_H_
#define COMM_CONFIG_H_

#include <iostream>
#include <mosquitto.h>
#include <string>

using namespace std;

//#define host "127.0.0.1"
char* host = "localhost";
//#define port 1883
#define qos 0
#define retain true

static struct mosquitto *mosq;

static bool connect_To_Broker(){
	int ret = mosquitto_lib_init( ); 
	if( ret == MOSQ_ERR_SUCCESS )
		std::cout << "Moqsuitto Lib Init erfolgreich" << std::endl;
	else{
		std::cout << "Mosquitto Lib Init nicht erfolgreich" << std::endl;
		return false;
	}

	mosq = mosquitto_new( 
		ID,
  		true,
  		0
  	);	// void *userdat
	if( mosq != NULL )
		std::cout << "mosquitto_new erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_new nicht erfolgreich" << std::endl;
		return false;
	}

  	int rc = 0;

	rc = mosquitto_connect_async( 
		mosq,
  		host,
  		1883,
  		60
  	);

	if( rc == MOSQ_ERR_SUCCESS )
		std::cout << "mosquitto_connect erfolgreich" << std::endl;
	else{
		std::cout << "mosquitto_connect nicht erfolgreich" << std::endl;
		return false;
	}
	
  	return true;
}

static void disconnect_From_Broker(){
	mosquitto_disconnect(mosq);
	mosquitto_loop_stop(mosq, true);
	mosquitto_destroy(mosq);
	mosquitto_lib_cleanup();
}


// mosquitto_loop_start(mosq);

// libmosq_EXPORT void mosquitto_message_callback_set(
//   	struct 	mosquitto 	*	mosq,
//   		void 		(*on_message)(struct mosquitto *, void *, const struct mosquitto_message *))

// libmosq_EXPORT int mosquitto_subscribe(	struct 	mosquitto 	*	mosq,
//		int 	*	mid,
//	const 	char 	*	sub,
//		int 		qos	)

#endif
