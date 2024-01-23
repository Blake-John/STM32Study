#include "stm32f10x.h"
#include "KEY.h"
#include "delay.h"

int8_t num = 0;

void KeyInit (void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPD;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    // AFIO
    GPIO_EXTILineConfig (GPIO_PortSourceGPIOA, GPIO_PinSource11);

    // EXTI
    EXTI_InitTypeDef EXTI_InitStruct;
    EXTI_InitStruct.EXTI_Line = EXTI_Line11;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising;
    EXTI_Init (&EXTI_InitStruct);

    // NVIC
    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = EXTI15_10_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init (&NVIC_InitStruct);
}

int8_t getNum (void)
{
    return num;
}

void EXTI15_10_IRQHandler (void)
{
    if (EXTI_GetITStatus (EXTI_Line11) == SET)
    {
        if (num)
        {
            num = 0;
        }
        else
        {
            num = 1;
        }
        
        // while (GPIO_ReadInputDataBit (GPIOA, GPIO_Pin_11) = 1);
    
        EXTI_ClearITPendingBit (EXTI_Line11);
    }
    
}