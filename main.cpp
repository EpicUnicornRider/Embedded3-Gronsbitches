/*
 * Copyright (c) 2006-2020 Arm Limited and affiliates.
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"

InterruptIn  mypin(D4); // change this to the button on your board
DigitalOut myled(D2);
DigitalOut BLed(LED1);

void Light(){
    printf("mypin has value : %d \n\r", mypin.read());
    myled = !myled; // toggle led based on value of button
}
    
int main()
{
    mypin.rise(&Light);

    BLed = !BLed;
    wait_us(250000);

    
}
