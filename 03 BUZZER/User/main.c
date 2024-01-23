#include "stm32f10x.h"
#include "delay.h"

int main (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    
    GPIO_Init (GPIOB, &GPIO_InitStruct);
    
    while (1)
    {
        GPIO_WriteBit (GPIOB, GPIO_Pin_12, Bit_RESET);
        Delay_ms (500);

        GPIO_WriteBit (GPIOB, GPIO_Pin_12, Bit_SET);
        Delay_ms (500);
    }
    
}
