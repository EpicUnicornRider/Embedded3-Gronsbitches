#include "mbed.h"

DigitalIn armAlarm = D2;
DigitalIn disableAlarm = D3;

int alarm_active = 0;
int i = 0;

//alarm_changed will make sure there can only be activated/deactivated once per second.
bool alarm_changed = false;

void arm_alarm() {

    while(1) {
        while(i < 100) {

            if (armAlarm.read() == 1 && alarm_changed != true) {
                alarm_active = !alarm_active;
                alarm_changed = 1;
            }

            i++;

            ThisThread::sleep_for(10ms);
        }

        printf("Alarm status: %d \n", alarm_active);

        alarm_changed = false;
        i = 0;
    }
}