#include "stm32f10x.h"
#include "LED.h"

/// @brief Init the LED GPIO Peripheral Clock
/// @param  
void LED_Init (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOA, &GPIO_InitStruct);

    GPIO_SetBits (GPIOA, GPIO_Pin_0 | GPIO_Pin_3);
}

/// @brief Turn on the A0 LED
/// @param  
void LED0_ON (void)
{
    GPIO_ResetBits (GPIOA, GPIO_Pin_0);
}

/// @brief Turn off the A0 LED
/// @param  
void LED0_OFF (void)
{
    GPIO_SetBits (GPIOA, GPIO_Pin_0);
}

/// @brief reverse the led state
/// @param  
void LED0_REVERSE (void)
{
    if (GPIO_ReadOutputDataBit (GPIOA, GPIO_Pin_0) == 0)
    {
        GPIO_SetBits (GPIOA, GPIO_Pin_0);
    }
    else
    {
        GPIO_ResetBits (GPIOA, GPIO_Pin_0);
    }
    
}

/// @brief Turn on the A3 LED
/// @param  
void LED3_ON (void)
{
    GPIO_ResetBits (GPIOA, GPIO_Pin_3);
}

/// @brief Turn off the A3 LED
/// @param  
void LED3_OFF (void)
{
    GPIO_SetBits (GPIOA, GPIO_Pin_3);
}

void LED3_REVERSE (void)
{
    if (GPIO_ReadOutputDataBit (GPIOA, GPIO_Pin_3) == 0)
    {
        GPIO_SetBits (GPIOA, GPIO_Pin_3);
    }
    else
    {
        GPIO_ResetBits (GPIOA, GPIO_Pin_3);
    }
}
