#include "mbed.h"
#include <stdio.h>
#include "EthernetInterface.h"
#include "ethernet.h"

void internet(char ip[], int port, char txtSend[]) {
    
    Ethernet ethernet;

    ethernet.address = ip;
    ethernet.port = port;

    ethernet.connect();
    ethernet.sendGetRequest(txtSend);
    ethernet.receiveRequest();
    ethernet.closeConnection();
}