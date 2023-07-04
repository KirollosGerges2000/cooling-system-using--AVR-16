/*
 * control motor with PWM.c
 *
 * Created: 6/24/2023 3:15:35 PM
 * Author : kerollos
 */ 
#define F_CPU 16000000UL  // declaration for crystal frequency  

/*function for controlling speed of fan by PWM*/
int motors(unsigned char j)
{
	DDRB|=(1<<1);  //Define as Pin 1 of input_Driver
	DDRB|=(1<<2);  //Define as Pin 2 of input_Driver
 PORTB=0x02; //init to powered motor
PWM(j); //  controlled duty cycle by Temperature sensor
}

/*FUNCTION FOR PWM TO CONTROL Fan  with variable speeds*/
void PWM(unsigned char i)
{
DDRB|=(1<<3);  //PB3 Enable of PWM "OCR0"
OCR0=i;    //for duty cycle 
TCCR0=0x61;   // phase correct PWM 
}



/*ISR(INT0_vect)  // Interrupt Function
{
i=i+10;	
}

void  Timer0_PWM_Init(unsigned int value)
{
	TCCR0=0x6A;   // fast PWM TCCR0=0x6A
DDRC=DDRC|(1<<0);  //Define as PORT C as an output port
	OCR0=value;
}
*/