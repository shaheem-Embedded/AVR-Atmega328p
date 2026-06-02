/*
 * timer_1.c
 *
 * Created: 02-Jun-26 9:13:05 PM
 *  Author: SHAHEEM
 */ 
#include <avr/io.h>
#include <avr/interrupt.h>
#include "timer_1.h"

volatile uint8_t overflow_count=0;

void timer_1_enable()
{
	TCNT1 = 0; //Enable Timer1 with 0 initial value;
	TCCR1A  &= ~(1<<COM1A1| 1<<COM1A0|1<<COM1B1|1<<COM1B0); //Enable T1 in the normal non PWM mode of operation.
	PRR     &=~(1<<PRTIM1); ////To enable the Timer/Counter 1 without power shut down;
	TCCR1A  &=~(1<<WGM10|1<<WGM11); //Enable Waveform generation mode as normal;
	TCCR1B  &=~(1<<WGM12|1<<WGM13);//Enable Waveform generation mode as normal;
	//Enable 64 prescalar for timer 1
	TCCR1B &=~(1<<CS12);
	TCCR1B |= (1<<CS10|1<<CS11);
	TIMSK1 |=(1<<TOIE1); //Enable Timer 1 overflow Interrupt;
	sei();
}

ISR(TIMER1_OVF_vect)
{
	overflow_count++;
	if (overflow_count==1)
	{
		TCNT1 = 6072;   // pre-load for remaining time
	}
	if(overflow_count>=2)
	{
		PORTB ^= (1<<PORTB5);
		PORTD ^= (1<<PORTD1);
		overflow_count = 0;
		TCNT1 = 0;
	}
}