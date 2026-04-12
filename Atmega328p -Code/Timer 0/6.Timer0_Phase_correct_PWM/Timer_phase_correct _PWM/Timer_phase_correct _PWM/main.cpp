/*
 * Timer_phase_correct _PWM.cpp
 *
 * Created: 12-Apr-26 3:36:21 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include <util/delay.h>

#define PORTD4 STATUS_LED
#define PORTB7 Power_switch
#define PORTB6 Speed_switch
#define PORTD3 Dircetion_switch

#define F_CPU 16000000UL
void phase_correct_pwm_init();
void speed_selection();
void power_check();

int count=0;
void phase_correct_pwm_init()
    /* Replace with your application code */
    {
	//Configure (Enable as 0) Power saver mode for Timer 0;
	PRR &=~(1<<PRTIM0);
	//Clear OC0A on compare match, set OC0A at BOTTOM,(non-inverting mode);
	TCCR0A &=~(1<<COM0A0);
	TCCR0A |= (1<<COM0A1);
	//Configure Waveform generation for phase correct PWM mode of operation.
	TCCR0A |= (1<<WGM00);
	TCCR0B &= ~(1<<WGM01 | 1<<WGM02);
	//Configure prescalar Bits for 8 prescalar value.- 4Khz (Suitable for motor frequency is- 1Khz to 20 Khz)
	TCCR0B &=~(1<<CS00| 1<<CS02);
	TCCR0B |= (1<<CS01);
	//Configure OC0A as output:PORTD6.
//	--------------------------------------------------------------------------------------
	/*Calculate % Duty cycle  requirements.
	
	  Duty cycle =   Tonx100/Time periode :(Time Periode = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(TOP+1)
	            i.e OCR0x = Dutycyclex(TOP+1)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x 510/100
					OCR0x = 255.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/NX510  
	              = 16x10^6/(8x510)
				  = 3.92khz ==4khz.(Suitable for motor)
   ----------------------------------------------------------------------------------------*/
   OCR0A = 255;         //Value to be loaded IN OCR0x for Fast PWM signal with 50% duty cycle.
   //Set as output OC0A pin to act as output.
					
    /* Replace with your application code */	
    }
	
void power_check()
{
	if (!(switch)
	{
		count++;
	}
	
	
}
int main(void)
{
	DDRD |= (1<<DDD6|1<<DDD1|1<<DDD2|DDD4); //Configure OC0A,Status LED,Motor O/p;
	DDRD &= ~(1<<Dircetion_switch|1<<Speed_switch|1<<Power_switch); //Switches configured as input;
	PORTB |= (1<< Power_switch | 1<< Speed_switch); //Enable Pull up;
	PORTD |= (1<<Dircetion_switch); //Enable Pull up;
	
	//Motor output initialization
	PORTD |= (1<<PORTD1);             
	PORTD &= ~(1<<PORTD2);
	
	phase_correct_pwm_init();
	power_check();
	speed_selection();
    
	while (1)
	{
		//for(uint16_t i=0;i<=255;i++)
		//{
		//	OCR0A = i;
		//	_delay_ms(100);
		//}
	}
}
