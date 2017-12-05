# Protocol 0.1

## Protocol byte frame

|MODE|VALUE   |PORT ADDR                   |PIN ADDR                   |
|----|--------|----------------------------|---------------------------|
|SPI_B7|SPI_B6| SPI_B5 \| SPI_B4 \| SPI_B3 | SPI_B2 \| SPI_B1 \| SPI_B0|

* SPI_B7
    >Indica o modo de acesso ao pino LOW(0) para WRITE, HIGH(1) para READ
* SPI_B6
	> Bit indicando o valor no caso de escrita e no caso de leitura, indida acesso a modulos extras (PWM)
* SPI_B[5-3]
	> Indica o endereço do registrador [ PORT | DDR ]
* SPI_B[2-0]
	> Indica o bit no respectivo registrador.

### PORT mapping (ATMEGA328p only)

|REGISTER | ADDR|
|-----|-----|
|DDRB |0 0 1|
|DDRC |0 1 0|
|DDRD |0 1 1|
|PORTB|1 0 0|
|PORTC|1 0 1|
|PORTD|1 1 0|

