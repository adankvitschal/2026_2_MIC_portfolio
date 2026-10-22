/*
 * main.c
 *
 * Created: 10/22/2026 10:50:58 AM
 *  Author: Adan Kvitschal
 */ 

#include <xc.h>
#include "avr/interrupt.h"

uint16_t	gMilliseconds	= 0;
uint8_t		gClockSeconds	= 0;
uint8_t		gClockMinutes	= 0;
uint8_t		gClockHours		= 0;

//Objetivo: Obter uma interrupção com período de 10ms
ISR(TIMER0_COMPA_vect) { //Interrupção de comparação A do timer 0
	gMilliseconds += 10;
}

void TMR0_config() {
	TCCR0A = (1<<WGM01)|(0<<WGM00); //Configuração no modo CTC
	TCCR0B = (0<<WGM02)|(1<<CS02)|(0<<CS01)|(1<<CS00);
	OCR0A  = 155; //Corresponde a 9,984ms
	TIMSK0 = (1<<OCIE0A); //Habilita interrupção COMPA
}

int main(void) {
	DDRB |= (1<<DDB0); //PORTB0 como saída
	TMR0_config();
	sei();
    while(1) {
		//Led blink não bloqueante
		if(gMilliseconds < 100) {
			PORTB |= (1<<PORTB0);	//Seta PB0 por 100ms
		} else {
			PORTB &= ~(1<<PORTB0);	//Zera PB0 por 900ms
		}
		//Lógica do RTC (Real Time Clock)
        if(gMilliseconds >= 1000) {
	        gMilliseconds -= 1000;
	        gClockSeconds++;
	        if(gClockSeconds >= 60) {
		        gClockSeconds = 0;
		        gClockMinutes++;
		        if(gClockMinutes >= 60) {
			        gClockMinutes = 0;
			        gClockHours++;
			        if(gClockHours >= 24) {
				        gClockHours = 0;
			        }
		        }
	        }
        }
    }
}