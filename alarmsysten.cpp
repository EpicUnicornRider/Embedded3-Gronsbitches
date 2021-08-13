#include "alarm.h"
#include "controllerscreen.h"
#include "vibrationsensor.h"
#include "mbed.h"

void startsystem() {
    LCDStart();
    clearscreen();
    startuptext();
}

void stopalarm() {
    disablealarm();
}

void armalarm() {
    countdownalarmscreen();
}

void alarm() {
    
}