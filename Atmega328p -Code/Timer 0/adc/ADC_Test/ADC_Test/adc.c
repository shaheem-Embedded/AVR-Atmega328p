/*
 * adc.c
 *
 * Created: 30-Apr-26 6:54:54 PM
 *  Author: SHAHEEM
 */ 
#include "adc.h"
#include<avr/io.h>

void adc_init(void)
{
	//Set ref voltage 1.1v
	ADMUX |= ((1<<REFS1) | (1<<REFS0));
	//ADC enable
	ADCSRA |= (1<<ADEN);
	Set clock_freq:prescalar 128khz
	ADCSRA |= ((1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0));
	
	
	
}
//Read ADC value;
	uint16_t read_adc(uint8_t channel)
	{
		channel &= 0x07;
		ADMUX = (ADMUX & 0XF0)|channel;
		ADCSRA = (1<<ADSC);
		
		
	}