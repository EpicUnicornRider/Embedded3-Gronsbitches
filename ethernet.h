#ifndef ETHERNET_H
#define ETHERNET_H

#include "EthernetInterface.h"

class Ethernet {       // The class
  public:             // Access specifier

    EthernetInterface net;
    SocketAddress a;
    TCPSocket socket;
    char *address;
    int port;
    char httpRequest[];
    
    void connect() {
        printf("Ethernet socket example\n");
        net.connect();
 
        // Show the network address
        SocketAddress a;
        net.get_ip_address(&a);
 
        printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
 
        // Open a socket on the network interface, and create a TCP connection to mbed.org
        TCPSocket socket;
        socket.open(&net);
 
        a.set_ip_address(address);
        a.set_port(port);
 
        socket.connect(a);
    }

    void sendGetRequest() {
        char sbuffer[] = "GET %s / HTTP/1.1\r\n HOST: %s\r\n\r\n", httpRequest, address;
        int scount = socket.send(sbuffer, sizeof sbuffer);
        printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
    }

    void receiveRequest() {
        char rbuffer[64];
        int rcount = socket.recv(rbuffer, sizeof rbuffer);
        printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
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