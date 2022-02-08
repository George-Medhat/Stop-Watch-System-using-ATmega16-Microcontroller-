/*
 * main.c
 *
 *  Created on: Jan 17, 2022
 *      Author: dell
 */


#include"fn.h"

int main(void){
	SREG &= ~(1<<7); /* Disable global interrupts in MC */
	Timer1_CTC_init();
	Pins_init();
	SREG |= (1<<7); /* Enable global interrupts in MC */

	while(1){
		for(int i=0;i<DIGITS_NUM;i++){

			PORTA=(PORTA & 0xC0) | ((1<<i) & 0x3F);
			PORTC=(PORTC & 0xF0) | (curr_digit[i] & 0x0F);
			_delay_ms(1);
		}

	}



	return 0;
}
