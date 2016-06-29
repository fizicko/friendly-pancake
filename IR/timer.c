#define F_CPU 16000000UL
#define PRE 64UL

#include "timer.h"

unsigned char buffer_index=0;
unsigned int period;
static unsigned char data; 
static unsigned char countBit, countByte;
volatile unsigned int icr1 = 0;
volatile unsigned int icr2 = 0;
volatile unsigned char flag = 0;

enum state {IDLE = 0, RESEIVE = 1};  
enum state currentState = IDLE;

unsigned char buf[MAX_SIZE];

//***************************************
void TIM_Init(void)
{
   DDRL &= ~(1<<PL1);
   PORTL |= (1<<PL1);
  
   TIMSK5 = (1<<ICIE5); 
   TCCR5A=(0<<COM5A1)|(0<<COM5A0)|(0<<COM5B1)|(0<<COM5B0)|(0<<COM5C1)|(0<<COM5C0)|(0<<WGM51)|(0<<WGM50); 
   TCCR5B=(0<<ICNC5)|(0<<ICES5)|(0<<WGM53)|(0<<WGM52)|(0<<CS52)|(1<<CS51)|(1<<CS50);
   TCCR5C=(0<<FOC5A)|(0<<FOC5B)|(0<<FOC5C);
   TCNT5 = 0;
   
   currentState = IDLE;
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

//***************************************
ISR (USART0_UDRE_vect)		
{
	buffer_index++;			
if(buffer_index == MAX_SIZE)  	
	{
	UCSR0B &=~(1<<UDRIE0);
	buffer_index = 0;	
	ClearBit(flag, RESEIVE_OK);
	}
	else 
	{
	UDR0 = buf[buffer_index];	
	}

}
//***************************************
ISR(TIMER5_CAPT_vect)
{

   icr1 = icr2;
   icr2 = ICR5;  

	period = icr2;
	
  if (icr2 > icr1) {
    period -= icr1;
  }
  else {
    period += (65535 - icr1);    
  }	
	
	switch(currentState){
      
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
   
}




//***************************************
void TIM_Display(void)
{
	if(BitIsSet(flag, RESEIVE_OK)){
	UDR0 = buf[0];		
	UCSR0B|=(1<<UDRIE0);	
	}
}
