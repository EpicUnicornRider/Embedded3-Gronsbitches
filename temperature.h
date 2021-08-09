#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

AnalogIn Temp(A0); //Readings from temperature sensor
DigitalOut Heater(D2); //Red LED simulating heater
DigitalOut AC(D4); //Blue LED simulating Air Conditioning

Thread Thread1;

int R0 = 100000;
int B = 4275;
char tempCount[50];


void Temperature_thread()
{
    while(true) {

        int a = Temp.read_u16();
        float R = 65536.0/a-1.0;
        R = R0*R;

        float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; //Calculating analog input from temperature sensor to show celsius

        sprintf(tempCount, "Temperature: %.1fC", temperature);
        printf("temperature: %.1fC\n", temperature);
        BSP_LCD_DisplayStringAt(0, LINE(3), (uint8_t *)tempCount, CENTER_MODE); //Display text and temperature readings on LCD display
        wait_us(5000000);

        if(temperature > 28) { //AC turns on at temperatures above 28 degrees celsius
            AC = 1;
            Heater = 0;
        } else if(temperature < 27) { //Heater turns on at temperatures below 27 degrees celsius
            Heater = 1;
            AC = 0;
        }
    }
}