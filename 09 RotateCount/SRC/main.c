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
#include "RotateEncoder.h"

int16_t num = 0;

int main()
{
    OLED_Init ();
    OLED_ShowString (1, 3, "Hello STM32 !");
    RotateEncoder_Init ();
    
    while (1)
    {
        num += getCount ();
        OLED_ShowSignedNum (3, 5, num, 5);
    }
    
}
