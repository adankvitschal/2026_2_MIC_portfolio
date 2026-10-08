/*
 * main.c
 *
 * Created: 10/8/2026 8:48:55 AM
 *  Author: Adan Kvitschal
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

void SPI_master_config() {
	SPCR = (1<<SPE)|(0<<DORD)	// Habilita SPI, Ordem MSB primeiro (padrão)
		 | (1<<MSTR)			// Modo Mestre
		 | (0<<CPOL)|(0<<CPHA)	// SPI modo 0
		 | (0<<SPR1)|(0<<SPR0);	// Divisor fosc/2, SCK->8MHz
	SPSR = (1<<SPI2X);			// Velocidade dobrada
	DDRB = (1<<DDB3)|(1<<DDB5);	// Config dos pinos MOSI e SCK como saídas
	DDRC = (1<<DDC0);			// USando PC0 como Slave Select (Saída)
	PORTC |= (1<<PORTC0);		// Slave select em nível alto
}

uint8_t SPI_transceive(uint8_t pTxByte) {
	uint8_t tReceivedByte;
	PORTC &= ~(1<<PORTC0);			// Slave select em nível baixo
	SPDR = pTxByte;					// Escrita no SPDR dispara a transação
	while((SPSR & (1<<SPIF)) == 0); // Espera a flag SPIF subir
	tReceivedByte = SPDR;			// Leitura do registrador de dados
	PORTC |= (1<<PORTC0);			// Slave select em nível alto
	return tReceivedByte;
}

int main(void) {
	SPI_master_config();
    while(1) {
        SPI_transceive(0x45);
		_delay_ms(1);
    }
}