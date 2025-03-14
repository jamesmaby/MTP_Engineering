#include "stm32f0xx.h"
#include "system.h"
#include "io.h"

#include "main.h"
#include "meDelay.h"
#include "MeFiFo.h"
#include "meUSART1.h"
#include "test_printf.h"
#include "meFileDescriptor.h"
#include "meUSARTFD.h"
#include "meFIFOFD.h"
#include "meConsole.h"



uint8_t	rx_byte;
char	rx_tab[BUFFER_SIZE];

extern uint8_t indice;

uint32_t birthday = 1000;
delay_t delay_main;

char receive_fifo;

DEFINE_FIFO(fifo_Rx,FIFO_RX_SIZE) 
DEFINE_FIFO(fifo_Tx,FIFO_TX_SIZE) 


int main(void)
{
	System_Init();
	
	UART_Init();
	NVIC_Initialisation();
	
	meDelayInit(&delay_main,birthday);
		
	MEPIN_SET( PIN_LED0 );

	me_sd_t me_sd;
	ctx_cons_t ctx_cons;

	static delay_t console_delay;
	ctx_cons.delay_cons = &console_delay;

	fd_FIFO_USART1_Init(&me_sd,&fifo_Rx,&fifo_Tx);
	console_Init(&ctx_cons,&me_sd);


    while(1)
    {
		char buffer[64];
		strcpy(buffer, "bonjour");  // Initialise le buffer proprement
	
		console_polling(&ctx_cons);

		if( meDelay(&delay_main) == 1 ){
			MEPIN_SWAP( PIN_LED0 );

			/* fonctions de test_printf.c */
			// sprintf(buffer,size,"Valeur : %d, hex : %x, string : %-10s\n",854, 0x2A3, "jimibi");
			// SendString(buffer);
			
			//USART1_printf("Valeur: %d, Hex: %x, String: %-10s\n", 4567, 0x15F2, "james");

			/* fonctions de meFileDescriptor.c */

			// Test du me_sd_Printf()
			//me_sd_Printf(&me_sd,"name : %s %20s : %-10s \r\n","je suis","PAS TRES TRES","CONTENT");
			// me_sd_Printf(&me_sd,"String: %x \r\n",me_sd_Read(&me_sd,buffer,1));

			// Test du me_sd_Print()
			//SendNb(me_sd_Print( &me_sd, buffer));

			// Test du me_sd_Read()
			// 	int bytesRead = me_sd_Read(&me_sd, buffer, 1);
			// 	if (bytesRead > 0) {
			// 		buffer[bytesRead] = '\0';  
			// 		SendNb(bytesRead);
			// 		SendString(buffer);
			// 	}

			// Test du me_sd_Write()
			//SendNb(me_sd_Write(&me_sd,buffer,9));		

			// SendString("\r\n");
			meDelayInit(&delay_main,birthday);
		}
    }
}

void HardFault_Handler(){
	__ASM volatile( "BKPT #01	\n"	);
}
