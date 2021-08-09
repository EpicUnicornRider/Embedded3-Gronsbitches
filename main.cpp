#include "mbed.h"
#include "TS_DISCO_F746NG.h"
#include "LCD_DISCO_F746NG.h"
#include "sensors.h"

int main()
{
    Startup();
    Thread1.start(Temperature_thread);
    Thread2.start(Sound_thread);
    Thread3.start(Light_thread);

    while(1) {
        //Alarm();
    }
}
