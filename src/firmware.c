#define F_CPU 16000000UL
#include <avr/io.h>

volatile unsigned char lastData = 0;
volatile unsigned char AD[6];
volatile unsigned char pwm0 = 0;
volatile unsigned char pwm1 = 0;

/* ACCESS MOD */
#define WRITE 0x80
#define READ  0x00
/*------------*/

#define HIGH 0x40

#define PWM_SET_PS   0x08
#define PWM_SET_DUTY 0x40 | 0x00

#define GET_PIN  0x07
#define GET_PORT 0x38
#define GET_VALUE 0x40
#define GET_OCR 0x10

#define _DDRB  0x08
#define _DDRC  0x10
#define _DDRD  0x18

#define _PORTB  0x20
#define _PORTC  0x28
#define _PORTD  0x30

#define PWM 0x20
#define PWM_0 0x20
#define PWM_0A PWM_0
#define PWM_0B PWM_0 | 0x10

#define PWM_1 0x30
#define PWM_1A PWM_1

unsigned char initPWM(unsigned char command)
{
    /*
     * Help function to initialize PWM
     *
     */
    switch ((command & GET_PORT) & 0x30) {
        case (PWM_0):
            if(pwm0) break;
            setPinCommand(WRITE | HIGH | _DDRD | 6);
            TCCR0A = (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
            TCCR0B = (command & GET_PIN);
            pwm0 = 1;
            return pwm0;
        case (PWM_1):
            if(pwm1) break;
            setPinCommand(WRITE | HIGH | _DDRB | 1);
            TCCR1A = (1 << COM1A1) | (1 << WGM10) | (1 << WGM11);
            TCCR1B = (1 << WGM12) | (command & GET_PIN);
            OCR1A = 0x00;
            pwm1 = 1;
            return pwm1;
    }
}

void setPWMOCR (unsigned char lastCommand, unsigned char duty) {

    lastData = 0x00;
    switch((lastCommand & GET_PORT) & 0x30)
    {
        case (PWM_0):
            OCR0A = duty;
            break;
        case (PWM_1):
            OCR1A = duty;
            break;
    }
}

void setPinCommand(volatile unsigned char lastData) {
    switch (lastData & GET_PORT) {
        case (_DDRB):
            if ((lastData & GET_PIN) == 1) {
                TCCR1A = 0x00;
                TCCR1B = 0x00;
                OCR1A = 0x00;
                pwm1 = 0;
            }
            DDRB &= ~(1 << (lastData & GET_PIN));
            DDRB |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
        case (_DDRC):
            DDRC &= ~(1 << (lastData & GET_PIN));
            DDRC |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
        case (_DDRD):
            if ((lastData & GET_PIN) == 6) {
                TCCR0A = 0x00;
                TCCR0B = 0x00;
                OCR0A = 0x00;
                pwm0 = 0;
            }
            DDRD &= ~(1 << (lastData & GET_PIN));
            DDRD |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
        case (_PORTB):
            PORTB &= ~(1 << (lastData & GET_PIN));
            PORTB |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
        case (_PORTC):
            PORTC &= ~(1 << (lastData & GET_PIN));
            PORTC |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
        case (_PORTD):
            PORTD &= ~(1 << (lastData & GET_PIN));
            PORTD |=  (!!(lastData & GET_VALUE) << (lastData & GET_PIN));
            break;
    }
}

unsigned char getPinCommand(volatile unsigned char lastData) {

    switch (lastData & GET_PORT) {
        case (_PORTB):
            if (DDRB & (1 << (lastData & GET_PIN))) {
                return !!(PORTB & (1 << (lastData & GET_PIN)));
            } else {
                return !!(PINB & (1 << (lastData & GET_PIN)));
            }
            break;
        case (_PORTC):
            if (DDRC & (1 << (lastData & GET_PIN))) {
            return !!(PORTC & (1 << (lastData & GET_PIN)));
            } else {
                return !!(PINC & (1 << (lastData & GET_PIN)));
            }
            break;
        case (_PORTD):
            if (DDRD & (1 << (lastData & GET_PIN))) {
                return !!(PORTD & (1 << (lastData & GET_PIN)));
            } else {
                return !!(PIND & (1 << (lastData & GET_PIN)));
            }
            break;
    }
}

ISR(SPI_STC_vect) {
    /*
     * Routine to parser SPDR as 8bit command
     */
    unsigned char command = SPDR;

    if (!!((lastData & GET_PORT) & PWM) && SPDR) {
        setPWMOCR(lastData, SPDR);
        return;
    }

    if (command & WRITE) {
        setPinCommand(command);
    }

    else {
        if (!! (command & GET_VALUE) && !(command & GET_PORT)) {
            /* ADC parser */
            SPDR = AD[command & GET_PIN];

        } else if ((command & GET_VALUE) && (command & GET_PORT)) {
            if ((command & GET_PORT) & PWM) {
                /* PWM parser */

                if (!!(command & GET_PORT) && !!(command & PWM_SET_PS)) {
                    SPDR = initPWM(command);
                } else {
                    lastData = command;
                }
            }
        } else {
            SPDR = getPinCommand(command);
        }
    }
}

unsigned char getAD(unsigned char addr) {
    /*
     * Configuring ADC registors and busy waiting for
     * conversion ends.
     */

    unsigned char out;
    ADMUX &= 0xF0;
    ADMUX |= addr;

    ADCSRA |= 0x40 ;

    while ( ! (ADCSRA & ( 1 << ADIF) ) ) {}
    out = ADCH;

    return out;

}

int main(){
     /*
      * PB3 - MOSI,
      * PB4 - MISO,
      * PB5 - SCK,
      * PB2 - SS,
      * PB0 = External MUX for ADs Inputs AD4 and AD5.
      */
    DDRB |= 0x13;

    // PD2 to PD7 are the Contact Sensors Inputs 1 to 6 (All pull-ups).
    PORTD |= 0xFC;

    SPCR |= (1 << SPIE) | (1 << SPE);

    ADMUX |= (1 << REFS0) | (1 << ADLAR);
    ADCSRA |= (1 << ADEN) | (1 << ADPS0) | (1 << ADPS1) | (1 << ADPS2) ;

    sei();

    while(1) {
        /*
         * Continue converting Analog pins as I can
         *
         */
        AD[0] = getAD(0);
        AD[1] = getAD(1);
        AD[2] = getAD(2);
        AD[3] = getAD(3);
        AD[4] = getAD(4);
        AD[5] = getAD(5);
    }

    return 0;

}

