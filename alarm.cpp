#include "mbed.h"
#include "alarmsystem.h"

DigitalIn armAlarm = D2;

bool alarm_active = false;
int i = 0;
int countdown = 10;

//alarm_changed will make sure there can only be activated/deactivated once per second.
bool alarm_changed = false;

void arm_alarm() {

    while(1) {

        if (armAlarm == 1) {
            if (alarm_active == false) {
                ThisThread::sleep_for(500ms);
                alarm_active = true;
                armalarm();
            } else {
                ThisThread::sleep_for(500ms);
                alarm_active = false;
                stopalarm();
            }
        }

    }
}