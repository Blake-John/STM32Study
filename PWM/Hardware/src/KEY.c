#include "stm32f10x.h"
#include "KEY.h"
#include "delay.h"

/// @brief Initialize the key port
/// @param  
void Key_Init (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU; // 上拉输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOB, &GPIO_InitStruct);
}


void Key_InitA (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD; // 下拉输入
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOA, &GPIO_InitStruct);
}


/// @brief get the key state of each port
/// @param  
/// @return the key number tellint which key is pressed
uint8_t Key_Get (void)
{
    uint8_t Keynum = 0;

    if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_0) == 0)
    {
        Delay_ms (20);
        while (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_0) == 0);
        Delay_ms (20);
        Keynum = 1;
    }
    
    if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_10) == 0)
    {
        Delay_ms (20);
        while (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_10) == 0);
        Delay_ms (20);
        Keynum = 2;
    }

    if (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_11) == 1)
    {
        Delay_ms (20);
        while (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_11) == 1);
        Delay_ms (20);
        Keynum =3;
        
    }
    
    if (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9) == 1)
    {
        Delay_ms (20);
        while (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_9) == 1);
        Delay_ms (20);
        Keynum =4;
        
    }
    

    return  Keynum;
}
