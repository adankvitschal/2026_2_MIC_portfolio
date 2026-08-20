/*
 * main.c
 *
 * Created: 8/20/2026 8:58:53 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

int main(void) {
	DDRB |= 0b00100000; //Define pino PB5 como saída
	DDRD &= 0b11110111; //Define pino PD3 como entrada
    while(1) {
		if((PIND & 0b00001000) != 0) { //Ler valor da chave PD3, segue se estiver em nível lógico alto
			PORTB |= 0b00100000; //Atribui nível lógico alto ao pino PB5
			_delay_ms(100);
			PORTB &= 0b11011111; //Atribui nível lógico baixo ao pino PB5
			_delay_ms(900);
		}
    }
}