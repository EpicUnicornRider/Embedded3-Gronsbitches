#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

AnalogIn Light(A2); //Readings from light sensor
DigitalOut LED(D2); //LED Socket simulating light on/off

Thread Thread3;

int32_t LightA = 0;
char lights[50];

void Light_thread()
{
    while(true) {

        float g = Light.read(); //read light
        LightA = 0;
        for(int i=0; i<32; i++) {
            LightA += Light.read_u16();
        }

        LightA >>= 5;

        wait_us(5000000);
        
        if(g < 0.3){
            printf("It's dark! Turning on lights...\n");
            LED = 1;
            sprintf(lights, "ON");
            BSP_LCD_SetTextColor(LCD_COLOR_GREEN);
        }
        else{
            printf("There is enough light. Turning off lights...\n");
            LED = 0;
            sprintf(lights, "OFF");
            BSP_LCD_SetTextColor(LCD_COLOR_RED);

        }
        BSP_LCD_ClearStringLine(7);
        BSP_LCD_DisplayStringAt(50, LINE(7), (uint8_t *)lights, CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(-50, LINE(7), (uint8_t *)"Lights: ", CENTER_MODE);

        wait_us(1000000);
    }
}