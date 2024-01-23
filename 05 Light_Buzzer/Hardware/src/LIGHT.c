#include "stm32f10x.h"
#include "LIGHT.h"

/// @brief Initialize the Light Sensor port
/// @param  
void L_Init (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOB, &GPIO_InitStruct);
}

/// @brief get the output of the light sensor
/// @param  
/// @return the state of the light sensor 0 or 1
uint8_t L_Get (void)
{
    return GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_13);
}
