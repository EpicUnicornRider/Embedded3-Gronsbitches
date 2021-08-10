#include <cstdio>
#include "connection.h"
Thread Thread1; //thread

AnalogIn Sound(A0); //sound input

int32_t SoundA = 0; //store the sound

int Count = 0; //counts the loud noices
char SoundPrint[10];
//sound thread
void Sound_thread()
{

    while (true) {

        float f = Sound.read(); //reads the sound
        for(int i=0; i<32; i++) {
            SoundA = Sound.read_u16();
        }

        sprintf(SoundPrint,"%i", SoundA);

        if(SoundA > 50000) { //if the sound and light is above and below certain criteria then the alrm starts

            Count++; //counts 1 loud

            printf("*** ALARM ***\n"); //print alarm start to putty
            printf("%s\n", SoundPrint);
            wait_us(2000000);
        }
        
    }
}