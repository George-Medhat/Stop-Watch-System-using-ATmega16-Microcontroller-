/*
 * fn.h
 *
 *  Created on: Jan 17, 2022
 *      Author: dell
 */

#ifndef FN_H_
#define FN_H_



#endif /* FN_H_ */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define DIGITS_NUM 6
#define TRUE 1
#define FALSE 0

extern unsigned char curr_digit[DIGITS_NUM];

void Timer1_CTC_init(void);
void Pins_init(void);
