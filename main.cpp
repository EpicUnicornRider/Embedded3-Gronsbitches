/**
*   @file main.cpp
*   @brief Main file to start program.
*
*   @author Oliver P. Hartvigsen.
*   
*   @date 2021-08-17
*/

#include "mbed.h"
#include "internet.h"
#include "vibrationsensor.h"
#include "controllerscreen.h"
#include "alarmsystem.h"
#include "alarm.h"
#include "rtos.h"

Thread thread1;
Thread thread2;

int main()
{
    startsystem();

    //This thread will run function to detect if alarm button to activate/deactive is pressed.
    thread1.start(arm_alarm);

    //This thread will check if alarm is tripped, checking the vibration sensor and sending request to server for sound data.
    thread2.start(alarmdetect);
}   