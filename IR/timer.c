
#define F_CPU 16000000UL
#define PRE 64UL


#include "timer.h"


#define baudrate 9600L
#define bauddivider (F_CPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

#define START_IMP_TH  (11000UL*(F_CPU/1000000))/PRE
#define START_IMP_MAX (14500UL*(F_CPU/1000000))/PRE
#define BIT_IMP_MAX   (2400UL*(F_CPU/1000000))/PRE
#define BIT_IMP_TH    (1500UL*(F_CPU/1000000))/PRE

unsigned char buffer_index=0;

volatile unsigned int icr1 = 0;
volatile unsigned int icr2 = 0;
enum state {IDLE = 0, RESEIVE = 1};  
enum state currentState = IDLE;

#define CAPTURE    0
#define RESEIVE_OK 1
#define RESEIVE_IND 2
volatile unsigned char flag = 0;

//первые четыре байта - адрес и команда, пятый байт - количество повторов
#define NUM_REPEAT 4
#define MAX_SIZE 5
unsigned char buf[MAX_SIZE] = { 0x32, 0x35, 0x30, 0x34, 0x12 };

//инициализация таймера Т1
void TIM_Init(void)
{
   DDRL &= ~(1<<PL1);
   PORTL |= (1<<PL1);
  
   TIMSK5 = (1<<ICIE5); //разрешаем прерывание по событию захват
   TCCR5A=(0<<COM5A1)|(0<<COM5A0)|(0<<COM5B1)|(0<<COM5B0)|(0<<COM5C1)|(0<<COM5C0)|(0<<WGM51)|(0<<WGM50);  //режим - normal, 
   TCCR5B=(0<<ICNC5)|(0<<ICES5)|(0<<WGM53)|(0<<WGM52)|(0<<CS52)|(1<<CS51)|(1<<CS50); //захват по заднему фронту, предделитель - 64
   TCCR5C=(0<<FOC5A)|(0<<FOC5B)|(0<<FOC5C);
   TCNT5 = 0;
   
   currentState = IDLE;
}

void UART_Init(void)
{

//Init UART
UBRR0L = LO(bauddivider);
UBRR0H = 0x0F & HI(bauddivider);
UCSR0A = 0;
UCSR0B = 1<<RXEN0|1<<TXEN0|0<<RXCIE0|0<<TXCIE0;
UCSR0C = 1<<UCSZ00|1<<UCSZ01;


}

//Прерывание по опустошению буффера УАПП
ISR (USART0_UDRE_vect)		
{
buffer_index++;			// Увеличиваем индекс

if(buffer_index == MAX_SIZE)  	// Вывели весь буффер? 
	{

	UCSR0B &=~(1<<UDRIE0);	// Запрещаем прерывание по опустошению - передача закончена
	ClearBit(flag, RESEIVE_OK);
	}
	else 
	{
	UDR0 = buf[buffer_index];	// Берем данные из буффера. 
	}
}
//прерывание по событию захват
ISR(TIMER5_CAPT_vect)
{

   icr1 = icr2;
   icr2 = ICR5;  
   SetBit(flag, CAPTURE);
  // SetBit(flag, RESEIVE_IND);
}

unsigned int TIM_CalcPeriod(void)
{
  unsigned int buf1, buf2;
  
  cli();
  buf1 = icr1;
  buf2 = icr2;
  sei(); 
  
  if (buf2 > buf1) {
    buf2 -= buf1;
  }
  else {
    buf2 += (65535 - buf1);    
  }
  return buf2;
}

//
void TIM_Handle(void)
{
  unsigned int period;
  static unsigned char data; 
  static unsigned char countBit, countByte;

  if (BitIsClear(flag, CAPTURE)) return;
 
  period = TIM_CalcPeriod();
  
  switch(currentState){
      //ждем стартовый импульс
      case IDLE:
	  
         if (period < START_IMP_MAX) {
		
           if (period > START_IMP_TH){
		   //
             data = 0;
             countBit = 0;
             countByte = 0;
             buf[NUM_REPEAT] = 0;
             currentState = RESEIVE;
           }
           else {
             buf[NUM_REPEAT]++;
           }
         }
         break;
       
       //прием посылки
       case RESEIVE:
	   
         if (period < BIT_IMP_MAX){
		 
           if (period > BIT_IMP_TH){
		   
              SetBit(data, 7);
           }
           countBit++;
           if (countBit == 8){
             buf[countByte] = data;
             countBit = 0;
             data = 0;
             countByte++;
			 
             if (countByte == (MAX_SIZE - 1)){

               SetBit(flag, RESEIVE_OK);
               currentState = IDLE;
               break;
             }             
           }
           data = data>>1;
         }
         break;
         
               
       default:
          break;
    }
 
  ClearBit(flag, CAPTURE);
  
}


void TIM_Display(void)
{

	if(BitIsSet(flag, RESEIVE_IND)){
	if(buffer_index == 5){buffer_index = 0;}			// Сбрасываем индекс
	UDR0 = buf[0];		// Отправляем первый байт
	UCSR0B|=(1<<UDRIE0);		// Разрешаем прерывание UDRE
	}
}

