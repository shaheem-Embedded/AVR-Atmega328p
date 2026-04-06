/*
 * test_timer0.cpp
 *
 * Created: 26-Mar-26 7:06:08 PM
 * Author : SHAHEEM
 */

#include <avr/io.h>
#include <avr/io.h>
void delay_1s(void);

int main(void)
{
	//step 1: load initial value 0
	TCNT0 = 0x00;
	//step 2: choosing normal mode: mode0
    TCCR0B &= ~(1 << WGM12);
	//step 3: selecting pre-scaler value - No prescaling
	TCCR0B &= ~((1 << CS02) | (1 << CS01));
	TCCR0B |= (1 << CS00);
    //step 4: overflow calculation
	/*
		Fclk = 16 MHz = 16,000,000
		1 tick = 1 / 16,000,000 = 62.5 ns
		256 ticks = 256 x 65.5 ns = 16 micro seconds -> 1 overflow -> 16 x 10^-6
		for 1s = 1 / 16 micro seconds = 62500 overflow required for 1s delay
	*/
		/*PORTB config as output*/
		DDRB |= (1 << DDB2);
		/*making low during starting*/
		PORTB &= (1 << PB2);
		while (1)
		{
			PORTB ^= (1 << PB2);
			delay_1s();
		}
}
	void delay_1s(void)
	{
	for(uint16_t i = 0; i < 62500; i++)
	{
		while (!(TIFR0 & (1 << TOV0)));
		TIFR0 |= (1 << TOV0); //clearing the bit by writing 1 to it.
	}
	}


