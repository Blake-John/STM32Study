#include "stm32f10x.h"
#include "delay.h"

int main (void)
{
    // 开启A引脚时钟
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
    // 初始化GPIOA
    // 1. 创建 GPIO_InitStruct 并设置其值
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_3 | GPIO_Pin_6;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    // 2. 利用 GPIOA 设置引脚， GPIO_InitStruct 设置模式、引脚号，速度
    GPIO_Init (GPIOA, &GPIO_InitStruct);
    // void GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_InitTypeDef *GPIO_InitStruct)
    // #define GPIOA               ((GPIO_TypeDef *) GPIOA_BASE)
    // GPIO_SetBits (GPIOA, GPIO_Pin_0);
    // GPIO_ResetBits (GPIOA, GPIO_Pin_0);
    
    while (1)
    {
        GPIO_Write (GPIOA, ~0x0001); // 0000 0000 0000 0001
        Delay_ms (500);

        GPIO_Write (GPIOA, ~0x0008); // 0000 0000 0000 1000
        Delay_ms (500);

        GPIO_Write (GPIOA, ~0x0040); // 0000 0000 0100 0000
        Delay_ms (500);
    }
    
}
