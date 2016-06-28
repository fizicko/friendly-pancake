// Â íàñòðîéêàõ ïðîåêòà îáÿçàòåëüíî ïðàâèëüíî óêàæèòå ñâîþ òàêòîâóþ ÷àñòîòó
#include <avr/io.h>
#include <util/delay.h>
#include <avr/pgmspace.h>

#include "n3310.h"
#include "picture.h"

int main()
{

	LcdInit();
	_delay_ms(500);
	LcdClear();
	LED_PORT &= ~(_BV (LED_PIN));
	LED_PORT |= _BV (LED_PIN);
	_delay_ms(30000);	

}
	

    return 0;
}
