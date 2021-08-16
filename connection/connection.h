/**
*       @file connection.h
*       @brief This header will be a class for a connection object
*
*       @author Rasmus M. Sørensen
*
*       @date 16-08-2021
*/

#ifndef ETH_HANDLING_H
#define ETH_HANDLING_H

#include "mbed.h"


class myConnection {
    private:
        char *address;
        int port;
        nsapi_error_t error;

    public:
        void socketConnect(char sbuffer[]);

        myConnection(char *ip, int portt) {
            this->address = ip;
            this->port = portt;
        }

        ~myConnection() {
            delete[] address;

            printf("Done\n");
        }
};

#endif