#include <util/delay.h>  // delay timer library 
#include <stdlib.h>   // std lib library for specific useful keywords
#define LCD_Data_Dir DDRC     //declaration about data pins
#define LCD_Command_Dir DDRB    //declaration about RS
#define LCD_Data_Port PORTC     // PORTC for data 
#define LCD_Command_Port PORTB   //PORTB for commands 
#define RS PB4   //PORTB_PIN4 for Register select
#define RW PB5   //PORTB_PIN5 for Read/Write
#define EN PB6   //PORTB_PIN6 for Enable

/*Function for implementing commands in lcd */

void LCD_Command(unsigned char cmnd)
{
	LCD_Data_Port= cmnd;  // write the command of this function on Data_port
	LCD_Command_Port &= ~(1<<RS);  //active RS for write command
	LCD_Command_Port &= ~(1<<RW);   //active R/W for write command
	LCD_Command_Port |= (1<<EN);    // disable Enable for 1 micro second 
	_delay_us(1);                   // delaying 
	LCD_Command_Port &= ~(1<<EN); //Active Enable 
	_delay_ms(3);                 // delaying
}
/*Function for implementing characters in lcd */
void LCD_Char (unsigned char char_data)
{
	LCD_Data_Port= char_data;  // write the char of this function on Data_port
	LCD_Command_Port |= (1<<RS);//active RS for write command
	LCD_Command_Port &= ~(1<<RW);//active R/W for write command
	LCD_Command_Port |= (1<<EN);// disable Enable for 1 micro second 
	_delay_us(1);   // delaying 
	LCD_Command_Port &= ~(1<<EN);//Active Enable 
	_delay_ms(1); // delaying
}
/*Function for initialization lcd at begaining of executing */
void LCD_Init (void)
{
	LCD_Command_Dir = 0xFF;  // declaration of command_Dir as output 
	LCD_Data_Dir = 0xFF;     // declaration of Data_Dir as output
	_delay_ms(20);           // delaying  
	
	LCD_Command (0x38);  //using 8_bit in Hardware
	LCD_Command (0x0C);   // cursor_off
	LCD_Command (0x80);   // to assign cursor location
	//LCD_Command (0x01);  //to clear
	
}
/*Function for writing string"text" on lcd */
void LCD_String (char *str)
{
	/*Array of char*/
	int i;  //declaration of variable of array
	/* "for loop" for  Array of char to make string */
	for(i=0;str[i]!=0;i++)
	{
		/* function of char implement by "for loop"  to make string"*/
		LCD_Char (str[i]);  
	}
}
/*Function for positioning string (x,y) position with writing "text: on lcd  */
void LCD_String_xy (char row, char pos, char *str)
{    
	/*LCD contains 16 columns , 2 rows*/
	if (row == 0 && pos<16)   //for columns
	LCD_Command((pos & 0x0F)|0x80);  
	else if (row == 1 && pos<16)   //for rows
	LCD_Command((pos & 0x0F)|0xC0);
	LCD_String(str);   //lcd string function  
}
/*Function for clearing all characters on lcd use usually initialization */
void LCD_Clear()
{
	LCD_Command (0x01);   //clearing 
	LCD_Command (0x80);  // to assign cursor location
}
/*Function for writing the variables of program on lcd */
void lcd_into_string(char data)                            
{    /*buff in stdin lib*/
	char buff[16];
	itoa(data,buff,10);
	LCD_String(buff); 
}
/*Function for positioning string (x,y) position only */
void LCD_xy (char row, char pos)
{
	if (row == 0 && pos<16)
	LCD_Command((pos & 0x0F)|0x80);//for columns
	else if (row == 1 && pos<16)
	LCD_Command((pos & 0x0F)|0xC0);//for rows

}