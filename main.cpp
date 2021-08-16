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
    /*char ip[] = "10.130.52.204";
    int port = 80;
    char txtSend[] = "GET /GronCan/?sw=1 \\Hello\\ HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n";

    internet(ip, port, txtSend);*/

    int num = 1;

    startsystem();

    thread1.start(arm_alarm);


    thread2.start(alarmdetect);
}   