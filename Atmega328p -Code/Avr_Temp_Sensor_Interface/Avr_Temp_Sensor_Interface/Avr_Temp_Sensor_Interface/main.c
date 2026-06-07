/*
 * Avr_Temp_Sensor_Interface.c
 *
 * Created: 07-Jun-26 5:03:39 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include<stdint.h>
#include<util/delay.h>

#include "AVT_TEMP_SENSROR_INTERFACE.h"
#include "Avr_LCD_Interface.h"

int main(void)
{ 
	float temperature;
	//a=25.45;
	uint16_t adc_data;
	lcd_init();    // always first
	ADC_init();
//	ADC_read();
	

    /* Replace with your application code */
    while (1)
    { 
		lcd_set_cursor(0, 0);
		lcd_print_string("Atmos.Temp:");
		adc_data = ADC_read();
		temperature = (adc_data * 500.0) / 1023.0;
		lcd_set_cursor(1, 0);
		lcd_print_float(temperature);
		lcd_data(0xDF);
		lcd_print_string("C");
		_delay_ms(300);
    }
}

