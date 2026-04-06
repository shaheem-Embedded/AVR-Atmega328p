/*
 * test_timer0.cpp
 *
 * Created: 26-Mar-26 7:06:08 PM
 * Author : SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>

//void delay_1sec(void);

void delay_1sec(void)
{
	/*
		Fclk = 16 MHz = 16,000,000;
		1 tick = 1 / 16,000,000 = 62.5 ns;
		256 ticks = 256 x 62.5 ns = 16 micro seconds -> 1 overflow -> 16 x 10^-6;
		Number of overflow = Total time/time per overflow ;
		Count = 1s / 16 micro seconds = 62500 overflow required for 1s delay;*/
	   
	for(uint16_t i=0;i<62500; i++)
	{
			while(!(TIFR0 & (1<<TOV0)));            //Check the TIFR0 register with TOV0 overflag bit status;
			TIFR0 |= (1<<TOV0);                      //Clear the TOV0 bit by writing 1.
	}
} 
int main(void)
{
	   TCNT0    = 0;                            //Load initial value to TCNT0;
	   PRR    &= ~(1<<PRTIM0);                     //To eanble the Timer/Counter 0;
	                          
	   TCCR0A &= ~(1<<COM0A1|1<<COM0A0);         //Enable Noramal mode of BOTTOM to TOP- 0xFF ;OC0A disconnected;
	   
	   TCCR0A &= ~(1<<WGM00|1<<WGM01);          //Enable Waveform generation mode as normal;
	   TCCR0B &= ~(1<<WGM02);
	 
	   TCCR0B |= (1<<CS00);                     //Enable Clock with no Prescalar value;
	   TCCR0B &= ~(1<<CS01|1<<CS02);

       DDRD   |= (1<<DDD6);                       //Set Data diraction register as output for PORTD;
	   PORTD  &=~(1<<PORTD6);                     //Enable initially to 0;
		
    while (1)
    {
		PORTD ^= (1<<PORTD6);
		delay_1sec();
    }
}
