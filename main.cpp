#include "mbed.h"
#include "LCD_DISCO_F746NG.h"
#include "light.h"
#include "startup.h"
#include "ethernet.h"

LCD_DISCO_F746NG lcd;

int main()
{
    Startup();
    internet();
    //Thread1.start(Temperature_thread);
    //Thread2.start(Sound_thread);
    Thread3.start(Light_thread);
    Thread4.start(Time_thread);
}
