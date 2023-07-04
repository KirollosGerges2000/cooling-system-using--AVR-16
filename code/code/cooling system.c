/*
cooling system.c
 *
 * Created: 6/26/2023 2:10:10 PM
 * Author : Kirollos Gerges
 */ 

#include <avr/io.h>  //  input,output for avr library 
#include "lcd.c"    //  lcd library
#include "ADC.c"   //  ADC library
#include "Motors.c"   //  controlling motors library
volatile int volt=0; // init volatile for volt  
float x=0;  //init for temp value 
float y=0;   //init for input PWM value
float z=0;   //init for input rpm value 
/* the main function to implement process*/
int cooling_system(void)
{
  LCD_Init(); // initialize LCD driver 
  ADC_init(); // initialize ADC driver 
  LCD_Clear();  // clear LCD at the beginning 
  //super loop for repeating cycles
    while (1) 
    {
		display();  //for executing lcd  to display data to user.
motors(y);  //for control speed of motors according to temperature.
				}
 }
 
 
 /* function for implement process of ADC by some equations */
 int input_volt(void)
 {
	 volt = ADC_readChannel(0); // read channel two where the temp sensor is connect
	 x=(float)(5*volt)/1023; // to gain the ADC of temperature reading
	 x=x*100;   // out of Temp equation
	 y=x*1.7;  // out of PWM  equation
	 z=(float)(820*(y/255)); // to gain the ADC of encoder reading
	 z=z/10;// out of rpm equation
	 /* for animations of lcd */
	 if(x>100)
	 {
		 LCD_xy(1,2);
		 LCD_String("rpm");
		 LCD_xy(1,10);
		 LCD_String("C");
		 LCD_String_xy (0,5,"|");
		 LCD_String_xy (1,6,"|");
		 LCD_String_xy (0,11,"|");
		 LCD_String_xy (1,11,"|");
	 }
	 else if (x<=100 )
	 {
		 LCD_xy(1,2);
		 LCD_String("rpm");
		 LCD_xy(1,9);
		 LCD_String("C");
		 LCD_String_xy (0,5,"|");
		 LCD_String_xy (1,5,"|");
		 LCD_String_xy (0,11,"|");
		 LCD_String_xy (1,10,"|");
	 }
	 
 }
 
/* function for display data for user */
void display(void)
{
	LCD_Init();
	
	LCD_String("SX10  Temp ");
	LCD_Command(0xC0);  // start cursor from second line

	LCD_xy(1,0);
	lcd_into_string(z);  // display value of rpm on lcd
	LCD_xy(1,7);
	lcd_into_string(x);  // // display value of temperature on lcd
	input_volt();
	LCD_String_xy (0,12,"Cool");
	LCD_String_xy (1,12,"Syst");
}

