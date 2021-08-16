#ifndef ETHERNET_H
#define ETHERNET_H

#include "EthernetInterface.h"
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

    void connectTest() {
printf("111\n");

        net.connect();

        printf("222\n");
 
    // Show the network address
    net.get_ip_address(&a);

    printf("333\n");

    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");
    // Open a socket on the network interface, and create a TCP connection to mbed.org
    socket.open(&net);

    printf("444");
 
    //net.gethostbyname("ifconfig.io", &a);
    a.set_ip_address("10.130.52.204");
    a.set_port(80);
 
    socket.connect(a);
    // Send a simple http request
    char sbuffer[] = "GET /GronCan/ / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n";
    //sprintf(sbuffer, "GET /GronCan/ /LIGHTSTATUS/ %i / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n", g);
    int scount = socket.send(sbuffer, sizeof sbuffer);
    printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
 
    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    int rcount = socket.recv(rbuffer, sizeof rbuffer);
    printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
 
    // Close the socket to return its memory and bring down the network interface
    socket.close();
 
    // Bring down the ethernet interface
    net.disconnect();
    printf("Disconnected\n");
    }
};

#endif