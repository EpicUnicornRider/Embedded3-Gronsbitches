#include "mbed.h"
#include <stdio.h>
#include <string>
#include "stm32746g_discovery_lcd.h"

int icounter = 10;

char stringforcountdown[] = "";

void LCDStart() {
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
}

void clearscreen() {
    BSP_LCD_Clear(LCD_COLOR_BLACK);
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
}

void startuptext() {
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(-56, LINE(3), (uint8_t*)"Alarm: ", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
    BSP_LCD_DisplayStringAt(56, LINE(3), (uint8_t*)"DISABLED", CENTER_MODE);
}

void enablealarm() {
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(-50, LINE(3), (uint8_t*)"Alarm: ", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(50, LINE(3), (uint8_t*)"ARMED", CENTER_MODE);
}

void disablealarm() {
    clearscreen();
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(-56, LINE(3), (uint8_t*)"Alarm: ", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_LIGHTGREEN);
    BSP_LCD_DisplayStringAt(56, LINE(3), (uint8_t*)"DISABLED", CENTER_MODE);
}

void alarm() {
    clearscreen();
    BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
    BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
    BSP_LCD_DisplayStringAt(-56, LINE(3), (uint8_t*)"Alarm: ", CENTER_MODE);
    BSP_LCD_SetTextColor(LCD_COLOR_RED);
    BSP_LCD_DisplayStringAt(56, LINE(3), (uint8_t*)"ARMED", CENTER_MODE);
    BSP_LCD_DisplayStringAt(0, LINE(7), (uint8_t*)"ALARM! INTRUTION DETECTED!", CENTER_MODE);
}

void countdownalarmscreen() {

    icounter = 10;

    while(icounter != 0) {

        clearscreen();
        BSP_LCD_SetBackColor(LCD_COLOR_BLACK);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(-56, LINE(3), (uint8_t*)"Alarm: ", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_RED);
        BSP_LCD_DisplayStringAt(56, LINE(3), (uint8_t*)"ARMING", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
        BSP_LCD_DisplayStringAt(-25, LINE(7), (uint8_t*)"Alarm enabled in: ", CENTER_MODE);
        BSP_LCD_SetTextColor(LCD_COLOR_RED);

        sprintf(stringforcountdown, "%d", icounter);
        BSP_LCD_DisplayStringAt(145, LINE(7), (uint8_t*)stringforcountdown, CENTER_MODE);

        icounter--;

        wait_us(1000000);
    }

    clearscreen();
    enablealarm();
}