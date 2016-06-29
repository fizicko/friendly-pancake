//***************************************************************************
//  File........: timer.h
//
//  Author(s)...: Pashgan    chipenable.ru
//
//  Target(s)...: ATMega...
//
//  Compiler....: GNU GCC
//
//  Description.: Модуль для приемка ИК сигналов. Протокол фирмы NEC  
//
//  Data........: 18.04.11  
//
//***************************************************************************
#ifndef TIM_H
#define TIM_H

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bits_macros.h"




void TIM_Init(void);       //инициализация таймера Т1
void TIM_Handle(void);     //обработка сигналов 
void TIM_Display(void);    //Вывод принятого кода на дисплей
void UART_Init(void);

#endif //TIM_H
