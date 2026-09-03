/*
 * main.c
 *
 * Created: 9/3/2026 8:56:23 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

void GPIO_config() {
	DDRB  &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)); // Portas PB0,PB1,PB2,PB3 como entrada
	PORTB |= (1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3); //Habilita pullup nos pinos PB0,PB1,PB2,PB3
	//DDRD  = 0xff; //Seta tudo mundo como saída na porta D, mesmo que 0b11111111
	DDRD  |= (1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)
		  |  (1<<DDD4)|(1<<DDD5)|(1<<DDD6)|(1<<DDD7); // configura PD0,PD1,PD2,PD3,PD4,PD5,PD6,PD7 como saídas
	DDRC  |= (1<<DDC0); //Pino PC0 como saída
}

void GPIO_incBar() {
	PORTD = PORTD >> 1;
	PORTD |= 0b10000000; //Aciona bit mais significativo
}

void PCINT_config() {
	PCICR  |= (1<<PCIE0); //Habilita grupo PCINT0-PCINT7
	PCMSK0 |= (1<<PCINT3)|(1<<PCINT2)|(1<<PCINT1)|(1<<PCINT0); //Habilita interrupção PCINT0-PCINT3
}

ISR(PCINT0_vect) {
	PORTC |= (1<<PORTC0);	//seta pino PC0
	_delay_ms(100);
	PORTC &= ~(1<<PORTC0);	//zera pino PC0
	GPIO_incBar();
}

int main(void) {
	GPIO_config();
	PCINT_config();
	sei();
    while(1) {
        //TODO:: Please write your application code 
    }
}