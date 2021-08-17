#include "mbed.h"
#include "alarmsystem.h"

DigitalIn armAlarm = D2;

//This variable is to make sure the same code doesn't run two time in a row.
bool alarm_active = false;
int i = 0;

//Used for the countdown on the screen.
int countdown = 10;

//alarm_changed will make sure there can only be activated/deactivated once per second.
bool alarm_changed = false;


//This function just runs a few functions depending on if the alarm is already armed or not when clicking the button.
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