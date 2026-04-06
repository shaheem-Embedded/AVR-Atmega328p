/*
 * Motor_driver_state_level.cpp
 *
 * Created: 24-Mar-26 5:34:23 PM
 * Author : SHAHEEM
 */ 
#define F_CPU 16000000UL 
#include<avr/io.h>
#include<util/delay.h>

void switch_state();
void update_switch();
void motor_control();

typedef enum
{
	STOP=0,
	FORWARD,
	REVERSE,
}State_t;

State_t CURRENT_STATE=STOP;
uint8_t direction_switch=0;
uint8_t main_switch=0;

int main(void)
{
DDRD |= (1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4);//SET DATA DIRECTION REGISTERS AS O/P.
DDRC &= ~((1<<DDC3)|(1<<DDC4));//SET DATA DIRECTION REGISTERS AS I/P.
PORTC |= (1<<PC4);   //ENABLE PULL UP.

while(1)
{
	switch_state();
	update_switch();
	motor_control();
	_delay_ms(10); 
}
}

void switch_state()
{
	if(PINC & (1<<PINC3))
	{
		main_switch ^=1;
		while(PINC & (1<<PINC3));
		_delay_ms(50);
	}
	if(!(PINC & (1<<PINC4)))
	{
		direction_switch =!direction_switch;
		while(!(PINC & (1<<PINC4)));
		_delay_ms(50);
	}
}

void update_switch()
{
	if(main_switch==0)
	{
		CURRENT_STATE =STOP;
	}
else
{
	if(direction_switch ==1)
	{
		CURRENT_STATE = FORWARD;
	}
	else
	{
		CURRENT_STATE = REVERSE;
	}
}
}

void motor_control()
{
	switch(CURRENT_STATE)
	{
		case STOP:
		PORTD &= ~((1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD4));
		break;
		case FORWARD:
		PORTD |= (1<<PD1)|(1<<PD3);
		PORTD &= ~((1<<PD2)|(1<<PD4));
		break;
		case REVERSE:
		PORTD |=(1<<PD2)|(1<<PD4);
		PORTD &= ~((1<<PD1)|(1<<PORTD3));
		break;
	}
}


