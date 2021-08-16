#include "mbed.h"
#include <stdio.h>
#include <string>
#include "EthernetInterface.h"
#include "ethernet.h"

std::string internet(char ip[], int port, std::string txtSend) {

    char txtarray[100];

    strcpy(txtarray, txtSend.c_str()); 
    
    Ethernet ethernet;

    ethernet.address = ip;
    ethernet.port = port;

    //ethernet.connectTest();


    ethernet.connect();
    ethernet.sendGetRequest(txtarray);
    string recv = ethernet.receiveRequest();
    ethernet.closeConnection();

    return recv;
}