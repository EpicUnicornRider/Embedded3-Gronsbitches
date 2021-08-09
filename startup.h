#include "mbed.h"
#include "LCD_DISCO_F746NG.h"

void Startup()
{
    BSP_LCD_Clear(LCD_COLOR_BLUE);
    BSP_LCD_SetBackColor(LCD_COLOR_BLUE);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    wait_us(300);
    BSP_LCD_DisplayStringAt(0, LINE(5), (uint8_t *)"STARTING UP", CENTER_MODE);     //Startup screen with the text "STARTING UP"
    wait_us(1000000);
    int antal = 0;
    char tal = 49;
    antal = int(tal);
    printf("\n%c = ASCII %d\n", tal, antal);

    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    
}