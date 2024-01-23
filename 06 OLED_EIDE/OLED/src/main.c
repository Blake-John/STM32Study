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

void delay(int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}

void show_start (void)
{
    OLED_ShowString (2, 2, "Hello STM32 !");
}

int main()
{
    OLED_Init ();
    OLED_Clear ();

    show_start ();

    while (1)
    {

    }
    
}
