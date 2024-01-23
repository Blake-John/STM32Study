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
#include "delay.h"
#include "KEY.h"
#include "timer.h"
#include "OLED.h"
#include "Encoder.h"

uint16_t duty1 = 50, duty2 = 130;
uint32_t px = 0, py = 0;
uint32_t dx = 0, dy = 0;
int kye = 0;

void showx (void)
{
    OLED_ShowString (3, 1, "x : ");
    OLED_ShowNum (3, 5, dx, 3);
    OLED_ShowChar (3, 8, '.');
    OLED_ShowNum (3, 9, px, 1);
}

void showy (void)
{
    OLED_ShowString (4, 1, "y : ");
    OLED_ShowNum (4, 5, dy, 3);
    OLED_ShowChar (4, 8, '.');
    OLED_ShowNum (4, 9, py, 1);
}

int main()
{
    Timer_Init ();
    EncoderInit ();
    KeyInit ();
    OLED_Init ();
    OLED_ShowString (1, 3, "Hello STM32 !");
    showx ();
    showy ();
    TIM_SetCompare2 (TIM2, 50);
    TIM_SetCompare3 (TIM2, 130);

    while (1)
    {
        if (getNum ())
        {
            if (getKey () == 1)
            {
                duty2 += 5;
                dy += 4;
                py += 5;
                if (py == 10)
                {
                    py = 0;
                    dy++;
                }
                if (duty2 > 250)
                {
                    duty2 = 250;
                }
                if (dy >= 108)
                {
                    dy = 108;
                    py = 0;
                }
                TIM_SetCompare3 (TIM2, duty2);
                showy ();
            }

            if (getKey () == -1)
            {
                duty2 -= 5;
                if (dy <= 5)
                {
                    dy = 0;
                    py = 0;
                }
                else
                {
                    dy -= 5;
                    py += 5;
                }
                if (py == 10)
                {
                    py = 0;
                    dy++;
                }
                if (duty2 < 130)
                {
                    duty2 = 130;
                }
                TIM_SetCompare3 (TIM2, duty2);
                showy ();

            }
        }
        else 
        {
            if (getKey () == 1)
            {            
                duty1 += 5;
                dx += 4;
                px += 5;
                if (px == 10)
                {
                    px = 0;
                    dx++;
                }
                if (duty1 > 250)
                {
                    duty1 = 250;
                }
                if (dx >= 180)
                {
                    dx = 180;
                    px = 0;
                }
                TIM_SetCompare2 (TIM2, duty1);
                showx ();
            }

            if (getKey () == -1)
            {
            
                duty1 -= 5;
                if (dx <= 5)
                {
                    dx = 0;
                    px = 0;
                }
                else
                {
                    dx -= 5;
                    px += 5;
                }
                if (px == 10)
                {
                    px = 0;
                    dx++;
                }
                if (duty1 < 50)
                {
                    duty1 = 50;
                }
                TIM_SetCompare2 (TIM2, duty1);
                showx ();
                
            }

        }
    }
}
