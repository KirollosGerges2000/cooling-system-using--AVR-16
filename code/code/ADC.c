#include "ADC.h"

void ADC_init(void)
{
	/* ADMUX Register Bits Description:
	 * REFS1:0 = 00 to choose to connect external reference voltage by input this voltage through AREF pin
	 * ADLAR   = 0 right adjusted
	 * MUX4:0  = 00000 to choose channel 0 as initialization
	 */
	ADMUX = 0x00;

	/* ADCSRA Register Bits Description:
	 * ADEN    = 1 Enable ADC
	 * ADIE    = 0 Disable ADC Interrupt
	 * ADPS2:0 = 011 to choose ADC_Clock=F_CPU/8=1Mhz/8=125Khz --> ADC must operate in range 50-200Khz
	 */
	ADCSRA = (1<<7) | (1<<1) | (1<<0);


}

unsigned short ADC_readChannel(unsigned char channel_num)
{
//	channel_num &= 0x07; /* channel number must be from 0 --> 7 */
	ADMUX &= 0xE0; /* clear first 5 bits in the ADMUX (channel number MUX4:0 bits) before set the required channel */
	ADMUX = ADMUX | channel_num; /* choose the correct channel by setting the channel number in MUX4:0 bits */
	SET_BIT(ADCSRA,6); /* start conversion write '1' to ADSC */
//	ADCSRA |= (1<<ADSC);
	while(BIT_IS_CLEAR(ADCSRA,4)); /* wait for conversion to complete ADIF becomes '1' */
	SET_BIT(ADCSRA,4); /* clear ADIF by write '1' to it :) */
	return ADC; /* return the data register */
}
