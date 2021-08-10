#include "mbed.h"
#include <stdio.h>
#include "EthernetInterface.h"
#include "ethernet.h"

void internet(char ip[], int port, char txtSend[]) {
    
    Ethernet ethernet;

    ethernet.address = ip;
    ethernet.port = port;
    strcpy(txtSend, ethernet.httpRequest);

    ethernet.connect();
    ethernet.sendGetRequest();
    ethernet.receiveRequest();
    ethernet.closeConnection();
}