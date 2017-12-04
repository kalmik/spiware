#ifndef ATMEGA382P_H
#define ATMEGA382P_H
/**
 * 
 */
 	#define HIGH 0x40
  	#define LOW  0x00

 	/* ACCESS MOD */
	#define WRITE 0x80 /* 10000000 */
	#define READ  0x00
 	#define ANALOG 0x40
    /*------------*/

 	#define DDRB  0x08
 	#define DDRC  0x10
 	#define DDRD  0x18

 	#define PORTB  0x20
 	#define PORTC  0x28
 	#define PORTD  0x30

 	/* PIN ADDR */
 	#define PIN_00 0x00
 	#define PIN_01 0x01
 	#define PIN_02 0x02
 	#define PIN_03 0x03
 	#define PIN_04 0x04
 	#define PIN_05 0x05
 	#define PIN_06 0x06
 	#define PIN_07 0x07
 	/*-----------*/

 	#define PWM_SET_PS   0x40 | 0x08 //set pre-scaler command
	#define PWM_SET_DUTY 0x40 | 0x00 //set duty_cycle command

	#define PWM 0x20
	#define PWM_0 0x20
	#define PWM_0A PWM_0
	#define PWM_0B PWM_0 | 1
	#define PWM_1 0x30
	#define PWM_1A PWM_1


 	#define PWM_LENGTH 255


 	/* PORT ADDR -------------------------------------*/
 	#define PIN_PORT_08 PORTB | PIN_00 /* port B0               */
 	#define PIN_PORT_09 PORTB | PIN_01 /* port B1 PWM           */
 	#define PIN_PORT_10 PORTB | PIN_02 /* port B2 PWM SPI CS    */
 	#define PIN_PORT_11 PORTB | PIN_03 /* port B3 PWM SPI MOSI  */
 	#define PIN_PORT_12 PORTB | PIN_04 /* port B4     SPI MISO  */
 	#define PIN_PORT_13 PORTB | PIN_05 /* port B5     SPI SCK   */

	#define PIN_PORT_A0 PORTC | PIN_00 /* port C0               */ 
	#define PIN_PORT_A1 PORTC | PIN_01 /* port C1               */ 
	#define PIN_PORT_A2 PORTC | PIN_02 /* port C2               */ 
	#define PIN_PORT_A3 PORTC | PIN_03 /* port C3               */ 
	#define PIN_PORT_A4 PORTC | PIN_04 /* port C4               */ 
	#define PIN_PORT_A5 PORTC | PIN_05 /* port C5               */

	#define PIN_PORT_00 PORTD | PIN_00 /* port D0               */ 
	#define PIN_PORT_01 PORTD | PIN_01 /* port D1               */ 
	#define PIN_PORT_02 PORTD | PIN_02 /* port D2      INT0     */ 
	#define PIN_PORT_03 PORTD | PIN_03 /* port D3 PWM  INT1     */ 
	#define PIN_PORT_04 PORTD | PIN_04 /* port D4               */ 
	#define PIN_PORT_05 PORTD | PIN_05 /* port D5 PWM           */ 
	#define PIN_PORT_06 PORTD | PIN_06 /* port D6 PWM           */ 
	#define PIN_PORT_07 PORTD | PIN_07 /* port D7               */ 

 	#define DIR_PORT_08 DDRB | PIN_00 
 	#define DIR_PORT_09 DDRB | PIN_01 
 	#define DIR_PORT_10 DDRB | PIN_02 
 	#define DIR_PORT_11 DDRB | PIN_03 
 	#define DIR_PORT_12 DDRB | PIN_04 
 	#define DIR_PORT_13 DDRB | PIN_05 

	#define DIR_PORT_A0 DDRC | PIN_00
	#define DIR_PORT_A1 DDRC | PIN_01
	#define DIR_PORT_A2 DDRC | PIN_02
	#define DIR_PORT_A3 DDRC | PIN_03
	#define DIR_PORT_A4 DDRC | PIN_04
	#define DIR_PORT_A5 DDRC | PIN_05

	#define DIR_PORT_00 DDRD | PIN_00
	#define DIR_PORT_01 DDRD | PIN_01
	#define DIR_PORT_02 DDRD | PIN_02
	#define DIR_PORT_03 DDRD | PIN_03
	#define DIR_PORT_04 DDRD | PIN_04
	#define DIR_PORT_05 DDRD | PIN_05
	#define DIR_PORT_06 DDRD | PIN_06
	#define DIR_PORT_07 DDRD | PIN_07
 	/*------------------------------------------------*/

  	#define PWM_0_PIN PIN_PORT_06
 	#define PWM_1_PIN PIN_PORT_09

 	#define PWM_0_DIR DIR_PORT_06
 	#define PWM_1_DIR DIR_PORT_09

/*end ATMEGA382P_H */
#endif 