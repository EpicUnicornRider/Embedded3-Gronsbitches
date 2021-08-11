/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */
#include "mbed.h"
#include "DHT.h"
#include "connection/connection.h"
#include <cstdio>
#include <string>
#include <sstream>

//Pins
DigitalIn tempHumid = D3;

float tValue;
float hValue;
int tVal;
int hVal;

extern void connection(char ip[], int port, char txtbuffer[]);

char ip[] = "10.130.52.204";
int port = 80;
char txtbuffer[73];

// Socket demo
int main()
{
    DHT tempHumidSensor(D3, DHT22);

    while(true) {

    tempHumidSensor.readData();

    tValue = tempHumidSensor.ReadTemperature(CELCIUS);
    hValue = tempHumidSensor.ReadHumidity();

    tVal = (int)tValue;
    hVal = (int)hValue;

    sprintf(txtbuffer, "GET /GronCan/?sw=1 / TEMP/%d.1 / HTTP/1.1\r\n HOST: 10.130.52.204\r\n\r\n", tVal);

    printf("------------------------------\n");
    connection(ip, port, txtbuffer);

    printf("Temperature: %d.1 \n", tVal);
    printf("Humidity: %d%% \n\n",hVal);
    ThisThread::sleep_for(15s);
    }
}
