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
#include"KEY.h"
#include"Timer.h"
#include "OLED.h"

#define LED_PERIPH RCC_APB2Periph_GPIOC
#define LED_PORT GPIOC
#define LED_PIN GPIO_Pin_13

void delay(int x)
{
    for (int i = 0; i < x; i++)
    {
        for (int j = 0; j < 1000; j++)
            __NOP();
    }
}


int main()
{
    Timer_Init();
    OLED_Init ();
    Key_Init();
    Key_InitA ();
    int Duty1=50, Duty2=130;
    TIM_SetCompare2(TIM2,Duty1);
    TIM_SetCompare3 (TIM2, Duty2);
    int key = 0;
    uint8_t dex = 0, dey = 0;
    uint8_t px = 0, py = 0;
    void showx (void)
    {
        OLED_ShowNum (1, 1, dex, 3);
        OLED_ShowChar (1, 4, '.');
        OLED_ShowNum (1, 5, px, 1);
    }
    void showy (void)
    {
        OLED_ShowNum (3, 1, dey, 3);
        OLED_ShowChar (3, 4, '.');
        OLED_ShowNum (3, 5, py, 1);
    }
    showx ();
    showy ();
    while(1)
    {
        key = Key_Get ();
        switch (key)
        {
            case 1:
                Duty1 += 5;
                dex += 4;
                px += 5;
                if (Duty1 > 250)
                {
                    Duty1 = 50;
                    dex = 0;
                    px = 0;
                }
                if (px == 10)
                {
                    px = 0;
                    dex += 1;
                }
                
                TIM_SetCompare2 (TIM2, Duty1);
                showx ();
                break;
            
            case 2:
                Duty2 += 5;
                dey += 4;
                py += 5;
                if (Duty2 > 250)
                {
                    Duty2 = 130;
                    dey = 0;
                    py = 0;
                }
                if (py == 10)
                {
                    py = 0;
                    dey += 1;
                }
                
                TIM_SetCompare3 (TIM2, Duty2);
                showy ();
                break;

            case 3:
                Duty1 -= 5;
                dex -= 5;
                if (Duty1 < 50)
                {
                    Duty1 = 50;
                    dex = 0;
                    px = 0;
                }
                if (px == 0)
                {
                    px += 5;
                }
                else if (px == 5)
                {
                    px -= 5;
                    dex += 1;
                }
                
                TIM_SetCompare2 (TIM2, Duty1);
                showx ();
                break;

            case 4:
                Duty2 -= 5;
                dey -= 5;
                if (Duty2 < 130)
                {
                    Duty2 = 130;
                    dey = 0;
                    py = 0;
                }
                if (py == 0)
                {
                    py += 5;
                }
                else if (py == 5)
                {
                    py -= 5;
                    dey += 1;
                }
                
                TIM_SetCompare3 (TIM2, Duty2);
                showy ();
                break;
        }
    }
}
