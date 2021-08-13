#include "mbed.h"

DigitalIn vibrationSensor = D5;

bool vibration() {

    int i = 0;
    int detected = 0;

    while(1) {

        detected = 0;

        while(i <= 100) {

            float readout = vibrationSensor.read();
            if (readout == 1) {
                detected = 1;
            }

            i++;

            ThisThread::sleep_for(10ms);
        }

        if(detected == 1) {
            return true;
        } else {
            return false;
        }

        i = 0;

        printf("Value: %d \n", detected);
    }
}