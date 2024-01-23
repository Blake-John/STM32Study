#include "stm32f10x.h"
#include "delay.h"

/// @brief us delay
/// @param us the delay period from 0 to 233015
void Delay_us (uint32_t us)
{
    SysTick->LOAD = 72 * us;                    // 设置定时器重装值
    SysTick->VAL = 0x00;                        // 清空当前计数值
    SysTick->CTRL = 0x00000005;                 // 设置时钟源为 HCLK ，启动定时器
    while (!(SysTick->CTRL & 0x00010000));      // 等待计数到 0
    SysTick->CTRL = 0x00000004;                 // 关闭定时器
    
}

/// @brief ms delay
/// @param ms the delay period from 0 to 4294967295
void Delay_ms(uint32_t ms)
{
	while(ms--)
	{
		Delay_us(1000);
	}
}

/// @brief s delay
/// @param s the delay period from 0 to 4294967295
void Delay_s(uint32_t s)
{
	while(s--)
	{
		Delay_ms(1000);
	}
} 

