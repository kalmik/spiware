#include "spi.h"

SPI::SPI()
{
	printf("SPI Initialized\n");
}

SPI::~SPI()
{
	mraa_spi_stop(spi);
}

SPI::SPI(int freq)
{
	init(freq);
}

void SPI::init(int freq)
{
	spi = mraa_spi_init(0);
	frequency = freq;
	sizeSlave = 0;
	mraa_spi_frequency(spi, frequency);
}

void SPI::setFrequency(int freq)
{
	frequency	= freq;
}

int SPI::getFrequency()
{
	return frequency;
}

mraa_gpio_context SPI::addSlave(unsigned char port)
{
    slave[sizeSlave] = mraa_gpio_init(port);
    mraa_gpio_dir(slave[sizeSlave], MRAA_GPIO_OUT);
    mraa_gpio_write(slave[sizeSlave], 1);

    return slave[sizeSlave++];
}

unsigned char SPI::getSlavePort(mraa_gpio_context index)
{
	return mraa_gpio_get_pin(index);
}

int SPI::writeByte(unsigned char buffer, mraa_gpio_context addr)
{
	mraa_gpio_write(addr,0);
	int recv = mraa_spi_write(spi, buffer);
	mraa_gpio_write(addr,1);
	return recv;
}

int SPI::readByte(unsigned char signal, mraa_gpio_context addr)
{
	writeByte(0x00, addr); //clear buffer
	writeByte(signal, addr);
	return writeByte(0, addr);
}

int SPI::sendCommand(unsigned char command, mraa_gpio_context addr)
{
	writeByte(0x00, addr); //clear buffer
	return writeByte(command, addr);
}

int SPI::getADC(unsigned char index, mraa_gpio_context addr)
{
	writeByte(0x00, addr); //clear buffer
	writeByte(ANALOG | index, addr); //preparation
	return writeByte(ANALOG | index, addr);	
}
int SPI::getDigital(unsigned char index, mraa_gpio_context addr)
{
	writeByte(0x00, addr); //clear buffer
	writeByte(index, addr); //preparation
	return writeByte(index, addr);	
}

mraa_gpio_context SPI::getSlaveContext(unsigned char _port)
{
	int i = 0;
	unsigned char port;
	for(i; i < sizeSlave; i++){
		port = getSlavePort(slave[i]);
		if(port == _port){
			return slave[i];
		}
	}
}

unsigned char SPI::getSizeSlave()
{
	return sizeSlave;
};