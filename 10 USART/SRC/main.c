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

   OLED_ShowString (1, 1, "Receive : ");
   // SerialSendByte ('A');

   // uint8_t arry[] = {0x42, 0x43, 0x44, 0x45};

   // SerialSendArray (arry, 4);
   // SerialSendNum (12345, 5);

   // printf ("Num = %d\r\n", 666);
   // char string[100];
   // sprintf (string, "Num = %d\r\n", 666);
   // SerialSendString (string);

   SerialPrintf ("Num = %d\r\n", 666);

   while (1)
   {
      if (GetFlag () == 1)
      {
         uint8_t data = GetData ();
         SerialSendByte (data);
         OLED_ShowHexNum (2, 1, data, 2);
      }
      
      
   }
       
}
