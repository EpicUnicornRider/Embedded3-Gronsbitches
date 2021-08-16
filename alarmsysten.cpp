#include "alarm.h"
#include "controllerscreen.h"
#include "vibrationsensor.h"
#include "mbed.h"

bool detecton = false;
bool alarmtriggered = false;

void startsystem() {
    LCDStart();
    clearscreen();
    startuptext();
}

void stopalarm() {
    alarmtriggered = false;
    detecton = false;
    disablealarm();
}

void armalarm() {
    countdownalarmscreen();
    detecton = true;
}

void alarmdetect() {
        while(1) {
            if(detecton) {
                if(vibration() && alarmtriggered == false) {
                    alarmtriggered = true;
                    alarm();
                }
            }
            ThisThread::sleep_for(50ms);
        }
}