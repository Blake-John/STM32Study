
#include "stm32f10x.h"
#include "Encoder.h"

int32_t key;

void EncoderInit (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOB, &GPIO_InitStruct);

    //todo 配置 AFIO 中断引脚选择器
    GPIO_EXTILineConfig (GPIO_PortSourceGPIOB, GPIO_PinSource0);
    GPIO_EXTILineConfig (GPIO_PortSourceGPIOB, GPIO_PinSource1);

    //todo 配置 EXTI 产生中断
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line0 | EXTI_Line1;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init (&EXTI_InitStruct);

    //todo 配置 NVIC 进行中断处理
    
    // 设置中断分组
    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    // 初始化 NVIC
    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI0_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init (&NVIC_InitStruct);

    NVIC_InitStruct.NVIC_IRQChannel = EXTI1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init (&NVIC_InitStruct);
    
}

int32_t getKey (void)
{
    int32_t temp = key;
    key = 0;
    return temp;
}

void EXTI0_IRQHandler (void)
{
    // 判断由哪一个中断线进入，因为 9 - 5， 15 - 10 是同一个中断函数
    if (EXTI_GetITStatus (EXTI_Line0) == SET)
    {
        if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_1) == 0)
        {
            key = -1;
        }
        
        // 清楚中断标志位，防止卡死在中断中
        EXTI_ClearITPendingBit (EXTI_Line0);
    }
    
}

void EXTI1_IRQHandler (void)
{
    if (EXTI_GetITStatus (EXTI_Line1) == SET)
    {
        if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_0) == 0)
        {
            key = +1;
        }
        
        EXTI_ClearITPendingBit (EXTI_Line1);
    }
    
}