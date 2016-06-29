//***************************************************************************
//  File........: main.c
//
//  Author(s)...: Pashgan    chipenable.ru
//
//  Target(s)...: ATMega...
//
//  Compiler....: GNU Compiler Collection (GCC) 4.3.2 
//
//  Description.: ������������� ����� ������� ��� ������������� �������� �� ���
//
//  Data........: 18.04.11 
//
//***************************************************************************
#include <avr/io.h>
#include <avr/interrupt.h>
#include "lcd_lib.h"
#include "timer.h"

int main(void)
{
  LCD_Init();
  TIM_Init();
  LCD_SendString("winavr");
  sei();
  
  while(1){
     TIM_Handle();    
     TIM_Display();
  }
  return 0;
}
