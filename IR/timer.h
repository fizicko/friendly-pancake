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

#define FCPU 16UL

#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

#define START_IMP_TH  (12000UL*(F_CPU/1000000))/PRE
#define START_IMP_MAX (15000UL*(F_CPU/1000000))/PRE
#define BIT_IMP_MAX   (3000UL*(F_CPU/1000000))/PRE
#define BIT_IMP_TH    (1500UL*(F_CPU/1000000))/PRE

#define RESEIVE_OK 1
#define RESEIVE_IND 2

#define NUM_REPEAT 4
#define MAX_SIZE 5
#define CAPTURE    0

void TIM_Init(void);       //инициализация таймера Т1
void TIM_Display(void);    //Вывод принятого кода на дисплей
void UART_Init(void);

#endif //TIM_H#ifndef TIM_H

