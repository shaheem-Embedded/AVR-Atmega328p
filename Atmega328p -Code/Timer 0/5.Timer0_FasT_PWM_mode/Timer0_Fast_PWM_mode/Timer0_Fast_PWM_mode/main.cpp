/*
 * Timer0_Fast_PWM_mode.cpp
 *
 * Created: 10-Apr-26 9:08:33 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include <util/delay.h>

#define F_CPU 16000000UL

//void fast_pwm_init();

void fast_pwm_init()
{
//Configure (Enable as 0) Power saver mode for Timer 0;
	PRR &=~(1<<PRTIM0);
	//Clear OC0A on compare match, set OC0A at BOTTOM,(non-inverting mode);
	TCCR0A |= (1<<COM0A0);
	TCCR0A |= (1<<COM0A1);
	//Configure Waveform generation for Fast PWM mode of operation.
	TCCR0A |= (1<<WGM00|1<<WGM01);
	TCCR0B &= ~(1<<WGM02);
	//Configure prescalar Bits for 64 prescalar value.
	TCCR0B|=(1<<CS00 | 1<<CS01);
	TCCR0B &=~(1<<CS02);
	//Configure OC0A as ouput:PORTD6.
	DDRD |= (1<<DDD6);
	
//	--------------------------------------------------------------------------------------
	/*Calculate % Duty cycle  requirements.
	
	  Duty cycle =   Tonx100/Time periode :(Time Periode = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(TOP+1)
	            i.e OCR0x = Dutycyclex(TOP+1)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x 256/100
					OCR0x = 128.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/NX256  
	              = 16x10^6/(64x256)
				  = 977Khz.==1khz.(Suitable for LED)
   ----------------------------------------------------------------------------------------*/
    // OCR0A = 0;         //Value to be loaded IN OCR0x for Fast PWM signal with 50% duty cycle.
    //Set as output OC0A pin to act as output.
					
   /* Replace with your application code */
	
}
int main(void)
{ 
	fast_pwm_init();
    while (1)
    {
     for(uint16_t i=0;i<=255;i++)
	  {
	 	 OCR0A = i;
	 	_delay_ms(300);	
      }
	}
}
