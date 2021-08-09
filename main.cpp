#include "mbed.h"
#include "LCD_DISCO_F746NG.h"
#include "light.h"
#include "sound.h"
#include "temperature.h"
#include "startup.h"

LCD_DISCO_F746NG lcd;

int main()
{
    Startup();
    Thread1.start(Temperature_thread);
    Thread2.start(Sound_thread);
    Thread3.start(Light_thread);
}
