//***************************************************************************
//  File........: main.c
//
//  Author(s)...: Pashgan    chipenable.ru
//
//  Target(s)...: ATMega...
//
//  Compiler....: GNU Compiler Collection (GCC) 4.3.2 
//
//  Description.: Использование схемы захвата для декодирования сигналов ИК ПДУ
//
//  Data........: 18.04.11 
//
//***************************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"
//#define F_CPU 16000000UL

int main(void)
{
  TIM_Init();
  UART_Init();
  DDRL |= (1<<PL5);

  sei();
  
  while(1){
     TIM_Handle();
	 	 _delay_ms(500);
	
		PORTL ^= (1<<PL5);    
     TIM_Display();
  }
  return 0;
}
