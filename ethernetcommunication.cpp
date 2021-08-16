#include "internet.h"
#include <string> 

char ip[] = "10.130.52.204";
int port = 80;

void alarmtriggered() {
    internet(ip, port, "GET /GronCan/ /ALARM/ 1 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n");
}

void alarmstopped() {
    internet(ip, port, "GET /GronCan/ /ALARM/ 0 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n");
}

void alarmarmed() {
    internet(ip, port, "GET /GronCan/ /ARMED/ 1 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n");
}

void alarmunarmed() {
    internet(ip, port, "GET /GronCan/ /ARMED/ 0 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n");
}

std::string getsoundstatus() {
    return internet(ip, port, "GET /GronCan/ /GETSOUND/ HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n");
}