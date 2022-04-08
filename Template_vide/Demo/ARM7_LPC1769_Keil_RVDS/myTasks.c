#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* le fichier .h du TP  */
#include "myTasks.h"

// #define ledSTACK_SIZE		128


/* déclaration des diverses taches avec la fonction prototype */
//static portTASK_FUNCTION_PROTO( vLed1Task, pvParameters );//exemple de déclaration
/*-------------------variables globales propres aux taches------------*/
#define ledSTACK_SIZE 128

unsigned int delay = 500;

void vInit_myTasks(UBaseType_t uxPriority ){
	//xTaskCreate( Tache_Encod, "ENCOD", ledSTACK_SIZE, &delay, uxPriority, NULL );
}
