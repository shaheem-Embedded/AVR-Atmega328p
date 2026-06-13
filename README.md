__1__. **Blink LED code:** 
       Scope covered:  >>Accessing GPIO of microcontroller.
                       >Led as ouput device.
                       >Switch as Input device.
__2__.**Motor Driver:**
       Scope covered:  >>Accessing GPIO of microcontroller.
                       >Enable Pull-up & Pull down configurations in Atmega328p.
                       >Implemented State machine logic algorithm for Motor control.






3.**Timer 1 -64 prescalar With Overflow Interrupt**.
4.**Uart communication** 
  Implemneted UART trasmission data to serial monitor using "Asynchronous,No parity,1 stop bit" Based String transfer/9600 baud rate.
5.
6. **AVR atmega328p Based Temperature Measurement (LM35 Sensor)**
  1.Implemented Temperature Reading & measurement using LM35 sensor and converted to degree celsius.
  2. Implemented Dual Output - Using LCD and Using UART and displayed in System Serial monitor(Using arduino IDE)
  3.Implemented Status LED indicator - I have used Timer 1 INTERRUPT SERVICE routine for 0.5 sec delay (hence avoided loop delay imperfection in while loop during      the main code execution ,I used this to make sure that status LED code is independent of main code)
  4. I added  threshold level checking of different levels of Temperature measurement and implemented Different stages of indications on LCD.
  5. If Temp >50 - Alarming Temp. (Warning LED blinks)
  6. If Temp <50 and >40 - Temp Reducing 
  7. If Temp <40 and >30 - Normal Temp.(Warning LED Turned OFF)
  8. If Temp <30 - Atmospheric temp.

                 
                 
