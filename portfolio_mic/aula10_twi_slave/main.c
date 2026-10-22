/*
 * main.c
 *
 * Created: 10/22/2026 8:20:44 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000

#include <xc.h>
#include "avr/interrupt.h"
#include "util/delay.h"

ISR(TWI_vect) {
	PORTB |= (1<<PORTB0);
	//Tratar o estado atual da máquina do TWI
	uint8_t tStatusCode = (TWSR & 0b11111000);
	switch(tStatusCode) {
		case (0x60): { //Recebido SLA+W, início de escrita do mestre
			PORTB |= (1<<PORTB1);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA); //Envio do ACK
		} break;
		case (0x80): { //Novo dado recebido do mestre
			PORTB |= (1<<PORTB2);
			uint8_t tReceivedByte = TWDR; //Recebe o dado enviado pelo mestre
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT)|(1<<TWEA); //Envio do ACK
		} break;
		case (0xA0): { //Final da transmissão (stop condition ou repeated start)
			PORTB |= (1<<PORTB3);
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		} break;
		default: {
			PORTB |= (1<<PORTB4);
			//Algum erro ou condição não tratada
			TWCR = (1<<TWEN)|(1<<TWIE)|(1<<TWINT);
		}
	}
	_delay_ms(1);
	PORTB = 0;
}

void TWI_slave_config(uint8_t pAddress) {
	DDRC &= ~((1<<DDC5)|(1<<DDC4));
	TWBR = 64;						//Divisor 64, fscl=100kHz
	TWSR |= (0<<TWPS1)|(0<<TWPS0);	//Prescaler de 1
	TWAR = pAddress<<1;
	TWCR = (1<<TWEN)|(1<<TWIE);	//Habilita o periférico
	//_delay_ms(100);
	//TWCR = 0;
}

int main(void) {
	DDRB |= (1<<DDB4)|(1<<DDB3)|(1<<DDB2)|(1<<DDB1)|(1<<DDB0); //Saídas para LEDs de sinalização
	TWI_slave_config(10);
	sei();
    while(1) {
        //
    }
}