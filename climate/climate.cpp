/**
*       @file climate.cpp
*       @brief This file will include the code 
*       needed to read and control the climate
*
*       @author Rasmus M. Sørensen
*
*       @date 16-08-2021
*/

#include "climate.h"
#include "DHT.h"

DigitalOut window = D6;
DigitalOut humidifier = D2;

DHT tempHumidSensor(D3, DHT22);

/** 
* This method will get the temperature and return the result
* @author Rasmus M. Sørensen
* @param value This is the temperature value that will be returned
* @date 16-08-2021
*/
float temperature() {
    float tempValue;

    tempHumidSensor.readData();

    tempValue = tempHumidSensor.ReadTemperature(CELCIUS);

    myClimate tempClimate(tempValue);

    return tempClimate.value;
}

/** 
* This method will get the humidity and return the result
* @author Rasmus M. Sørensen
* @param value This is the humidity value that will be returned
* @date 16-08-2021
*/
float humidity() {
    float humidValue;

    tempHumidSensor.readData();

    humidValue = tempHumidSensor.ReadHumidity();

    myClimate humidClimate(humidValue);

    return humidClimate.value;
}

/** 
* These methods will be used when a window should either open or close
* @author Rasmus M. Sørensen
* @date 16-08-2021
*/
void openWindow() {
    window = 1;
}
void closeWindow() {
    window = 0;
}

/** 
* These methods will be used when the humidifier should either turn on or off
* @author Rasmus M. Sørensen
* @date 16-08-2021
*/
void startHumidifier() {
    humidifier = 1;
}
void stopHumidifier() {
    humidifier = 0;
}
