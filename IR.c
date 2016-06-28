#include "timer.h"

#define PRE 64UL

#define START_IMP_TH  (12000UL*FCPU)/PRE
#define START_IMP_MAX (15000UL*FCPU)/PRE
#define BIT_IMP_MAX   (3000UL*FCPU)/PRE
#define BIT_IMP_TH    (1500UL*FCPU)/PRE

volatile unsigned int icr1 = 0;
volatile unsigned int icr2 = 0;
enum state {IDLE = 0, RESEIVE = 1};  
enum state currentState = IDLE;
unsigned char buffer_index=0;

#define CAPTURE    0
#define RESEIVE_OK 1
volatile unsigned char flag = 0;

//первые четыре байта - адрес и команда, пятый байт - количество повторов
#define NUM_REPEAT 4
#define MAX_SIZE 5
unsigned char buf[MAX_SIZE] = {0x31, 0x32, 0x33, 0x34, 0x35,};

//инициализация таймера Т1
void TIM_Init(void)
{
   DDRL &= ~(1<<PL1);
   PORTL |= (1<<PL1);
  
		TIMSK5 = (1<< ICIE1); //drcdlrrle ddlduaricl di niaunct croarn
		TCCR5A=(0<<COM5A1)|(0<<COM5A0)|(0<<COM5B1)|(0<<COM5B0)|(0<<COM5C1)|(0<<COM5C0)|(0<<WGM51)|(0<<WGM50);  //dlcce - normal, 
		TCCR5B=(0<<ICNC5)|(0<<ICES5)|(0<<WGM53)|(0<<WGM52)|(0<<CS52)|(1<<CS51)|(1<<CS50);
		TCCR5C=(0<<FOC5A)|(0<<FOC5B)|(0<<FOC5C); //croarn di craileo odiino, ddlaalecnleu - 64
		TCNT5 = 0;
   
   currentState = IDLE;
}


//*********************************************************
ISR (USART0_UDRE_vect)		
{
buffer_index++;			

if(buffer_index == MAX_SIZE)  
	{
	UCSR0B &=~(1<<UDRIE0);
	}
	else 
	{
	UDR0 = buf[buffer_index];
	}
}

//прерывание по событию захват******************************
ISR(TIMER5_CAPT_vect)
{

   icr1 = icr2;
   icr2 = ICR1;  
   SetBit(flag, CAPTURE);
}
//************************************************************
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

//***************************************************
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
//**************************************************
void TIM_Display(void)
	{
	if (BitIsSet(flag, RESEIVE_OK)){
	buffer_index=0;
	UDR0 = buf[0];
	UCSR0B|=(1<<UDRIE0);
	}
	//sei();
			
	}
//******************************************************
void UART_Init(void)
	{
#define F_CPU 16000000UL
#define baudrate 9600L
#define bauddivider (FCPU/(16*baudrate)-1)
#define HI(x) ((x)>>8)
#define LO(x) ((x)& 0xFF)

	//Init UART
	UBRR0H = HI(bauddivider);
	UBRR0L = LO(bauddivider);

	UCSR0A = 0;
	UCSR0B = 1<<RXEN0|1<<TXEN0|0<<RXCIE0|0<<TXCIE0;
	UCSR0C = 1<<UCSZ00|1<<UCSZ01;

}
