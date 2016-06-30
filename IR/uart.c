#include <avr/io.h>
#include "uart.h"
#include "bits_macros.h"

//***************************************
ISR (USART0_UDRE_vect)		
{


	/*buffer_index++;			
if(buffer_index == MAX_SIZE)  	
	{
	UCSR0B &=~(1<<UDRIE0);
	buffer_index = 0;	
	ClearBit(flag, RESEIVE_OK);
	}
	else 
	{
	UDR0 = buf[buffer_index];	
	}*/

}
//***************************************

void UART_Init(void)
{

//Init UART
UBRR0L = LO(bauddivider);
UBRR0H = 0x0F & HI(bauddivider);
UCSR0A = 0;
UCSR0B = 1<<RXEN0|1<<TXEN0|0<<RXCIE0|0<<TXCIE0;
UCSR0C = 1<<UCSZ00|1<<UCSZ01;
}

/*void TIM_Display(void)
{
	extern unsigned char flag;
	extern unsigned char buf[];
	if(BitIsSet(flag, RESEIVE_OK)){
	UDR0 = buf[0];		
	UCSR0B|=(1<<UDRIE0);	
	}
}*/
