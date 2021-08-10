#include "mbed.h"

DigitalIn vibrationSensor = D5;

int vibration() {

    while(true) {

        double readout = vibrationSensor.read();
        printf("Value: %lf /n", readout);

        wait_us(500000);
    }
    
    return 1;
}