
//чтение времени из DS1307

#define F_CPU 1000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "TWI.h"
#include "LCD_I2C.h"
#include "ds1307.h"


int main(void)
{
I2C_Init();//инициализация модуля TWI
lcd_init();//инициализация LCD
lcd_clear();//очистка LCD и перевод курсора в 0.0

char buf[10];

struct Time ds1307_Time;

while (1)
{
//читаем время
ds1307_GetTime(&ds1307_Time);
sprintf(buf,"%02d:%02d:%02d",ds1307_Time.hours,ds1307_Time.minutes,ds1307_Time.seconds);
lcd_gotoxy(0,0);
lcd_putstring(buf);
_delay_ms(500);
}

}