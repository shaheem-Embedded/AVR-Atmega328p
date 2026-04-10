/*
 * timer0_1024 Prescalar mode.cpp
 *
 * Created: 26-Mar-26 7:06:08 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#define F_CPU 16000000UL
void delay_1s(void);

int main(void)
{
	 //Enable Power reduction mode for Timer 0.
	 PRR =(1<<PRTIM0);
	 //Enable Compare mode as Normal port operation.
	 TCCR0A &= ~(1<<COM0A1|1<<COM0A0);
	 //Select Waveform Generation mode as Normal.
	 TCCR0A &=~(1<<WGM00|1<<WGM01|1<<WGM02);
	 //Select Pre-scalar Value 1024.
	 TCCR0B |= (1<<CS00 | 1<<CS02);
	 TCCR0B &=~(1<<CS01);
	 //Load Value to TCNTO.
	 TCNT0 =0;
    /*---------------------------------------------------------------------------------------------------
	 pre-scalar value 1024  /Calculation. [Methode 1]
	 T=1/f, 1 clock periode is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 1024
	 = 166.4 microseconds.
	 1 counter increment = 64 µs.
	 Total Counts in 8 bit register = 256x64µs = 16.384 ms.
	 
	 1overflow occurs in =16.384 ms.
	 
	 *No of overflow requires for Total time = Total time/Time for 1 overflow.
	                                        = 1Sec/16.384 ms..
											= 61.035.
											~ 61 Counts.
//---------------------------------------------------------------------------------------------------											
	  *pre-scalar value 64/Calculation. [Methode 2]
	   
	   T = 1/fold =    1/16Mhz.
	   TNew = 1/fnew,
	   
	   fnew =  fold/prescalr value = 16Mhz/1024 =15.625Khz.
	   T= 1/15.625Khz = 64µs.
	   1 counter increment = 64 µs.
	   Total Counts in 8 bit register = 256x64µs = 16.384 ms.
	  
	  1overflow occurs in =16.384 ms.
	 *No of overflow requires for Total time = Total time/Time for 1 overflow.
	 = 1Sec/16.384 ms.
	 = 61.035.
	 ~ 61Counts.
//-------------------------------------------------------------------------------------------------- 
		/*PORTB config as output*/
		DDRB |= (1 << DDB2);
		/*making low during starting*/
		PORTB &= (1 << PORTB2);
		while (1)
		{
			PORTB ^= (1 << PORTB2);
			delay_1s();
		}
}
	void delay_1s(void)
	{
	for(uint16_t i = 0; i < 61; i++)
	{
		while (!(TIFR0 & (1 << TOV0)));
		TIFR0 |= (1 << TOV0); //clearing the bit by writing 1 to it.
	}
	}


