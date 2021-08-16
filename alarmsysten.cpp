#include "alarm.h"
#include "controllerscreen.h"
#include "vibrationsensor.h"
#include "ethernetcommunication.h"
#include "mbed.h"

bool detecton = false;
bool alarmtriggeredsystem = false;

void startsystem() {
    LCDStart();
    clearscreen();
    startuptext();
}

void stopalarm() {
    alarmtriggeredsystem = false;
    detecton = false;
    alarmunarmed();
    disablealarm();
}

void armalarm() {
    alarmarmed();
    countdownalarmscreen();
    detecton = true;
}

void alarmdetect() {
        while(1) {
            if(detecton) {
                if(vibration() && alarmtriggeredsystem == false) {
                    alarmtriggeredsystem = true;
                    alarmtriggered();
                    alarm();
                }
            }
            ThisThread::sleep_for(50ms);
        }
}