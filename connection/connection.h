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
        nsapi_error_t error;

    public:
        char *address;
        int port;
        void socketConnect(char sbuffer[]);

};

#endif