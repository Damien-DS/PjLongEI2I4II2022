
/* Standard includes. */
#include <stdlib.h>
// pour le lpc1769
#include "FreeRTOS.h"
#include "task.h"
#include "myTasks.h"

/* Priorities for the demo application tasks. */
#define mainLED_TASK_PRIORITY		( tskIDLE_PRIORITY + 2 )


 // Configuration minimal du processeur pour avoir les 8 Leds du Port2 disponible
 
static void prvSetupHardware( void );
static void init_gpio(void);

/*-----------------------------------------------------------*/
void gestion_abort(void)
{


}


/*
 * Application entry point:
 * Starts all the other tasks, then starts the scheduler. 
 */
int main( void )
{
 // Configuration minimal du processeur pour avoir les 8 Leds du Port2 disponible
	
	prvSetupHardware();
	//init des leds
	init_gpio();
	/* initialisation des taches */
	vInit_myTasks( 2 );
	
	// toutes les taches ont été démarrées - Demarrer le scheduler.
  // Les taches tournent en USER/SYSTEM mode et le Scheduler tourne en Superviseur mode
	// Le processeur doit être en SUPERVISEUR quand vTaskStartScheduler est appelé
  // mais user privileged suffit en fait...	
	
	vTaskStartScheduler();

	/* Should never reach here!  If you do then there was not enough heap
	available for the idle task to be created. */
    LPC_GPIO3->FIOCLR = 1<<26;
		LPC_GPIO0->FIOCLR = 1<<22;
    LPC_GPIO3->FIOCLR = 1<<25;
	for( ;; )
	{ 
		LPC_GPIO3->FIOSET = 1<<26;
		LPC_GPIO0->FIOCLR = 1<<22;
    LPC_GPIO3->FIOSET = 1<<25;
	}
}

static void prvSetupHardware( void )
{
	//   SCS|=1;  // port 0 et Port 1 en FastIO
	LPC_SC->PCONP     |= (1 << 15);            /* power on sur GPIO & IOCON , deja sous tension par défaut*/
  LPC_GPIO3->FIODIR |= 0x03<<25;   //P3.25 et P3.26 en sortie
	LPC_GPIO0->FIODIR |= 0x01<<22;   //P0.22 en sortie
}
static void init_gpio(void)
{ 
	LPC_SC->PCONP     |= (1 << 15);  /* power on sur GPIO & IOCON , deja sous tension par défaut*/ 
  LPC_GPIO3->FIODIR |= 0x03<<25;   //P3.25 et P3.26 en sortie
  LPC_GPIO0->FIODIR |= 0x01<<22;   //P0.22 en sortie
    
  LPC_GPIO2->FIODIR |= 0x1F8; //P2.4 à P2.8 en sortie     
  LPC_GPIO0->FIODIR |= 0x01 <<11; //P0.11 en sortie (led)
	
} 
