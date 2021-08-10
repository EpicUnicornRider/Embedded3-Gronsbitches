#include "ethernet.h"
#include <cstdio>

char ip[] = "10.130.52.60";
int port = 80;
char txtbuffer[] = "GET /secret/ / HTTP/1.1\r\n HOST: 10.130.52.60\r\n\r\n";

void ethernet1() {

    myInternet* connection;
    connection = new myInternet();

    connection->address = ip;
    connection->port = port;

    connection->socketConnect();
    connection->sendData(txtbuffer);
    connection->recvData();
    connection->disconnect();

}