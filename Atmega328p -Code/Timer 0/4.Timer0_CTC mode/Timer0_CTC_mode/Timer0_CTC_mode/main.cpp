/*
 * Timer0_CTC_mode.cpp
 *
 * Created: 09-Apr-26 9:31:28 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#define F_CPU 16000000UL

void delay_1sec();
int main(void)
{
	//Configure TCCR0A register.
	//Compare output mode OC0A & OC0B set as Toggle mode.
	TCCR0A |= (1<<COM0A0);
	TCCR0A &= ~(1<<COM0A1);
	//Configure TCCR0B register.
	TCCR0A &= ~(1<<WGM00);
	TCCR0B &= ~(1<<WGM02);
	TCCR0A |= (1<<WGM01);
	//Select Pre-scalar Value 64.
	TCCR0B |= (1<<CS00|1<<CS01);
	TCCR0B &=~(1<<CS02);
	TIMSK0 &= ~(1<<TOIE0|1<<OCIE0B|1<<OCIE0A); 
	/*Required Time = (OC0RA+1)XPrescalar / F_CPU;
	  OCR0A = ((Required Time x F_CPU)/Prescalar)-1;
	  OCR0A = ((F_CPU/PrescalarxR.Frequency))-1; //Here required Time becomes 1/f.
	  OCR0A = (16X10^6 / 64X1000)-1;    (Calculated for 1ms,Since for 1 sec OCROA value to be loaded will be 15624 and it is not achievable for 8 Bit Timer/Counte Hardware.
	                                     So,We will calculate it for 1 msec and use loop to achieve the 1 sec Delay)
	 OCR0A = 250-1 ;=249.									 
	//Load value in OCR0A to be compared with TCNT0.
    /* Replace with your application code */
	OCR0A = 249;                                 //TCNT0 value will be 0,When TCNT0 equals to OCR0A Value and Flag OCF0A will be set.
	DDRB = (1<<DDB2);                            //Data direction set as output.
	PORTB &= ~(1<<PORTB2);                       //Port output initially as 0;
	DDRD = (1<<DDD6);                            //OC0A Toggle mode ,Data direction set or OC0A Pin output.
    while (1)
    {
	 PORTB ^= (1<<PORTB2);
	 delay_1sec();
    }
}

void delay_1sec()
{
	for(int i=0;i<1000;i++)
	{
		while (!(TIFR0 & (1<<OCF0A)));
		TIFR0 |=(1<<OCF0A);
	}
}