#include "stm32f10x.h"
#include "BUZZER.h"

/// @brief Initialize the buzzer port
/// @param  
void B_Init (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOB, &GPIO_InitStruct);

    GPIO_SetBits (GPIOB, GPIO_Pin_12);
}

/// @brief turn on the buzzer
/// @param  
void B_ON (void)
{
    GPIO_ResetBits (GPIOB, GPIO_Pin_12);
}

/// @brief turn off the buzzer
/// @param  
void B_OFF (void)
{
    GPIO_SetBits (GPIOB, GPIO_Pin_12);
}
