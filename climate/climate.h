/**
*       @file climate.h
*       @brief This header will be a class for climate objects
*
*       @author Rasmus M. Sørensen
*
*       @date 16-08-2021
*/

#ifndef CLI_HANDLING_H
#define CLI_HANDLING_H

#include "mbed.h"

class myClimate {

    public:
        float value;

        myClimate(float value) {
            this->value = value;
        }
        

};

#endif