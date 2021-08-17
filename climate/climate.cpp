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
* This method will be used when opening the window
* @author Rasmus M. Sørensen
* @date 16-08-2021
*/
void myClimate::openWindow() {
    window = 1;
}

/** 
* This method will be used when closing the window
* @author Rasmus M. Sørensen
* @date 17-08-2021
*/
void myClimate::closeWindow() {
    window = 0;
}

/** 
* This method will be used when the humidifier should turn on
* @author Rasmus M. Sørensen
* @date 16-08-2021
*/
void myClimate::startHumidifier() {
    humidifier = 1;
}

/** 
* This method will be used when the humidifier should turn off
* @author Rasmus M. Sørensen
* @date 16-08-2021
*/
void myClimate::stopHumidifier() {
    humidifier = 0;
}
