/*
 * spi.h
 *
 * Created: 08/10/2026 10:38:40
 *  Author: Aluno
 */ 


#ifndef SPI_H_
#define SPI_H_

void SPI_master_config();
uint8_t SPI_transceive(uint8_t pTxByte);

#endif /* SPI_H_ */