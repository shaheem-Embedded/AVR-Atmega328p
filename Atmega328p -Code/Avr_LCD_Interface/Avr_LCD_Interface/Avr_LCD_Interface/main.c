/*
 * Avr_LCD_Interface.c
 *
 * Created: 04-Jun-26 6:28:33 PM
 * Author : SHAHEEM
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <util/delay.h>
#include "Avr_LCD_Interface.h"

int main(void)
{
	lcd_init();
	lcd_set_cursor(0, 0);
	lcd_print_string("Atmos.Temp:");
	   float a=25.45;
	   lcd_set_cursor(1, 0);
	   lcd_print_float(a);
	   lcd_data(0xDF);
	   lcd_print_string("C");
	   
    /* Replace with your application code */
       while (1)
       {
	    /*   // Move text from left to right across the 16-character screen
	       for (int i = 0; i < 16; i++)
	       {
		       lcd_set_cursor(0, 0);
		       
		       // 1. Print spaces to push the text to the right
		       // 2. Print your text
		       // 3. Fill the rest of the line with spaces to erase leftover letters
		       for (int space = 0; space < i; space++)
		       {
			       lcd_print_string(" ");
		       }
			  lcd_print_string("Bismillah");
			   for (int clear = 0; clear < (10 - i); clear++)
			   {
				   lcd_print_string(" ");
			   }
		       _delay_ms(250); // Control the scroll speed
	       }
		   }*/
}
}
