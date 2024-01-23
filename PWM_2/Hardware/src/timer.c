#include "stm32f10x.h"
#include "timer.h"

void Timer_Init(void)
{
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin=GPIO_Pin_1|GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
    GPIO_Init(GPIOA,&GPIO_InitStructure);

    TIM_TimeBaseInitTypeDef Timebase;
    Timebase.TIM_ClockDivision=TIM_CKD_DIV1;
    Timebase.TIM_CounterMode=TIM_CounterMode_Up;
    Timebase.TIM_Period=2000-1;
    Timebase.TIM_Prescaler=720-1;
    TIM_TimeBaseInit(TIM2,&Timebase);

    TIM_OCInitTypeDef OC_Structure;
    OC_Structure.TIM_OCMode=TIM_OCMode_PWM1;
    OC_Structure.TIM_OutputState=ENABLE;
    OC_Structure.TIM_Pulse=10;
    OC_Structure.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM_OC2Init(TIM2,&OC_Structure);
    TIM_OC3Init(TIM2,&OC_Structure);

    TIM_Cmd(TIM2,ENABLE);
}