// В настройках проекта обязательно правильно укажите свою тактовую частоту
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include "timer.h"
#include "n3310.h"
#include "picture.h"
#include "uart.h"
int main()
{
		LcdInit();
		_delay_ms(500);
		LcdClear();
		TIM_Init();
		//UART_Init();

  sei();
  
  while(1)
  {


  	
	 _delay_ms(1000);
	extern unsigned char flag;

	if(BitIsSet(flag, RESEIVE_OK)){
		ClearBit(flag, RESEIVE_OK);
		extern unsigned char buf[];
		if ( buf[2]== 0x41) {
		LcdInit();
		}
		if ( buf[2]== 0x01) {
		LED_PORT ^= (_BV (LED_PIN));
		}
		if ( buf[2]== 0x05) {
					   
		LcdClear();
        LcdImage(Picture2);
        LcdUpdate();
		LED_PORT &= ~(_BV (LED_PIN));
	
		int v;
			for (v=0;v<3;v++)
	{

	_delay_ms(1000);
		LcdSingleBar ( 12,2,2,2,PIXEL_OFF );
		LcdSingleBar ( 12,5,2,2,PIXEL_OFF );
        LcdUpdate();
		_delay_ms(1000);
		LcdSingleBar ( 12,2,2,2,PIXEL_ON );
		LcdSingleBar ( 12,5,2,2,PIXEL_ON );
        LcdUpdate();
	}
				

		_delay_ms(700);		
		LED_PORT |= _BV (LED_PIN);
				LcdClear();
 //       LcdImage(Picture2);
 _delay_ms(70);
        LcdUpdate();
		}
	}
      

  		
	
	  	 


  }



//	   LED_PORT &= ~(_BV (LED_PIN));
/*		LcdGotoXYFont(0,0);
		LcdFStr(FONT_1X,(unsigned char*)PSTR("1234"));
		LcdGotoXYFont(0,1);
		LcdFStr(FONT_1X,(unsigned char*)PSTR(";-)"));
		LcdUpdate();
		_delay_ms(500);
		LcdClear();
		LcdCircle(9,8,7,PIXEL_ON);
		LcdUpdate();
		_delay_ms(500);
		LcdLine(6,12,20,4,PIXEL_ON);
		LcdUpdate();
		_delay_ms(500);
		LcdSingleBar ( 10,14,8,10,PIXEL_ON );
		LcdUpdate();
		_delay_ms(500);


		LcdRect(16,4,27,12,PIXEL_ON);
		LcdUpdate();
		_delay_ms(500);
		LcdPixel(4,8,PIXEL_ON);
		
        LcdUpdate();
		_delay_ms(500);

	    LcdClear();
        LcdImage(Picture);
        LcdUpdate();
			_delay_ms(500);
	    LcdClear();
        LcdImage(Picture1);
        LcdUpdate();
	
        _delay_ms(500);





		LcdClear();
		LcdImage(PictureC);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,20,3,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureA);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,20,3,PIXEL_OFF);
		LcdLine(20,8,21,3,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureB);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,21,3,PIXEL_OFF);
		LcdLine(20,8,22,3,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureD);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,22,3,PIXEL_OFF);
		LcdLine(20,8,23,3,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureE);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,23,3,PIXEL_OFF);
		LcdLine(20,8,24,4,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureF);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,24,4,PIXEL_OFF);
		LcdLine(20,8,25,5,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdImage(PictureG);
		LcdCircle(20,8,7,PIXEL_ON);
		LcdLine(20,8,25,5,PIXEL_OFF);
		LcdLine(20,8,25,6,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdLine(20,8,25,6,PIXEL_OFF);
		LcdLine(20,8,25,7,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
		_delay_ms(1000);
		LcdLine(20,8,25,7,PIXEL_OFF);
		LcdLine(20,8,25,8,PIXEL_ON);
		LcdLine(20,8,20,5,PIXEL_ON);
		LcdUpdate();
	_delay_ms(1000);*/
	
		while(0)
		{
			   
		LcdClear();
        LcdImage(Picture2);
        LcdUpdate();
LED_PORT &= ~(_BV (LED_PIN));
	
		int v;
			for (v=0;v<3;v++)
	{

	_delay_ms(1000);
		LcdSingleBar ( 12,2,2,2,PIXEL_OFF );
		LcdSingleBar ( 12,5,2,2,PIXEL_OFF );
        LcdUpdate();
		_delay_ms(1000);
		LcdSingleBar ( 12,2,2,2,PIXEL_ON );
		LcdSingleBar ( 12,5,2,2,PIXEL_ON );
        LcdUpdate();		

	}


	_delay_ms(1000);
		LcdClear();
        LcdImage(PictureH);
        LcdUpdate();
		_delay_ms(3000);
//		LcdClear();
//        LcdImage(PictureJ);
//        LcdUpdate();
//

		LED_PORT |= _BV (LED_PIN);
		_delay_ms(30000);	

}
	

    return 0;
}
