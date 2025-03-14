
#include "meUSART1.h"

#define baudrate 115200

extern char	rx_tab[BUFFER_SIZE];  // Pour remplir le buffer de réception des données (sans interruption) 
uint8_t indice = 0;               // Indice du buffer de réception des données (sans interruption) 

uint32_t bday = 1000;  // Voir me_Delay.c
delay_t delay_Rx;  // Voir me_Delay.c

bool is_Transmiting = 0;


void UART_Init(){

    RCC->AHBENR |= RCC_AHBENR_GPIOAEN;

    GPIOA->MODER &= ~(GPIO_MODER_MODER9 | GPIO_MODER_MODER10);
	GPIOA->MODER |= (GPIO_MODER_MODER9_1) | (GPIO_MODER_MODER10_1);

    GPIOA->AFR[1] &= ~(0x00000FF0);
	GPIOA->AFR[1] |=  0x00000110;

    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

    RCC->CFGR3 &= ~(RCC_CFGR3_USART1SW);

    USART1->CR1 |= USART_CR1_OVER8;
    USART1->BRR = SystemCoreClock/baudrate * 2;

    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;

    USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_TXEIE;

    USART1->CR1 |= USART_CR1_UE;

}

void USART1_IRQHandler()
{

    if (USART1->ISR & USART_ISR_RXNE){          // Test de l'origine de l'interruption

        meFiFo_Write(&fifo_Rx,USART1->RDR);
        //USART1_putc(USART1->RDR);        
	}

    if (USART1->ISR & USART_ISR_TXE) {            // Vérifier si la transmission est prête (TXE)
        if ( !(meFiFo_Empty(&fifo_Tx) == 1) ) {      // Lire depuis fifo_Tx
            USART1->TDR = meFiFo_Read(&fifo_Tx);        // Envoyer le caractère suivant
        }else {
            is_Transmiting = 0;
            USART1->CR1 &= ~USART_CR1_TXEIE; 
        }

    }
    
}


void NVIC_Initialisation(){

	NVIC_SetPriority(USART1_IRQn, 1);
	NVIC_EnableIRQ(USART1_IRQn);
}

void SendString(const char * str){
    while (*str){
        USART1_putc(*(str++));
    }
}

void USART1_putc(const char c){

    USART1->CR1 &= ~USART_CR1_TXEIE; 

    if (is_Transmiting){
        meFiFo_Write(&fifo_Tx, c);
    }else{
        USART1->TDR = c;
        is_Transmiting = 1;
    }    
    USART1->CR1 |= USART_CR1_TXEIE; 
}

bool USART1_getc(char * pc){

    if ( !(meFiFo_Empty(&fifo_Rx)) ){
        *pc = meFiFo_Read(&fifo_Rx);
        return true;
    }else {
        return false;
    }
}


void SendNb(uint16_t number){
    uint8_t ind = 0;
    char buffer[6];

    if (number == 0) {  
        USART1_putc('0');
        return;
    }

    while (number > 0) {
        buffer[ind++] = (number % 10) + '0';  // Extraire le dernier chiffre
        number /= 10;
    }

    while (ind > 0) {

        USART1_putc(buffer[--ind]);

    }
}

// void ReceiveString(){
//     if ( USART1->ISR & USART_ISR_RXNE ){
//         if (indice < sizeof(rx_tab)){
//             rx_tab[indice++] = USART1->RDR;
//         }
//         meDelayInit(&delay,bday);
//     }
    
// }

void ReceiveString(){
    if ( USART1->ISR & USART_ISR_RXNE ){
        if (indice < sizeof(rx_tab)){
            rx_tab[indice++] = USART1->RDR;
        }
        meDelayInit(&delay_Rx,bday);
    }
    
}

