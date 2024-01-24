#include "Serial.h"

uint8_t flag = 0;

char Rx_data[100];

void SerialInit (void)
{
    // 开启时钟
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1, ENABLE);
    RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA, ENABLE);

    // 初始化 GPIO 引脚
    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init (GPIOA, &GPIO_InitStruct);

    // 开启 USART 外设

    // 初始化 USART
    USART_InitTypeDef USART_InitStruct;
    USART_InitStruct.USART_BaudRate = 9600; // 波特率
    USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None; //使用流控
    USART_InitStruct.USART_Mode = USART_Mode_Tx | USART_Mode_Rx; // 配置输出还是输入
    USART_InitStruct.USART_Parity = USART_Parity_No; // 设置无校验/奇偶校验
    USART_InitStruct.USART_StopBits = USART_StopBits_1; // 设置停止位长度
    USART_InitStruct.USART_WordLength = USART_WordLength_8b; // 设置数据帧长度
    USART_Init (USART1, &USART_InitStruct);

    USART_Cmd (USART1, ENABLE);

    USART_ITConfig (USART1, USART_IT_RXNE, ENABLE);

    NVIC_PriorityGroupConfig (NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStruct;
    NVIC_InitStruct.NVIC_IRQChannel = USART1_IRQn;
    NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStruct.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init (&NVIC_InitStruct);
}


void SerialSendByte (uint8_t byte)
{
    USART_SendData (USART1, byte);
    while (USART_GetFlagStatus (USART1, USART_FLAG_TXE) == RESET);
    // 标志位会自动清零，与中断有所区别
}

void SerialSendArray (uint8_t* array, uint16_t length)
{
    for (uint16_t i = 0; i < length; i++)
    {
        SerialSendByte (array[i]);
    }
}

void SerialSendString (char* string)
{
    for (uint8_t i = 0; string[i] != '\0'; i++)
    {
        SerialSendByte (string[i]);
    }
    
}

void SerialSendNum (uint32_t num, uint8_t length)
{
    for (uint32_t i = 0; i < length; i++)
    {
        SerialSendByte (num / (int)pow (10, length - i - 1) % 10 + '0');
    }
    
}

// int fputc (int ch, FILE *f)
// {
//     SerialSendByte (ch);
//     return ch;
// }

void SerialPrintf (char* format, ...)
{
    char string[100];
    va_list arg;
    va_start (arg, format);
    vsprintf (string, format, arg);
    va_end (arg);
    SerialSendString (string);
}

// void SerialSendPackage (uint8_t length)
// {
//     SerialSendByte (0xFF);
//     SerialSendArray (Tx_data, length);
//     SerialSendByte (0xFE);
// }


// uint8_t GetFlag (void)
// {
//     if (flag == 1)
//     {
//         flag = 0;
//         return 1;
//     }

//     return 0;
    
// }

// uint8_t* GetData (void)
// {
//     return Rx_data;
// }


void USART1_IRQHandler (void)
{
    static uint8_t state = 0;
    static uint8_t pdata = 0;

    if (USART_GetITStatus (USART1, USART_IT_RXNE) == SET)
    {
        uint8_t buffer = USART_ReceiveData (USART1);
        if (state == 0)
        {
            if (buffer == '@' && flag == 0)
            {
                state = 1;
                pdata = 0;
            }
        }
        else if (state == 1)
        {
            if (buffer == '\r')
            {
                state = 2;
            }
            else
            {
                Rx_data[pdata] = buffer;
                pdata++;
            }     
        }
        else if (state == 2)
        {
            if (buffer == '\n')
            {
                Rx_data[pdata] = '\0';
                state = 0;
                flag = 1;
                
            }
        }
        
        USART_ClearITPendingBit (USART1, USART_IT_RXNE);
    }
    
}

