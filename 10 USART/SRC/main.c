/*
 * ************************************************
 * 
 *              STM32 blink gcc demo
 * 
 *  CPU: STM32F103C8
 *  PIN: PA1
 * 
 * ************************************************
*/

#include "stm32f10x.h"
#include "OLED.h"
#include "Serial.h"
#include "delay.h"


int main()
{
   OLED_Init ();
   SerialInit ();

   SerialSendByte ('A');

   uint8_t arry[] = {0x42, 0x43, 0x44, 0x45};

   SerialSendArray (arry, 4);
   while (1)
   {
    
   }
       
}
