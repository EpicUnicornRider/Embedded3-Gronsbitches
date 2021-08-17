#include "alarm.h"
#include "controllerscreen.h"
#include "vibrationsensor.h"
#include "ethernetcommunication.h"
#include "internet.h"
#include "mbed.h"

bool detecton = false;
bool alarmtriggeredsystem = false;
int cnt = 0;

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
    tryingtoarm();
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

                if (cnt > 10) {
                    cnt = 0;
                    getsoundstatus();
                }
            }

            cnt++;
            ThisThread::sleep_for(50ms);
        }
}