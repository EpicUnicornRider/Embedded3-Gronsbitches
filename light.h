#include "mbed.h"

AnalogIn Light(A2); //Readings from light sensor

Thread Thread3;

int32_t LightA = 0;

void Light_thread()
{
    while(true) {

        float g = Light.read(); //read light
        LightA = 0;
        for(int i=0; i<32; i++) {
            LightA += Light.read_u16();
        }

        LightA >>= 5;

        wait_us(1000000);
    }
}