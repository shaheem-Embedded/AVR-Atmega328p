/*
 * Avr_LCD_Interface.c
 *
 * Created: 04-Jun-26 6:28:33 PM
 * Author : SHAHEEM
 */


int main(void)
{
	lcd_init();
	lcd_set_cursor(0, 0);
	lcd_print_string("Bismillah");
    /* Replace with your application code */
   while (1)
   {
	   float a=25.45;
	   lcd_set_cursor(1, 0);
	   lcd_print_float(a);
   }
}
