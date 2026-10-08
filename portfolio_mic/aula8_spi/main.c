/*
 * main.c
 *
 * Created: 10/8/2026 8:48:55 AM
 *  Author: Adan Kvitschal
 */ 
#define F_CPU 16000000
#include <xc.h>
#include "util/delay.h"
#include "spi.h"

int main(void) {
	SPI_master_config();
    while(1) {
        SPI_transceive(0x45);
		_delay_ms(1);
    }
}