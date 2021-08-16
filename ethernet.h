#ifndef ETHERNET_H
#define ETHERNET_H

#include "EthernetInterface.h"
#include <string>
#include "mbed.h"

    EthernetInterface net;
    SocketAddress a;
    TCPSocket socket;

class Ethernet {       // The class
  public:             // Access specifier
    char *address;
    int port;
    
    void connect() {
        printf("Ethernet socket example\n");
        net.connect();
 
        net.get_ip_address(&a);
 
        printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
 
        socket.open(&net);
 
        a.set_ip_address(address);
        a.set_port(port);
 
        socket.connect(a);
    }

    void sendGetRequest(char sbuffer[]) {
        int scount = socket.send(sbuffer, strlen(sbuffer) + 1);
        printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
    }

    string receiveRequest() {
        char rbuffer[64];
        int rcount = socket.recv(rbuffer, sizeof rbuffer);
        printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);

        printf("%s", rbuffer);

        return rbuffer;
    }

    void closeConnection() {
        // Close the socket to return its memory and bring down the network interface
        socket.close();
    
        // Bring down the ethernet interface
        net.disconnect();
        printf("Done\n");
    }
};

#endif