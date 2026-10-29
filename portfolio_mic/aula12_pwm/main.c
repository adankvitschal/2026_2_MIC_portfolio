/*
 * main.c
 *
 * Created: 10/29/2026 8:53:38 AM
 *  Author: Adan Kvitschal
 */ 

#include <xc.h>

void PWM_config() {
	TCCR0A	= (1<<COM0A1)|(0<<COM0A0)	// Saída OCR0A não-inversora
			| (1<<COM0B1)|(1<<COM0B0)	// Saída OCR0B inversora
			| (1<<WGM01)|(1<<WGM00);	// Modo Fast PWM
	TCCR0B	= (0<<WGM02)|(0<<CS02)|(0<<CS01)|(1<<CS00);			//Habilita timer com Prescaler de 1x
	OCR0A	= 101;			//Razão de ciclo de 40% em OC0A
	OCR0B	= 76;			//Razão de ciclo de 30% em OC0B
	DDRD	= (1<<DDD6)|(1<<DDD5);	//Configura pinos de saída pwm OC0A e OC0B
}

int main(void) {
	PWM_config();
    while(1) {
        //TODO:: Please write your application code 
    }
}