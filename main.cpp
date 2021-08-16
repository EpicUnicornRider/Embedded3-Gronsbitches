#include "mbed.h"
#include "LCD_DISCO_F746NG.h"
#include "startup.h"
#include "ethernet.h"

LCD_DISCO_F746NG lcd;

int main()
{
    Startup(); // Startup screen on the LCD screen
    internet(); // Obtaining connection to the internet and an IP address
    Thread2.start(Sound_thread); // Thread checking sound status from sound sensor
    Thread3.start(Light_thread); // Thread checking the amount of light from light sensor
    Thread4.start(Time_thread);  // Thread checking current time using NTP
    SensorsInfo(); // Function for creating a new connection to the server and sending current information
}