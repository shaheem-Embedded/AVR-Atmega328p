/*
 * Timer0_Phase_correct_PWM.cpp
 *
 * Created: 17-Apr-26 10:42:17 PM
 * Author : SHAHEEM
 */
#include <avr/io.h>
#include <util/delay.h>

#define STATUS_LED      PORTB0 
#define PL              PORTB1
#define M1              PORTC0
#define M2              PORTC1


#define Speed_switch     PORTD0
#define Direction_switch PORTD1 
#define Power_switch     PORTD2 

#define F_CPU 16000000UL

typedef enum
{
	STOP,
	FORWARD,
	REVERSE,
	DUTY_CYCLE0,
	DUTY_CYCLE1,
	DUTY_CYCLE2,
	DUTY_CYCLE3,
	DUTY_CYCLE4,
}Control_t;

Control_t STATE;
int duty =0;

// Global Flags
int count      = 0;
int power_flag = 0;
int dir_flag   = 0; // 0 for Forward, 1 for Reverse

void phase_correct_pwm_init() 
{
	//Configure (Enable as 0) Power saver mode for Timer 0;
    PRR &= ~(1<<PRTIM0);
	//Clear OC0A on compare match when up-counting. Set OC0A on compare match when down-counting.;(Non inverting)
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |=  (1<<COM0A1);
	//Configure Waveform generation for phase correct PWM mode of operation.(TOP=0XFF)
	TCCR0A |= (1<<WGM00);
	TCCR0B &= ~(1<<WGM01|1<<WGM02);
	//Configure prescalar Bits for 8 prescalar value.
	TCCR0B&=~(1<<CS00 | 1<<CS02);
	TCCR0B |=(1<<CS01);
    //Configure OC0A as output
    DDRD |= (1<<DDD6);                 // PWM Pin Output
	
	//	--------------------------------------------------------------------------------------
	/*Calculate % Duty cycle requirements.
	
	  Duty cycle =   Tonx100/Time period :(Time period = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(2xTOP)
	            i.e OCR0x = (Duty cycle x 255)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x (255)/100
					OCR0x = 128.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/N(510)  
	              = 16x10^6/(8x510)  -Prescalar value 8.
				  = 3.92Khz.(Suitable for Motor)
   ----------------------------------------------------------------------------------------*/
  // OCR0A = 255;         //Value to be loaded IN OCR0x for phase correct PWM signal with 50% duty cycle.				
}


void switch_status()
{
	if(!(PIND & (1<<PIND2)))
	{
		power_flag ^= 1;
		while(!(PIND & (1<<PIND2)));
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(400);
		PORTB &=~(1<<PB0);
		
	}
	if(!(PIND & (1<<PIND1)))
	{
		dir_flag ^= 1;
		while(!(PIND & (1<<PIND1)));
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(400);
		PORTB &=~(1<<PB0);
	}
	if(!(PIND & (1<<PIND0)))
	{
		while(!(PIND & (1<<PIND0)));
		_delay_ms(400);
		count ++;
		if(count>5)
		count=0;
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(100);
		PORTB &=~(1<<PB0);
	}
}

void switch_update()
{
	if((power_flag)==0)
	{
		count=0;
		duty = 0;
		STATE = STOP;
		return;
	}
	else
	{
		if((dir_flag)==0)
		{
			STATE = FORWARD;
		}
		else
		{
			STATE = REVERSE;
		}
	}
	if (count==1) duty = 0;
	if (count==2) duty = 30;
	if (count==3) duty = 100;
	if (count==4) duty = 150;
	if (count==5) duty = 255;
}

void motor_control()
{
	switch(STATE)
	{
			case STOP:
			PORTC &= ~(1<<PC0);
			PORTC &= ~(1<<PC1);
			count=0;
			OCR0A = 0;
			break;
			
			case FORWARD:
			PORTC |= (1<<PC0);
			PORTC &= ~(1<<PC1);
			break;
			
			case REVERSE:
			PORTC |= (1<<PC1);
			PORTC &= ~(1<<PC0);
			break;
	}
	OCR0A = duty;
}

int main()
{
	DDRB |= (1<<DDB0 | 1<<DDB1); // Configure LED as ports as output.
	DDRC |= (1<<DDC0 | 1<<DDC1); // Configure Motor as ports as output.
	DDRD &= ~(1<<DDD0| 1<<DDD1 |1<<DDD2);//Configure Switches as input.
	PORTD |= (1<<PD0 | 1<< PD1 |1<<PD2);//Enable internal pull up configurations for Input switches.
	
	_delay_ms(10);
	PORTB |= (1<<PB1);
    phase_correct_pwm_init();
	while(1)
	{
		switch_status();
		switch_update();	
		motor_control();
	}
}
