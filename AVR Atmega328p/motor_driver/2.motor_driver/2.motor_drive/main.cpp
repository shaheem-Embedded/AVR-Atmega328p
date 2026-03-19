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
	DDRD |= (1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4);
	DDRC &= ~(1<<DDC3);
    /* Replace with your application code */
    while (1) 
    {
		PORTD |=  (1<<PD1);
		PORTD &= ~(1<<PD2);
		PORTD |=  (1<<PD3);
		_delay_ms(3000);
		PORTD |=  (1<<PD2);
		PORTD &= ~(1<<PD1);
		PORTD &= ~(1<<PD3);
		_delay_ms(3000);
		
				if(PINC & (1<<PINC3))
				{
                   PORTD |=  (1<<PD4);					
			    }
				else
				{
					PORTD &=  ~(1<<PD4);
				}
        }
}

