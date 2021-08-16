/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

/**
*       @file main.cpp
*       @brief This is the main file that will run the program flow
*
*       @author Rasmus M. Sørensen
*
*       @date 16-08-2021
*/
#include "mbed.h"
#include "DHT.h"
#include "connection/connection.h"
#include <cstdio>
#include <string>
#include <sstream>

float tValue;
float hValue;
bool window1;
char txtbuffer[150];

extern float temperature();
extern float humidity();
extern void openWindow();
extern void closeWindow();
extern void startHumidifier();
extern void stopHumidifier();
extern void connection(char txtbuffer[]);

// Socket demo
int main()
{

    while(true) {

    tValue = temperature();
    hValue = humidity();

    if(tValue > 25) {
        openWindow();
        window1 = 1;
    } else if(tValue < 20) {
        closeWindow();
        window1 = 0;
    }

    if(hValue < 40) {
        startHumidifier();
    } else if (hValue > 60) {
        stopHumidifier();
    }

    sprintf(txtbuffer, "GET /GronCan/ /TEMP/ %.1f /HUMID/ %.0f%% /WINDOW/ %i / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n", tValue, hValue, window1);

    printf("------------------------------\n");
    connection(txtbuffer);

    printf("Temperature: %.1f \n", tValue);
    printf("Humidity: %.0f%% \n\n",hValue);
    ThisThread::sleep_for(5s);
    }
}
