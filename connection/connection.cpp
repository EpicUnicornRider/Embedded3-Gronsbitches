#include "connection.h"
#include <cstdio>

void connection(char ip[], int port, char txtbuffer[]) {

    /*myConnection connection;

    connection.address = ip;
    connection.port = port;

    connection.socketConnect();
    connection.sendData(txtbuffer);
    connection.recvData();
    connection.disconnect();*/

    myConnection* connection;
    connection = new myConnection();

    connection->address = ip;
    connection->port = port;

    connection->socketConnect();
    connection->sendData(txtbuffer);
    connection->recvData();
    connection->disconnect();

}