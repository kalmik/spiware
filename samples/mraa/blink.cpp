#include <stdio.h>
#include "spi.h"

int main(int argc, char *argv[]){

    unsigned char state;

    SPI s(4000000);

    mraa_gpio_context p1 = s.addSlave(7);
    s.sendCommand(WRITE | HIGH  | DIR_PORT_09, p1);

    while(1){

        state = s.getDigital(PIN_PORT_09, p1) ^ 1;
        if(state) state = HIGH;

        s.sendCommand(WRITE | state | PIN_PORT_09, p1);

        state = s.getDigital(PIN_PORT_09, p1);

        printf("PIN %i\n", state);

        sleep(1.5);

    }

    return 0;
}
