/*
 * T0_interrupt.cpp
 *
 * Created: 07-Apr-26 7:34:39 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include<avr/interrupt.h>
#define F_CPU 16000000UL

int main(void)
{
	DDRD |= (1<<DDD6|1<<DDD7);
	PORTD  =(1<<PORTD6 | 1<<PORTD7);
    while (1)
    {
		
    }
}

void Timer0_interrupt_init()
{
	sei();
	//step 2: choosing normal mode: mode0
	TCCR0A &= ~((1 << WGM00)|(1 << WGM01));
	TCCR0B &= ~(1 << WGM02);
	//step 3: prescalar value : 64
	TCCR0B |= ((1 << CS01) | (1 << CS00));
	TCCR0B &= ~(1 << CS02);
	//Enable T0 interrupt
	TIMSK0 |= (1<<TIMSK0);
	
}

