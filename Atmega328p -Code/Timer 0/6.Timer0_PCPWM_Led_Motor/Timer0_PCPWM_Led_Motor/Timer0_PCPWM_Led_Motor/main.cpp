/*
 * Timer0_Phase_correct_PWM_LED_Motor Control.cpp
 *
 * Created: 15-Apr-26 10:42:17 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include <util/delay.h>
#define F_CPU 16000000UL

void phase_correct_pwm_init()
{
	//Configure (Enable as 0) Power saver mode for Timer 0;
	PRR &=~(1<<PRTIM0);
	//Clear OC0A on compare match when up-counting. Set OC0A on compare match when down-counting.;(Non inverting)
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |=  (1<<COM0A1);
	//Configure Waveform generation for phase correct PWM mode of operation.(TOP=OxFF)
	TCCR0A |= (1<<WGM00);
	TCCR0A &= ~(1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	//Configure prescalar Bits for 64 prescalar value.
	TCCR0B&=~(1<<CS02);
	TCCR0B |=(1<<CS00|1<<CS01);
	//Configure OC0A as output:PORTD6.
	DDRD |= (1<<DDD6);
//	--------------------------------------------------------------------------------------
	/*Calculate % Duty cycle requirements.
	
	  Duty cycle =   Tonx100/Time period :(Time period = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(TOP)
	            i.e OCR0x = (Duty cycle x 255)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x (255)/100
					OCR0x = 128.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/N(510)  
	              = 16x10^6/(64x510)
				  = 490hz.(Suitable for LED)
   ----------------------------------------------------------------------------------------*/
  // OCR0A = 255;         //Value to be loaded IN OCR0x for phase correct PWM signal with 50% duty cycle.
					
    /* Replace with your application code */
}

int main(void)
{
	//Configure OC0A as output:PORTD6.
	DDRD |= (1<<DDD6|1<<DDD0);
	DDRC |= (1<<DDC5|1<<DDC4);
	
	phase_correct_pwm_init();
	OCR0A = 128;
	_delay_ms(200);
	PORTC |= 1<<PC5;
	PORTC &= ~1<<PC4;
	PORTD |= 1<<PD0;
    while (1)
    {
		 //for(uint16_t i=0;i<=255;i++)
		 //{
			 //OCR0A = i;
			 //_delay_ms(200);
		 //}
		 
	 }
    }


