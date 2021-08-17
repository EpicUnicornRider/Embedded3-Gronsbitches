#include "alarm.h"
#include "controllerscreen.h"
#include "vibrationsensor.h"
#include "ethernetcommunication.h"
#include "internet.h"
#include "mbed.h"

bool detecton = false;
bool alarmtriggeredsystem = false;
int cnt = 0;

//Initilize the screen.
void startsystem() {
    LCDStart();
    clearscreen();
    startuptext();
}

//Disarm the alarm and send disarm request to server.
void stopalarm() {
    alarmtriggeredsystem = false;
    detecton = false;
    alarmunarmed();
    disablealarm();
}

//Start the alarm enablement countdown and send request to server telling the alarm has been armed.
void armalarm() {
    tryingtoarm();
    alarmarmed();
    countdownalarmscreen();
    detecton = true;
}

//Detect if vibration is detected and get sound status to choose if there's a too loud sound.
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