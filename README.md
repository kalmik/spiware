# SPIWARE

	The GPIO expander over SPI communication

## Protocol 0.1

It's is a implementation to a SPI "bridge slave mode" to ATMEGA328p.

### Protocol byte frame

|MODE|VALUE   |PORT ADDR                   |PIN ADDR                   |
|----|--------|----------------------------|---------------------------|
|SPI_B7|SPI_B6| SPI_B5 \| SPI_B4 \| SPI_B3 | SPI_B2 \| SPI_B1 \| SPI_B0|

* SPI_B7
    > It's is the access mode to the regiters LOW (0) to read and HIGH (1) to write
* SPI_B6
    > It's is the bit value to be write on register
* SPI_B[5-3]
    > Register address [ PORT | DDR ]
* SPI_B[2-0]
    > Register slot address

#### PORT mapping (ATMEGA328p only)

|REGISTER | ADDR|
|-----|-----|
|DDRB |0 0 1|
|DDRC |0 1 0|
|DDRD |0 1 1|
|PORTB|1 0 0|
|PORTC|1 0 1|
|PORTD|1 1 0|

#### Raw bit examples

* Write 1 on PB7

    ```c
    /*
     * We need to set
     * SPI_B7 = 1       --> Write mode
     * SPI_b6 = 1       --> write '1'
     * SPI_B[5-3] = 100 --> PORTB
     * SPI_B[2-0] = 111 --> 7 in binary
     */

    /* binary way */
    command = 0b11100111;
    /* hex way */
    command = 0xE7
    ```
* Read PD7

    ```c
    /*
     * We need to set
     * SPI_B7 = 0       --> Read mode
     * SPI_b6 = 0       --> 0
     * SPI_B[5-3] = 110 --> PORTD
     * SPI_B[2-0] = 110 --> 7 in binary
     */
     
    /* binary way */
    command = 0b00110110;
    /* hex way */
    command = 0x36;
    ```

 * Read ADC 1

 	To access the Analogic Digital Converter (ADC) the command should in READ MODE and set 1 in value bit (SPI_B6) and do not specify any PORT. so the command to read ADC should start with 01000_ _ _ the last 3 bits is the ADC number.

    ```c
    /* binary way */
    command = 0b01000001;
    // hex way
    command = 0x41;
    
    /*
     * To make easier you can do.
     */
     #define ANALOG_CMD = 0x40
     command = ANALOG_CMD | 0x01
    ```

