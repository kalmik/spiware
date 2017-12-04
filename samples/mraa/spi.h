#ifndef SPI_H
#define SPI_H

#include <stdio.h>
#include <stdlib.h>
#include "mraa.h"
#include "atmega328p.h"

#define RM1_SS 7
#define WM1_SS 8 
#define RWM2_SS 4
#define RWM3_SS 2

/*SLAVE COMMANDS*/


class SPI
{
public:
	SPI();
	SPI(int freq);
	~SPI();
	void init(int freq);
	
	mraa_gpio_context addSlave(unsigned char port);
	mraa_gpio_context getSlaveContext(unsigned char port);
	void setFrequency(int freq);
	int getFrequency();
	int writeByte(unsigned char buffer, mraa_gpio_context addr);
	int sendCommand(unsigned char command, mraa_gpio_context addr);
	int getADC(unsigned char index, mraa_gpio_context addr);
	int getDigital(unsigned char index, mraa_gpio_context addr);
	int readByte(unsigned char signal, mraa_gpio_context addr);
	unsigned char getSlavePort(mraa_gpio_context index);
	unsigned char getSizeSlave();

private:
	mraa_spi_context spi;
	int frequency;
	mraa_gpio_context slave[10];
	unsigned char sizeSlave;
};


#endif /* SPI_H */
