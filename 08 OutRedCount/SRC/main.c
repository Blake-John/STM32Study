/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "OLED.h"
#include "delay.h"
#include "OutRed.h"

int main()
{
    OLED_Init ();
    OLED_ShowString (1, 1, "Hello STM32 !");
    OutRed_Init ();

    while (1)
    {
        OLED_ShowNum (2, 7, getCount (), 3);
    }
    
}
