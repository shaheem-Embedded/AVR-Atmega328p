/*
 * Timer0_Phase_correct_PWM.cpp
 *
 * Created: 17-Apr-26 10:42:17 PM
 * Author : SHAHEEM
 */
#include <avr/io.h>
#include <util/delay.h>

#define STATUS_LED      PORTB0 
#define PL              PORTB1
#define M1              PORTC0
#define M2              PORTC1


#define Speed_switch     PORTD0
#define Direction_switch PORTD1 
#define Power_switch     PORTD2 

#define F_CPU 16000000UL

typedef enum
{
	STOP,
	FORWARD,
	REVERSE,
	DUTY_CYCLE0,
	DUTY_CYCLE1,
	DUTY_CYCLE2,
	DUTY_CYCLE3,
	DUTY_CYCLE4,
}Control_t;

Control_t STATE;
int duty =0;

// Global Flags
int count      = 0;
int power_flag = 0;
int dir_flag   = 0; // 0 for Forward, 1 for Reverse

void phase_correct_pwm_init() 
{
	//Configure (Enable as 0) Power saver mode for Timer 0;
    PRR &= ~(1<<PRTIM0);
	//Clear OC0A on compare match when up-counting. Set OC0A on compare match when down-counting.;(Non inverting)
	TCCR0A &= ~(1<<COM0A0);
	TCCR0A |=  (1<<COM0A1);
	//Configure Waveform generation for phase correct PWM mode of operation.(TOP=0XFF)
	TCCR0A |= (1<<WGM00);
	TCCR0B &= ~(1<<WGM01|1<<WGM02);
	//Configure prescalar Bits for 8 prescalar value.
	TCCR0B&=~(1<<CS00 | 1<<CS02);
	TCCR0B |=(1<<CS01);
    //Configure OC0A as output
    DDRD |= (1<<DDD6);                 // PWM Pin Output
	
	//	--------------------------------------------------------------------------------------
	/*Calculate % Duty cycle requirements.
	
	  Duty cycle =   Tonx100/Time period :(Time period = Ton + Toff)
	  
	  Duty cycle % = OCR0x X 100/(2xTOP)
	            i.e OCR0x = (Duty cycle x 255)/100   :( Here top value is 0XFF -255)
				    OCR0x =  50 x (255)/100
					OCR0x = 128.
	--------------------------------------------------------------------------------------
	Frequency of PWM Wave signal at OC0A Pin calculation:
	PWM frequency = fclk/N(510)  
	              = 16x10^6/(8x510)  -Prescalar value 8.
				  = 3.92Khz.(Suitable for Motor)
   ----------------------------------------------------------------------------------------*/
  // OCR0A = 255;         //Value to be loaded IN OCR0x for phase correct PWM signal with 50% duty cycle.				
}


void switch_status()
{
	if(!(PIND & (1<<PIND2)))
	{
		power_flag ^= 1;
		while(!(PIND & (1<<PIND2)));
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(100);
		PORTB &=~(1<<PB0);
		
	}
	if(!(PIND & (1<<PIND1)))
	{
		dir_flag ^= 1;
		while(!(PIND & (1<<PIND1)));
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(100);
		PORTB &=~(1<<PB0);
	}
	if(!(PIND & (1<<PIND0)))
	{
		while(!(PIND & (1<<PIND0)));
		_delay_ms(50);
		count ++;
		if(count>5)
		count=0;
		_delay_ms(50);
		PORTB |= (1<<PB0);
		_delay_ms(100);
		PORTB &=~(1<<PB0);
	}
}

void switch_update()
{
	if((power_flag)==0)
	{
		STATE = STOP;
	}
	else
	{
		if((dir_flag)==0)
		{
			STATE = FORWARD;
		}
		else
		{
			STATE = REVERSE;
		}
	}
	if (count==1) duty = 0;
	if (count==2) duty = 30;
	if (count==3) duty = 100;
	if (count==4) duty = 150;
	if (count==5) duty = 255;
}

void motor_control()
{
	switch(STATE)
	{
			case STOP:
			PORTC &= ~(1<<PC0);
			PORTC &= ~(1<<PC1);
			count=0;
			break;
			
			case FORWARD:
			PORTC |= (1<<PC0);
			PORTC &= ~(1<<PC1);
			break;
			
			case REVERSE:
			PORTC |= (1<<PC1);
			PORTC &= ~(1<<PC0);
			break;
	}
	OCR0A = duty;
}

int main()
{
	DDRB |= (1<<DDB0 | 1<<DDB1); // Configure LED as ports as output.
	DDRC |= (1<<DDC0 | 1<<DDC1); // Configure Motor as ports as output.
	DDRD &= ~(1<<DDD0| 1<<DDD1 |1<<DDD2);//Configure Switches as input.
	PORTD |= (1<<PD0 | 1<< PD1 |1<<PD2);//Enable internal pull up configurations for Input switches.
	
	_delay_ms(10);
	PORTB |= (1<<PB1);
    phase_correct_pwm_init();
	while(1)
	{
		switch_status();
		switch_update();	
		motor_control();
	}
}


































//
//
//
//void switch_status_check() {
    //// Power Switch
    //if(!(PINB & (1<<Power_switch))) {
        //_delay_ms(20); // Debounce
        //power_flag = !power_flag;
        //while(!(PINB & (1<<Power_switch))); 
    //}
    //
    //// Direction Switch
    //if (!(PIND & (1<<Direction_switch))) {
        //_delay_ms(20);
        //dir_flag = !dir_flag;
        //while(!(PIND & (1<<Direction_switch)));
    //}
//
    //// Speed Switch
    //if(!(PINB & (1<<Speed_switch))) {
        //_delay_ms(20);
        //count++;
        //if (count > 4) count = 0;
        //while(!(PINB & (1<<Speed_switch)));
    //}
//}
//
//void device_control() {
    //if (!power_flag) {
        //PORTD &= ~((1<<PORTD1) | (1<<PORTD2)); // Stop motor
        //OCR0A = 0;
        //PORTD &= ~(1<<STATUS_LED);
        //return;
    //}
//
    //PORTD |= (1<<STATUS_LED); // System ON
//
    //// Handle Direction
    //if(dir_flag == 0) {
        //PORTD |= (1<<PORTD1); PORTD &= ~(1<<PORTD2);
    //} else {
        //PORTD |= (1<<PORTD2); PORTD &= ~(1<<PORTD1);
    //}
//
    //// Handle Speed (PWM)
    //switch (count) {
        //case 0: OCR0A = 0;   break;
        //case 1: OCR0A = 64;  break;  // ~25%
        //case 2: OCR0A = 127; break;  // ~50%
        //case 3: OCR0A = 191; break;  // ~75%
        //case 4: OCR0A = 255; break;  // 100%
    //}
//}
//
//int main(void) {
    //// Setup I/O
    //DDRD |= (1<<DDD6) | (1<<DDD4) | (1<<DDD1) | (1<<DDD2);
    //DDRB &= ~((1<<Power_switch) | (1<<Speed_switch));
    //PORTB |= (1<<Power_switch) | (1<<Speed_switch); // Pull-ups
    //PORTD |= (1<<Direction_switch);
//
    //phase_correct_pwm_init();
//
    //while (1) {
        //switch_status_check();
        //device_control();
    //}
//}
//
//
//
//
//
///*
 //* Timer_phase_correct _PWM.cpp
 //*
 //* Created: 12-Apr-26 3:36:21 PM
 //* Author : SHAHEEM
 //*/
//
//#include <avr/io.h>
//#include <util/delay.h>
//
//
//#define Power_switch PB7 
//#define Speed_switch PB6
//#define Direction_switch PD3
//#define STATUS_LED PD4 
//
//#define F_CPU 16000000UL
//void phase_correct_pwm_init();
//void speed_selection();
//void power_check();
//
//typedef enum
//{
	//STOP,
	//FORWARD,
	//REVERSE,
	//DUTY_CYCLE_25,
	//DUTY_CYCLE_50,
	//DUTY_CYCLE_75,
	//DUTY_CYCLE_100,
//}State_t;
//State_t CURRENT_STATE=STOP;
//
//int count=0;int flag=0;
//int power_flag;
//int Direction_flag;
//
//void phase_correct_pwm_init();
//void switch_status_check();
//void switch_status_update();
//void device_control();
//
//
    ///* Replace with your application code */
	//void phase_correct_pwm_init()
    //{
	////Configure (Enable as 0) Power saver mode for Timer 0;
	//PRR &=~(1<<PRTIM0);
	////Clear OC0A on compare match, set OC0A at BOTTOM,(non-inverting mode);
	//TCCR0A &=~(1<<COM0A0);
	//TCCR0A |= (1<<COM0A1);
	////Configure Waveform generation for phase correct PWM mode of operation.
	//TCCR0A |= (1<<WGM00);
	//TCCR0B &= ~(1<<WGM01 | 1<<WGM02);
	////Configure prescalar Bits for 8 prescalar value.- 4Khz (Suitable for motor frequency is- 1Khz to 20 Khz)
	//TCCR0B &=~(1<<CS00| 1<<CS02);
	//TCCR0B |= (1<<CS01);
	////Configure OC0A as output:PORTD6.
////	--------------------------------------------------------------------------------------
	///*Calculate % Duty cycle  requirements.
	//
	  //Duty cycle =   Tonx100/Time periode :(Time Periode = Ton + Toff)
	  //
	  //Duty cycle % = OCR0x X 100/(TOP+1)
	            //i.e OCR0x = Dutycyclex(TOP+1)/100   :( Here top value is 0XFF -255)
				    //OCR0x =  50 x 510/100
					//OCR0x = 255.
	//--------------------------------------------------------------------------------------
	//Frequency of PWM Wave signal at OC0A Pin calculation:
	//PWM frequency = fclk/NX510  
	              //= 16x10^6/(8x510)
				  //= 3.92khz ==4khz.(Suitable for motor)
   //----------------------------------------------------------------------------------------*/
   //// OCR0A = 255;         //Value to be loaded IN OCR0x for Fast PWM signal with 50% duty cycle.
   ////Set as output OC0A pin to act as output.
					//
    ///* Replace with your application code */	
    //}
	//
//void switch_status_check()
//{
	//if(!(PINB & (1<<Power_switch)))
	//{
		//power_flag=!power_flag;
		//while(!(PINB & (1<<Power_switch)));
		//_delay_ms(50);
	//}
	//if (!(PIND & (1<<Direction_switch)))
		//{
			//Direction_flag=!Direction_flag;
			//while(!(PIND & (1<<Direction_switch)));
				//_delay_ms(50);
		//}
	//if(!(PINB & (1<<Speed_switch)))
		//{
			//count ++;
			//while(!(PINB & (1<<Speed_switch)));
			//_delay_ms(50);
			//if (count == 5)
			//{
				//CURRENT_STATE =STOP;
				//count=0;
			//}
			//else
			//{
				//if (count == 1)
				//{
					//CURRENT_STATE = DUTY_CYCLE_25;
				//}
				//if (count == 2)
				//{
					//CURRENT_STATE = DUTY_CYCLE_50;
				//}
				//if (count == 3)
				//{
					//CURRENT_STATE = DUTY_CYCLE_75;
				//}
				//if (count == 4)
				//{
					//CURRENT_STATE = DUTY_CYCLE_100;
				//}
			//}
		//}
//}
//void switch_status_update()
//{
	//if(power_flag==0)
	//{
		//CURRENT_STATE =STOP;
	//}
	//else
	//{
		//if(Direction_flag ==1)
		//{	
			//CURRENT_STATE = FORWARD;
//
		//}
		//else if(Direction_flag ==0)
		//{
			//CURRENT_STATE = REVERSE;
//
		//}
	//}	
//}
//void device_control()
//{
//switch (CURRENT_STATE)
//{
	//case STOP:
	//PORTD &= ~(1<<PD1);
	//PORTD &= ~(1<<PD2);
	//break;
	//case FORWARD:
	//PORTD |= (1<<PD1);
	//PORTD &= ~(1<<PD2);
	//break;
	//case REVERSE:
	//PORTD |= (1<<PD2);
	//PORTD &= ~(1<<PD1);
	//break;
	//case DUTY_CYCLE_25:
	//OCR0A = 30;  
	//break;
	//case DUTY_CYCLE_50:
	//OCR0A = 100; 
	//break;
	//case DUTY_CYCLE_75:
	//OCR0A = 180; 
	//break;
	//case DUTY_CYCLE_100:
	//OCR0A = 255;
	//break;
//}
//}
//
//int main(void)
//{
	//DDRD |= (1<<DDD6|1<< DDD4|1<<DDD1|1<<DDD2); //Configure OC0A,Status LED,Motor O/p;
	//DDRD &= ~(1<<Direction_switch); //Switches configured as input;
	//DDRB &=~(1<<Speed_switch|1<<Power_switch);//Configure Switches;
	//PORTB |= (1<< Power_switch|1<<Speed_switch); //Enable Pull up;
	//PORTD |= (1<<Direction_switch); //Enable Pull up;
	//phase_correct_pwm_init();
	////Motor output initialization
    //
	//while (1)
	//{
	//switch_status_check();
	//switch_status_update();
	//device_control();
	//}
//}
