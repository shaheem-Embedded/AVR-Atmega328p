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
#include "uart.h"
#include "timer1.h"


int main(void)
{ 
	float temperature;
	char buffer[20];
	//a=25.45;
	uint16_t adc_data;
	timer_1_enable();
	LED_port_enable();
	lcd_init();    // initialize the LCD always first
	ADC_init();     // initialize the ADC
	uart_init();    // initialize the UART transmission
	char data = 'H';

    /* Replace with your application code */
    while (1)
    { 
		lcd_set_cursor(0, 0);                      //Set Cursor to line ,Column 0
		lcd_print_string("Atmos.Temp:");           //Print in LCD
		adc_data = ADC_read();                     //Get value of ADC_read function
		temperature = (adc_data * 500.0) / 1023.0; //Temperature calculation
		lcd_set_cursor(1, 0);                      //Set Cursor to line 1 ,Column 0
		lcd_print_float(temperature);                //Print data in temperature variable
		lcd_data(0xDF);                              //Print degree 
		lcd_print_string("C");                       //Print "C"
		_delay_ms(300);                              //small delay after Displaying the current temperature value. 
		transmit_string(data);
		// UART transmit to PC
		//sprintf(buffer, "Atmos.Temp: %.2f C\r\n", temperature);
		uint16_t temp_whole = (uint16_t)temperature;
		uint16_t temp_frac = (uint16_t)((temperature - temp_whole) * 100);

		char buffer[20];
		sprintf(buffer, "Atmos.Temp: %d.%02d C\r\n", temp_whole, temp_frac);
		transmit_string(buffer);
		_delay_ms(1000);
    }
}

