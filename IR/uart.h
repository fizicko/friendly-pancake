#ifndef UART_H
#define UART_H

#define RESEIVE_OK 1

#define F_CPU 16000000UL

#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

void UART_Init(void);
void TIM_Display(void);

#endif
