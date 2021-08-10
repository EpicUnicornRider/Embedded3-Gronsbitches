#include "stm32746g_discovery_lcd.h"

void Dannebrog(){
     BSP_LCD_Clear(LCD_COLOR_DARKGREEN);
     BSP_LCD_SetBackColor(LCD_COLOR_DARKGREEN);
    
    //creating the most beatiful flag
     BSP_LCD_SetTextColor(LCD_COLOR_RED);  
     BSP_LCD_FillRect(127, 61, 226, 150);
     BSP_LCD_SetTextColor(LCD_COLOR_WHITE);
     BSP_LCD_FillRect(192, 61, 25, 150);
     BSP_LCD_FillRect(127, 126, 226, 25);    
}

void LCDStart(){
    BSP_LCD_Init();
    BSP_LCD_LayerDefaultInit(LTDC_ACTIVE_LAYER, LCD_FB_START_ADDRESS);
    BSP_LCD_SelectLayer(LTDC_ACTIVE_LAYER);
}

void startup() {
    //colours that are shown at startup
     BSP_LCD_Clear(LCD_COLOR_GREEN); 
     BSP_LCD_SetBackColor(LCD_COLOR_GREEN);
    HAL_Delay(500);  
     BSP_LCD_Clear(LCD_COLOR_RED);
     BSP_LCD_SetBackColor(LCD_COLOR_RED);
    HAL_Delay(500);    
}