/*
 * Uart_communication.c
 *
 * Created: 02-Jun-26 7:41:53 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "uart.h"
#include "timer_1.h"

char data = 'H';
int main(void)
{
	DDRB |= (1<<DDB5);
    /* Replace with your application code */
    uart_init();
	timer_1_enable();
    while (1)
    {
			transmit_string("Hello Shaheem\n");
			//transmit_data('\n');
    }
}

