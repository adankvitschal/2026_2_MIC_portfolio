/*
 * main.c
 *
 * Created: 8/27/2026 8:25:01 AM
 *  Author: Adan Kvitschal
 */ 

#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"

#define BIT0_MASK 0b00000001
#define BIT1_MASK 0b00000010
#define BIT2_MASK 0b00000100
#define BIT5_MASK 0b00100000

int main(void) {
	// Três formas diferentes de setar a direção de PB2 e PB5
	
	//Forma 1: shifts com definições do fabricante
	DDRB = (1<<DDB5)|(1<<DDB2);
	
	//Forma 2: Binário puro
	DDRB = 0b00100000
		 | 0b00000100;
	// res 0b00100100
	
	//Forma 3: Máscaras e diretivas de pré-processador
	DDRB = BIT5_MASK | BIT2_MASK;
	
    while(1) {
        //TODO:: Please write your application code 
    }
}