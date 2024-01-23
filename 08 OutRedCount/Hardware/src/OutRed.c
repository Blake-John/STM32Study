#include "stm32f10x.h"
#include "OutRed.h"
#include "delay.h"

uint16_t count;

void OutRed_Init (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);
    // EXTI 和 NVIC 不需要开启时钟
    // NVIC 是内核内的外设，而 RCC 负责管理内核以外的外设

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_14;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init (GPIOB, &GPIO_InitStruct);

    // AFIO 没有专门的库文件，而是在 GPIO 的库文件中
    GPIO_EXTILineConfig (GPIO_PortSourceGPIOB, GPIO_PinSource14);
    // 配置 AFIO 的数据选择器，GPIO_PortSource 是用于输入的端口，GPIO_PinSource 是输入端口连接到的线

    // 配置 EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line14;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;

    EXTI_Init (&EXTI_InitStruct);

    // 配置 NVIC
    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;

    NVIC_Init (&NVIC_InitStruct);
}

void EXTI15_10_IRQHandler (void) 
// 中断函数都是无参无返回值的，而且名字一定要与启动文件中的名字一样，否则无法进入中断
{
    // 判断是否从 EXTI14 进入
    if (EXTI_GetITStatus (EXTI_Line14) == SET)
    {
        if (GPIO_ReadInputDataBit (GPIOB, GPIO_Pin_14) == 0)
        {
            count++;
            
        }
        
        EXTI_ClearITPendingBit (EXTI_Line14);
    }
}

uint16_t getCount (void)
{
    return count;
}