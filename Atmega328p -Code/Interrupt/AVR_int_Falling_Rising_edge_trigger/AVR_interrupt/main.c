/*
 * AVR_interrupt.c
 *
 * Created: 10-May-26 10:57:04 AM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include<stdint.h>
#include<avr/delay.h>
#include<util/delay.h>
#include <avr/interrupt.h>
#define F_CPU 16000000UL

void interrupt_init();

int main(void)
{
	//Configure LED pins as outputs.
	DDRC |=  (1<<DDC0)|(1<<DDC1)|(1<<DDC2);
    /* Replace with your application code */
	interrupt_init();
    while (1)
    {
	//Status LED for monitoring program Execution
	_delay_ms(20000);
	PORTC ^= (1<<PC2); //Toggle LED2.
   }
}

void interrupt_init()
{
	//configure INT0,INT1 pins as inputs.
	DDRD &= ~((1<<DDD2)|(1<<DDD3));
	//Enable as Pullup configuration for External interrupt Pins.
	PORTD |= (1<<PD2)|(1<<PD3);
	//Configure External interrupt control register for Falling edge detection(INT0) and Rising Edge detection(INT1)/Interrupt sense control bits.
	EICRA |= (1<<ISC01)|(1<<ISC11)|(1<<ISC10);
	EICRA &= ~(1<<ISC00);
	//Configure interrupt Mask registers-Enable.
	EIMSK |= (1<<INT0)|(1<<INT1);
	//Set Global Interrupt Enable Bit.
	//SREG |= (1<<I);
	//global interrupt Enable.
	sei();
}

ISR(INT0_vect)
{
	PORTC ^= (1<<PORTC0); //If interrupt flag0(INTF0) is set ,Interrupt service routine calls and Turn LED0 on.
}
ISR(INT1_vect)
{
	PORTC ^= (1<<PORTC1); //If interrupt flag1(INTF1) is set ,Interrupt service routine calls and Turn LED1 on.
}