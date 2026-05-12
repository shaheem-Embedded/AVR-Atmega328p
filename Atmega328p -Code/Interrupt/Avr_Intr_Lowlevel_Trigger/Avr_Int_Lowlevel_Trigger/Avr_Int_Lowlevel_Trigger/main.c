/*
 * AVR_interrupt.c
 *
 * Created: 10-May-26 10:57:04 AM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include<stdint.h>
#include<util/delay.h>
#include <avr/interrupt.h>


void interrupt_init();
void motor_control();
volatile int flag = 0;
int main(void)
{
	//Configure LED pins as outputs.
	DDRC |=  (1<<DDC0)|(1<<DDC1);
	//Configure Buzzer & Motor pin as outputs.
	DDRB |=  (1<<DDB1);
	DDRD |=  (1<<DDD6)|(1<<DDD7);
    /* Replace with your application code */
	PORTB &= ~(1<<PB1);//Turn buzzer OFF.
	interrupt_init();
	
    while (1)
    {
	//Status LED for monitoring program Execution
	PORTC ^= (1<<PC1); //Toggle LED2.
	//Turn motor on in Clock wise direction
	_delay_ms(200);
	//flag = 0;
	if(PIND & (1<<PD2))
	{
		flag = 0;
	}
	motor_control();
	
   }
}

void interrupt_init()
{
	//configure INT0 pins as inputs.(Implemented Switch)
	DDRD &= ~(1<<DDD2);
	//Enable as Pullup configuration for External interrupt Pin.
	PORTD |= (1<<PD2);
	//Configure External interrupt control register for low level detection(INT0),
	EICRA &= ~((1<<ISC01)|(1<<ISC00));
	//Configure interrupt Mask registers-Enable.
	EIMSK |= (1<<INT0);
	//Set Global Interrupt Enable Bit.
	//SREG |= (1<<I);
	//global interrupt Enable.
	sei();
}
void motor_control()
{
	if(!(flag))
	{
		PORTD |= (1<<PD6);
		PORTD &= ~(1<<PD7);//Rotate motor clock wise direction.
		PORTC &= ~ (1<<PC0); //Turn Fault detection LED OFF.
	//	PORTB &= ~(1<<PB1); //Turn buzzer OFF.
	}
	else
	{
		PORTD |= (1<<PD7);
		PORTD &= ~(1<<PD6);//Rotate motor Anti clock wise direction.
		PORTC |= (1<<PC0); //Turn Fault detection LED ON.
		for(int i=0; i<200; i++)
		{
			PORTB ^= (1<<PB1);
			_delay_us(500);
		}
	}
}
ISR(INT0_vect)
{
	flag = 1;
}
