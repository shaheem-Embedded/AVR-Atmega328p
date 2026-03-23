#define F_CPU 16000000UL // Fixed: Added missing zero for 16MHz
#include <avr/io.h>
#include <util/delay.h>

int main(void) {
	uint8_t direction = 0;
	uint8_t main_on = 0;

	DDRD |= (1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4);
	DDRC &= ~((1<<DDC3)|(1<<DDC4));
	PORTC |= (1<<PC3)|(1<<PC4); // Enable pull-ups for BOTH buttons

	while (1) {
		// --- 1. Update 'main_on' status ---
		// Button PC3 (Active Low)
		if (!(PINC & (1<<PINC3))) {
			main_on = 1;
			} else {
			main_on = 0;
		}

		// --- 2. Update 'direction' toggle ---
		// Button PC4 (Active Low)
		if (!(PINC & (1<<PINC4))) {
			_delay_ms(50);      // Debounce
			direction = !direction;
			while (!(PINC & (1<<PINC4))); // Wait for release
		}

		// --- 3. Apply changes to Pins ---
		if (main_on) {
			if (direction) {
				PORTD |=  (1<<PD1);
				PORTD &= ~(1<<PD2);
				PORTD |=  (1<<PD3); // LED A
				PORTD &= ~(1<<PD4);
				} else {
				PORTD |=  (1<<PD2);
				PORTD &= ~(1<<PD1);
				PORTD |=  (1<<PD4); // LED B
				PORTD &= ~(1<<PD3);
			}
			} else {
			// STOP everything if main is 0
			PORTD &= ~((1<<PD1)|(1<<PD2)|(1<<PD3)|(1<<PD4));
		}
	}
}