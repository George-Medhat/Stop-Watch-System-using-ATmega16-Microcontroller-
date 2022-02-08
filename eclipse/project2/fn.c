/*
 * fn.c
 *
 *  Created on: Jan 17, 2022
 *      Author: dell
 */
#include"fn.h"




unsigned char curr_digit[DIGITS_NUM]={0};


void Timer1_CTC_init(void){

	TCCR1A=(1<<FOC1A);
	TCCR1B=(1<<WGM12) | (1<<CS12) | (1<<CS10); //CTC with clk/64

	TCNT1=0;
	OCR1A=1000;			// every 1 sec
	TIMSK |= (1<<OCIE1A); //Enable timer1 interrupt


}

void Pins_init(void){
	//Outputs to 7447 decoder
	DDRC |= 0x0F;       //first 4 pins output
	PORTC &= 0xF0;		//clear them

	//Enables and disables of six 7 segments
	DDRA |= 0x3F;       //first 6 pins output
	PORTA &= 0xC0;		//clear them

	//INT0 FALLING EDGE
	DDRD &= ~(1<<PD2);       //setting pin as input
	PORTD |= (1<<PD2);		//INTERNAL PULL UP
	MCUCR |=(1<<ISC01);     // interrupt at falling edge

	//INT1 RAISING EDGE
	DDRD &= ~(1<<PD3);       //setting pin as input
	MCUCR |=(1<<ISC10) | (1<<ISC11);     // interrupt at RAISING edge

	//INT2 FALLING EDGE
	DDRB &= ~(1<<PB2);       //setting pin as input
	PORTB |= (1<<PB2);		//INTERNAL PULL UP
	MCUCSR &= ~(1<<ISC2);     // interrupt at falling edge

	GICR |= (1<<INT0) | (1<<INT1) | (1<<INT2) ; //Enabling Int0,1,2
}

ISR(TIMER1_COMPA_vect){
//increment timer
	for(int i=0;i<DIGITS_NUM;i++){

		if(curr_digit[i]<9){
			curr_digit[i]++;
			break;
		}
		else {
			curr_digit[i]=0;
		}
	}
}



ISR(INT0_vect){
//RESET time
	for(int i=0;i<DIGITS_NUM;i++){
		curr_digit[i]=0;
	}

}


ISR(INT1_vect){


	TCCR1B &= ~(1<<CS12) & ~(1<<CS10); //disabling clock To Pause


}
ISR(INT2_vect){


	TCCR1B |=(1<<CS12) | (1<<CS10);	//Enabling clock To Resume


}
