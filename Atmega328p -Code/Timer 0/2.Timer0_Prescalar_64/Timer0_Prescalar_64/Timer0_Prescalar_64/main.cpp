/*
 * Timer0_Prescalar_64.cpp
 *
 * Created: 08-Apr-26 8:15:25 PM
 * Author: SHAHEEM
 */

#define F_CPU 16000000UL
#include <avr/io.h>


void delay_1s();
int main(void)
{
	 //Enable Power reduction mode for Timer 0.
	 PRR =(1<<PRTIM0);
	 //Enable Compare mode as Normal port operation.
	 TCCR0A &= ~(1<<COM0A1|1<<COM0A0);
	 //Select Waveform Generation mode as Normal.
	 TCCR0A &=~(1<<WGM00|1<<WGM01|1<<WGM02);
	 //Select Pre-scalar Value 64.
	 TCCR0B |= (1<<CS00 | 1<<CS01);
	 TCCR0B &=~(1<<CS02);
	 //Load Value to TCNTO.
	 TCNT0 =0;
/*---------------------------------------------------------------------------------------------------
	 pre-scalar value 64/Calculation. [Methode 1]
	 T=1/f, 1 clock periode is 1/16mhz = 62.5ns.
	 Tick time = 62.5 ns × 64
	 = 4000 ns.
	 1 counter increment = 4 µs.
	 Total Counts in 8 bit register = 256x4µs = 1.024 ms.
	 
	 1overflow occurs in =1.024 ms.
	 
	 *No of overflow requires for Total time = Total time/Time for 1 overflow.
	                                        = 1Sec/1.024 ms.
											= 976.56.
											~ 977Counts.
//---------------------------------------------------------------------------------------------------											
	  *pre-scalar value 64/Calculation. [Methode 2]
	   
	   T = 1/fold =    1/16Mhz.
	   TNew = 1/fnew,
	   
	   fnew =  fold/prescalr value = 16Mhz/64 =250Khz.
	   T= 1/250khz = 4µs.
	   1 counter increment = 4 µs.
	   Total Counts in 8 bit register = 256x4µs = 1.024 ms.
	  
	  1overflow occurs in =1.024 ms.
	 *No of overflow requires for Total time = Total time/Time for 1 overflow.
	 = 1Sec/1.024 ms.
	 = 976.56.
	 ~ 977Counts.
//-------------------------------------------------------------------------------------------------- 
     Replace with your application code */
	DDRD  |= (1<<DDD6|1<<DDD7);
	PORTD &= (1<<PORTD6|1<<PORTD7);

    while (1)
    {
	 PORTD |= (1<<PORTD7|1<<PORTD6);
	 delay_1s();
	 PORTD &= ~(1<<PORTD7|1<<PORTD6);
	 delay_1s();
    }
}

void delay_1s()
{
	for(int i=0;i<977;i++)
	{
		while(!(TIFR0 & (1<<TOV0)));
		TIFR0 |= (1<<TOV0);	
	}
}