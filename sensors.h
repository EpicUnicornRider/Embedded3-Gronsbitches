#include "mbed.h"
#include "TS_DISCO_F746NG.h"
#include "LCD_DISCO_F746NG.h"

#define MAXIMUM_BUFFER_SIZE

LCD_DISCO_F746NG lcd;
TS_DISCO_F746NG ts;
UnbufferedSerial pc(USBTX, USBRX);
AnalogIn Temp(A0); //Readings from temperature sensor
AnalogIn Sound(A1); //Readings from sound sensor
AnalogIn Light(A2); //Readings from light sensor
DigitalOut Heater(D2); //Red LED simulating heater
DigitalOut AC(D4); //Blue LED simulating Air Conditioning
Thread Thread1;
Thread Thread2;
Thread Thread3;
DigitalIn Reset(USER_BUTTON); //Onboard reset for Loudness counter
DigitalIn Button(D8); //Button for alarm reset (press 2 times)

int32_t SoundA = 0;
int32_t LightA = 0;
int Count = 0;
int B = 4275;
int R0 = 100000;
char tempCount[50];
char b[1000];
char a[20];
char c[20];
int resetBtn = 0;

struct locationInput {
    char placering[20];
};

 int getTxtInp(char linie[], int MAX)   //Keyboard reading using PuTTY
{
    int i = 0;
    char ind;

    while(i < MAX-1 && (ind = pc.read(&ind, 1))!= '\r')
        linie[i++] = ind;
    linie[i] = '\0';
    return i;
}

void Sound_thread()
{
    while(true) {

        float f = Sound.read(); //reads the sound
        for(int i=0; i<32; i++) {
            SoundA += Sound.read_u16();
        }

        SoundA >>= 5;

        if(SoundA > 30000 && LightA < 10000) { //if the sound and light is above and below certain criteria then the alarm starts

            Count++; //counts 1 loud
            printf("*** ALARM *** \n"); //print alarm start to putty

            lcd.SetTextColor(LCD_COLOR_RED);
            sprintf(c, "ALARM");//sprintf that combines a string with how many times a loud sound happens
            lcd.DisplayStringAt(0, LINE(8), (uint8_t *)c, CENTER_MODE);//display the amount of times it has been loud
            lcd.SetTextColor(LCD_COLOR_WHITE);

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
                lcd.SetTextColor(LCD_COLOR_BLACK);
                sprintf(c, "ALARM");//sprintf that combines a string with how many times a loud sound happens
                lcd.DisplayStringAt(0, LINE(8), (uint8_t *)c, CENTER_MODE);//display the amount of times it has been loud
                lcd.SetTextColor(LCD_COLOR_WHITE);
            }
        }
        sprintf(b, "Loud Sounds: %d", Count);//sprintf that combines a string with how many times a loud sound happens
        lcd.DisplayStringAt(0, LINE(5), (uint8_t *)b, CENTER_MODE);//display the amount of times it has been loud


        wait_us(1000000);
    }
}

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

void Temperature_thread()
{
    while(true) {

        int a = Temp.read_u16();
        float R = 65536.0/a-1.0;
        R = R0*R;

        float temperature = 1.0/(log(R/R0)/B+1/298.15)-273.15; //Calculating analog input from temperature sensor to show celsius

        sprintf(tempCount, "Temperature: %.1fC", temperature);
        printf("temperature: %.1fC\n", temperature);
        lcd.DisplayStringAt(0, LINE(3), (uint8_t *)tempCount, CENTER_MODE); //Display text and temperature readings on LCD display
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

void Startup()
{
    lcd.Clear(LCD_COLOR_BLUE);
    lcd.SetBackColor(LCD_COLOR_BLUE);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    wait_us(300);
    lcd.DisplayStringAt(0, LINE(5), (uint8_t *)"STARTING UP", CENTER_MODE);     //Startup screen with the text "STARTING UP"
    wait_us(1000000);
    int antal = 0;
    char tal = 49;
    antal = int(tal);
    printf("\n%c = ASCII %d\n", tal, antal);

    lcd.Clear(LCD_COLOR_BLACK);
    lcd.SetBackColor(LCD_COLOR_BLACK);
    lcd.SetTextColor(LCD_COLOR_WHITE);
    /*
    if(antal > 48 && antal < 58) {
        char tmp[4];
        int i;
        tmp[0] = tal;
        tmp[1] = '\0';
        antal = atoi(tmp);

        locationInput enheder[antal]; //Write location using PuTTY
        printf("\nTest %d structure(s):\n", antal);
        for(i=0; i<antal; i++) {
            printf("%s\n", "Indtast placering: ");
            getTxtInp(enheder[i].placering, 20);
        }
        for(i=0; i<antal; i++) {
            printf("%s\t", enheder[i].placering);
            sprintf(a, "Placering: %s", enheder[i].placering);
            lcd.DisplayStringAt(0, LINE(1), (uint8_t *)a, CENTER_MODE); //Display text and location input on LCD display
        }
    } else {
        printf("Forkert antal!\n");
    }
    */
}