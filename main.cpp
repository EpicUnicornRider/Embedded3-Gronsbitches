/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "EthernetInterface.h"
#include "ethernet.h"

// Network interface
//EthernetInterface net;

DigitalIn button = D4;

char ip[] = "10.130.52.60";
int port = 80;
char txtbuffer[] = "GET /secret/?sw=0 / HTTP/1.1\r\n HOST: 10.130.52.60\r\n\r\n";

// Socket demo
int main()
{

    myInternet* connection;
    connection = new myInternet();

    connection->socketConnect(ip, port);
    connection->sendData(txtbuffer);
    connection->recvData();
    connection->disconnect();
    
    // Bring up the ethernet interface
    /*printf("Ethernet socket example\n");
    net.connect();

    // Show the network address
    SocketAddress a;
    //net.get_ip_address(&a);

    printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

    // Open a socket on the network interface, and create a TCP connection to mbed.org
    TCPSocket socket;
    socket.open(&net);

    //net.gethostbyname("ifconfig.io", &a);
    a.set_ip_address("10.130.52.75");
    a.set_port(80);

    socket.connect(a);
    // Send a simple http request
    char sbuffer[] = "GET /secret/?sw=1 / HTTP/1.1\r\n HOST: 10.130.52.75\r\n\r\n";
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
    printf("Done\n");*/
}
