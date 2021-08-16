/**
*       @file connection.cpp
*       @brief This file will include the code needed to make a TCPSocket connection
*
*       @author Rasmus M. Sørensen
*
*       @date 16-08-2021
*/

#include "EthernetInterface.h"
#include <cstdio>
#include <exception>
#include "connection.h"

EthernetInterface net;
TCPSocket socket;

/** 
* This is the method to be called in main.cpp
* @author Rasmus M. Sørensen 
* @date 16-08-2021
*/
void connection(char ip[], int port, char txtbuffer[]) {
    myConnection connection(ip, port);
    connection.socketConnect(txtbuffer);
}

/** 
* This method will be used to open a TCPSocket and send data to the server
* @author Rasmus M. Sørensen
* @param sbuffer The data to send 
* @date 16-08-2021
*/
void myConnection::socketConnect(char sbuffer[]) {

            error = net.connect();

            if(error) {
                printf("Can't connect: %i\n", error);
            } else {
                printf("Successfully connected \n");
            }

            printf("before\n");

            SocketAddress a;

            error = net.get_ip_address(&a);

            printf("after\n");

            if(error) {
                printf("Could not get an IP address: %i\n", error);
            }

            printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

            error = socket.open(&net);

            if(error) {
                printf("Can't open socket on ethernet connection: %i\n", error);
            }

            error = a.set_ip_address(address);

            a.set_port(port);

            error = socket.connect(a);

            if(error) {
                printf("Can't connect to server device: %i\n", error);
            }

            int scount = socket.send(sbuffer, strlen(sbuffer));
            printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);

            char rbuffer[64];
            int rcount = socket.recv(rbuffer, sizeof rbuffer);
            printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
        

            error = socket.close();

            if (error) {
                printf("Can't close socket: %i\n", error);
            }

            error = net.disconnect();

            if (error) {
                printf("Can't disconnect from network: %i \n", error);
            }
    }
