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
	uint8_t direction=0;
	uint8_t main=0;
	DDRD |= (1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4); //Data direction registers Enabled for PORTD Pins.
	DDRC &= ~(1<<DDC3); //PortC3 Configure as input.
	DDRC &= ~(1<<DDC4); //PortC4 configured as input,
	PORTC |= (1<<PC4);  //Enable the PORTC4 pin to access the internal pull-up configuration in Atmega328P.
    
    while (1) 
    {
		if((PINC&(1<<PINC3)))
		{
			main ^=1;
			_delay_ms(50);
			while((PINC&(1<<PINC3)));
		}
		//else
		//{
		//   main =0;
		//}	
				if(!(PINC & (1<<PINC4)))
				{
					direction=!direction; //Toggle the PIN status.
					_delay_ms(50);
					while(!(PINC & (1<<PINC4)));//wait for release.
				}
				if(main)
				{
					if(direction)
					{
						PORTD |=  (1<<PD1); //as output for motor.
						PORTD &= ~(1<<PD2); //as output for motor.
						PORTD |=  (1<<PD3);
						PORTD &= ~(1<<PD4);	 //as output for status led.
					}
				else if(!(direction))
				{
					PORTD |=  (1<<PD2); //as output for motor.
					PORTD &= ~(1<<PD1); //as output for motor.	
					PORTD |= (1<<PD4);	
					PORTD &= ~(1<<PD3);
				}
				}
				else
				{
					PORTD &= ~((1<<PD1)|(1<<PD2)|(1<<PD4)|(1<<PD3)); //0 all Ports to stop functioning.
				}
				
	}
	}

