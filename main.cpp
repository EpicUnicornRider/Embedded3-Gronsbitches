#include "mbed.h"
#include "internet.h"
#include "vibrationsensor.h"
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

    thread1.start(vibration);
    thread2.start(arm_alarm);

    /*while(1) {



        printf("Hello %d\n", num);

        num = num + 1;

        ThisThread::sleep_for(1s);
        //wait_us(1000000);

    }*/
}