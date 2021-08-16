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
    int num = 1;

    startsystem();

    thread1.start(arm_alarm);


    thread2.start(alarmdetect);
}   