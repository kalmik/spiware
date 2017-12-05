# Protocol 0.1

## Protocol byte frame

|MODE|VALUE   |PORT ADDR                   |PIN ADDR                   |
|----|--------|----------------------------|---------------------------|
|SPI_B7|SPI_B6| SPI_B5 \| SPI_B4 \| SPI_B3 | SPI_B2 \| SPI_B1 \| SPI_B0|

* SPI_B7
    > It's is the access mode to the regiters LOW to write and HIGH to read
* SPI_B6
    > It's is the bit value to be write on register
* SPI_B[5-3]
    > Register address [ PORT | DDR ]
* SPI_B[2-0]
    > Register slot address

### PORT mapping (ATMEGA328p only)

|REGISTER | ADDR|
|-----|-----|
|DDRB |0 0 1|
|DDRC |0 1 0|
|DDRD |0 1 1|
|PORTB|1 0 0|
|PORTC|1 0 1|
|PORTD|1 1 0|

