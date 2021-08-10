#include "mbed.h"
#include "internet.h"
#include "vibrationsensor.h"
#include "rtos.h"

// main() runs in its own thread in the OS
int main()
{
    char ip[] = "";
    int port = 2;
    char txtSend[] = "";

    internet(ip, port, txtSend);

    //vibration();
}