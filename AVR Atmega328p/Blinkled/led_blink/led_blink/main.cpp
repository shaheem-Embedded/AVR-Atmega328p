/*
 * led_blink.cpp
 *
 * Created: 17-Mar-26 5:46:50 PM
 * Author : SHAHEEM
 */ 
#define F_CPU 1600000UL
#include <avr/io.h>
#include<util/delay.h>

int main(void)
{
	DDRD |= (1<<3)|(1<<1);
    /* Replace with your application code */
    while (1) 
    {
		PORTD |= (1<<3)|(1<<1);
		_delay_ms(3000);
		PORTD = ~((1<<3));
		_delay_ms(3000);
    }
}

