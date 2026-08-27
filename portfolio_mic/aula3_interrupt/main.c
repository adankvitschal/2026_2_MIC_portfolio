/*
 * main.c
 *
 * Created: 8/27/2026 10:25:11 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

//Configuração da Interrupção Externa (INT0/INT1)

ISR(INT0_vect) { //Função no vetor de interrupção INT0
	PORTB |= (1<<PORTB1);	//Acende led em PB1
	_delay_ms(50);
	PORTB &= ~(1<<PORTB1);	//Apaga led em PB1
}

ISR(INT1_vect) { //Função no vetor de interrupção INT1
	PORTB |= (1<<PORTB1);	//Acende led em PB1
	_delay_ms(100);
	PORTB &= ~(1<<PORTB1);	//Apaga led em PB1
}

void INT_config() {
	EICRA = (1<<ISC11)|(1<<ISC10)	//configura INT1 na borda de subida
		  | (1<<ISC01)|(0<<ISC00);	//configura INT0 na borda de descida
	EIMSK = (1<<INT1)|(1<<INT0);	//Habilita INT0 e INT1
}

void GPIO_config() {
	DDRB |= (1<<DDB0);	// Pino PB0 como saída
	DDRB |= (1<<DDB1);	// Pino PB1 como saída
}

int main(void) {
	GPIO_config();
	INT_config();
	sei(); // Habilita Interrupções globalmente
    while(1) {
		_delay_ms(100);
        PORTB ^= (1<<PORTB0); //alterna pino PB0
    }
}