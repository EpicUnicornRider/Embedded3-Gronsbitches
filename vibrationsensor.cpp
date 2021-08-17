/**
*   @file vibrationsensor.cpp
*   @brief The function in this file will monitor the vibration sensor and send back true/false.
*
*   @author Oliver P. Hartvigsen.
*   
*   @date 2021-08-17
*/
#include "mbed.h"

DigitalIn vibrationSensor = D5;


//Check if there's any vibration, value is printed in console and if detected func will return true.
bool vibration() {

    int i = 0;
    int detected = 0;


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
        printf("Vibration detected: True \n");
        return true;
    } else {
        printf("Vibration detected: False \n");
        return false;
    }


}