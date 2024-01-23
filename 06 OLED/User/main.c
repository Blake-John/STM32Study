#include "stm32f10x.h"
#include "LED.h"
#include "KEY.h"
#include "delay.h"
#include "OLED.h"

int main (void)
{
    OLED_Init ();
    OLED_Clear ();
    OLED_ShowChar (1, 1, 'A');
    OLED_ShowString (1, 3, "Hello, world!");
    OLED_ShowNum (2, 1, 12345, 5);
    OLED_ShowSignedNum (3, 1, 12345, 5);
    OLED_ShowSignedNum (3, 8, -12345, 5);
    OLED_ShowHexNum (4, 1, 0xAA55, 4);
    OLED_ShowBinNum (5, 1, 0xAA55, 16);

    while (1)
    {
        
    }
    
}
