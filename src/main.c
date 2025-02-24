#include "stm32f0xx.h"
#include "system.h"
#include "io.h"

int main(void)
{
	System_Init();
	
	MEPIN_SET( PIN_LED0 );
	
    while(1)
    {
		if( ( meTime & ((1<<10)-1) ) == 0 ){
			MEPIN_SWAP( PIN_LED0 );
		}
    }
}


void HardFault_Handler(){
	__ASM volatile( "BKPT #01	\n"	);
}
