/*
 * avr_dude_test.c
 *
 * Created: 31-May-26 9:59:55 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>

int main(void)
{
	DDRB |= (1<<DDB5);
    /* Replace with your application code */
    while (1)
    {
		PORTB |= (1<<PORTB5);
		_delay_ms(1000);
		PORTB &=~ (1<<PORTB5);
		_delay_ms(1000);
    }
}

