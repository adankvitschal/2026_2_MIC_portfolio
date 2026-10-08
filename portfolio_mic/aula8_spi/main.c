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
#include "sm28vlt32.h"

int main(void) {
	SPI_master_config();
	SM28VLT32_config();
    while(1) {
        uint16_t tMemoryData = SM28VLT32_readWord(1000);
		_delay_ms(1);
    }
}