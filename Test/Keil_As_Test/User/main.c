#include "stm32f10x.h"

int main (void)
{
	// 通过配置寄存器点灯
	// RCC->APB2ENR = 0x00000010;
	// GPIOC->CRH = 0x00300000;
	// GPIOC->ODR = 0x00000000;
	
	// 使用库函数点灯
	// 配置GPIOC外设时钟
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	// 定义一个用于设置GPIO的结构体
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	// 配置端口模式
	GPIO_Init (GPIOC, &GPIO_InitStructure);
	// GPIO_SetBits (GPIOC, GPIO_Pin_13);
	//! 低电平亮，高电平灭， GPIO_SetBits 设置为高电平
	GPIO_ResetBits (GPIOC, GPIO_Pin_13);
	while (1)
	{
	}

}
