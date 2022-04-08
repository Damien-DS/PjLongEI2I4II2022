#include <stdlib.h>

/* Scheduler include files. */
#include "FreeRTOS.h"
#include "task.h"

/* le fichier .h du TP  */
#include "myTasks.h"

// #define ledSTACK_SIZE		128


/* déclaration des diverses taches avec la fonction prototype */
//static portTASK_FUNCTION_PROTO( vLed1Task, pvParameters );//exemple de déclaration
static portTASK_FUNCTION_PROTO( Tache_Encod, pvParameters );
static portTASK_FUNCTION_PROTO( idle, pvParameters );
/*-------------------variables globales propres aux taches------------*/
#define ledSTACK_SIZE 128
unsigned int echantillonage_codeur = 10;
void vInit_myTasks(UBaseType_t uxPriority ){
	xTaskCreate( idle, "idle", ledSTACK_SIZE, NULL , 0 , NULL );
	xTaskCreate( Tache_Encod, "ENCOD", ledSTACK_SIZE, NULL, uxPriority, NULL );
}

void idle(void* pvParameters) {
	while(1) {
		
	}
}

void Tache_Encod( void* pvParameters) {
	uint16_t val_encod_AB = 0,val_lecture = 0;
	uint8_t ancienA = 0, ancienB =0, nvA = 0, nvB =0;
	uint8_t echantillonage_codeur = 10;
	uint32_t cmpt_int;
	while(1){
		// val encode = [ancien A][nvA][ancB][nvB]
		ancienA = nvA; //ancien A = nv A
		ancienB = nvB;
		vTaskDelay(echantillonage_codeur);
		val_lecture = (LPC_GPIO2->FIOPIN1 &(0x3 << 2)) >> 2; // Lecture de nv 
		nvA = (val_lecture & 0x2) >> 1;
		nvB = val_lecture & 1;
		val_encod_AB = (ancienA << 3) | (nvA << 2) | (ancienB << 1) | nvB ;
		if (val_encod_AB == 11) // 1011 
		{
			cmpt_int++;
		}
		else if(val_encod_AB == 14) //1110
		{
			cmpt_int--;
		}
		//Traiter le compteur
		LPC_DAC->DACR = cmpt_int > 1023 ? 0 << 6 : cmpt_int << 6; 
	}	
}
