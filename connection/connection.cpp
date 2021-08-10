#include "connection.h"
#include <cstdio>

char ip[] = "10.130.52.60";
int port = 80;
char txtbuffer[] = "GET /secret/?sw=1 / HTTP/1.1\r\n HOST: 10.130.52.60\r\n\r\n";

void connection() {

    myConnection* connection;
    connection = new myConnection();

    connection->address = ip;
    connection->port = port;

    connection->socketConnect();
    connection->sendData(txtbuffer);
    connection->recvData();
    connection->disconnect();

}