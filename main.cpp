#include "mbed.h"
#include "internet.h"
#include "vibrationsensor.h"
#include "rtos.h"

// main() runs in its own thread in the OS
int main()
{
    char ip[] = "10.130.52.204";
    int port = 80;
    char txtSend[] = "GET /GronCan/?sw=1 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n";

    internet(ip, port, txtSend);
}