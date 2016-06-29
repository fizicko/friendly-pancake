#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "timer.h"

int main(void)
{
  TIM_Init();
  UART_Init();

  sei();
  
  while(1){	 
	 TIM_Display();
	 _delay_ms(1000);
  }
  return 0;
}
