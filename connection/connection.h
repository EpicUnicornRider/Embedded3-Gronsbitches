#ifndef ETH_HANDLING_H
#define ETH_HANDLING_H

#include "mbed.h"
#include "EthernetInterface.h"

class myConnection {
    public:
        EthernetInterface net;
        SocketAddress a;
        TCPSocket socket;
        char *address;
        int port;

        void socketConnect() {

            net.connect();

            if(net.get_connection_status()) {
                printf("Connected successfully\n");
            } else {
                printf("Connection failed\n");
            }
            net.get_ip_address(&a);

            printf("IP address: %s\n", a.get_ip_address() ? a.get_ip_address() : "None");

            socket.open(&net);
            a.set_ip_address(address);
            a.set_port(port);

            socket.connect(a);
        }

        void sendData(char sbuffer[]) {
            // Send a simple http request
            int scount = socket.send(sbuffer, strlen(sbuffer));
            printf("sent %d [%.*s]\n", scount, strstr(sbuffer, "\r\n") - sbuffer, sbuffer);
        }

        void recvData() {
            // Recieve a simple http response and print out the response line
            char rbuffer[64];
            int rcount = socket.recv(rbuffer, sizeof rbuffer);
            printf("recv %d [%.*s]\n", rcount, strstr(rbuffer, "\r\n") - rbuffer, rbuffer);
        }

        void disconnect() {
            socket.close();
            net.disconnect();
            printf("Done\n");
        }
};

#endif