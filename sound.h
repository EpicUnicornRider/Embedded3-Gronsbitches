#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

AnalogIn Sound(A1); //Readings from sound sensor
AnalogIn LightForSound(A2); //Readings from light sensor
DigitalIn Reset(USER_BUTTON); //Onboard reset for Loudness counter
DigitalIn Button(D8); //Button for alarm reset (press 2 times)

Thread Thread2;

int32_t SoundA = 0;
int Count = 0;
char b[1000];
char c[20];
int resetBtn = 0;



void Sound_thread()
{
    while(true) {

        float f = Sound.read(); //reads the sound
        for(int i=0; i<32; i++) {
            SoundA += Sound.read_u16();
        }

        SoundA >>= 5;

        if(SoundA > 30000 && LightForSound.read_u16() < 10000) { //if the sound and light is above and below certain criteria then the alarm starts

            Count++; //counts 1 loud
            printf("*** ALARM *** \n"); //print alarm start to putty
            BSP_LCD_SetTextColor(LCD_COLOR_RED);
            sprintf(c, "ALARM");//sprintf that combines a string with how many times a loud sound happens
            BSP_LCD_DisplayStringAt(0, LINE(10), (uint8_t *)c, CENTER_MODE);//display the amount of times it has been loud
            BSP_LCD_SetTextColor(LCD_COLOR_WHITE);

        } else if(SoundA > 30000) { //if the sound is loud
            Count++; //counts loudness
            printf("Loud Sound \n"); // tells me its loud on putty
        }

        if(Reset == 1) {
            Count = 0;
            printf("Counter has been reset\n");
            wait_us(2000000);
        }

        if(Button == 1) {
            resetBtn++;
            if(resetBtn >= 2) {
                resetBtn = 0;
                printf("Alarm has been reset \n");
                BSP_LCD_ClearStringLine(10);
            }
        }
        sprintf(b, "Loud Sounds: %d", Count);//sprintf that combines a string with how many times a loud sound happens
        BSP_LCD_DisplayStringAt(0, LINE(9), (uint8_t *)b, CENTER_MODE);//display the amount of times it has been loud


        wait_us(1000000);
    }
}