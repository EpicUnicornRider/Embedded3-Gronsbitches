/**
*   @file internet.cpp
*   @brief This file contains functions to communicate with the server, only the mini api calls these functions.
*
*   @author Oliver P. Hartvigsen.
*   
*   @date 2021-08-17
*/

#include "mbed.h"
#include <stdio.h>
#include <string>
#include "EthernetInterface.h"
#include "ethernet.h"

//This function will instanciate ethernet.h and run the internet stack.
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

//This function is not used.
void closeconnection() {

    Ethernet ethernet;

    ethernet.closeConnection();

}