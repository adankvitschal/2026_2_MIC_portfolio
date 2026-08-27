/*
 * main.c
 *
 * Created: 8/27/2026 8:25:01 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include <stdint.h>
#include "util/delay.h"

//Controle de vários LEDs com operações de shift

void GPIO_config() {
	DDRB = (1<<DDB6)|(1<<DDB4)|(1<<DDB2)|(1<<DDB0); //Bits pares são configurados como saída
	//DDRB = 0b01010101;
}

int main(void) {
	GPIO_config();
	uint8_t tData = 0x03; //0b0000 0011
	while(1) {
        PORTB = tData;
		_delay_ms(1000);
		tData = tData << 1; //0b0000 0110, 0b0000 1100, 0b0001 1000, ...
		if(tData == 0) {
			tData = 0x03;
		}
    }
}