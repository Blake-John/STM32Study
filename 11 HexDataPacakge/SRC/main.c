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
#include "KEY.h"

uint8_t keynum;

int main()
{
   OLED_Init ();
   SerialInit ();
   Key_Init ();

   OLED_ShowString (1, 1, "Receive : ");
   OLED_ShowString (3, 1, "Send : ");

   // Tx_data[4] = 0x45;
   Tx_data[0] = 0x01;
   Tx_data[1] = 0x02;
   Tx_data[2] = 0x03;
   Tx_data[3] = 0x04;

   while (1)
   {
      keynum = Key_Get ();
      if (keynum == 1)
      {
         Tx_data[0]++;
         Tx_data[1]++;
         Tx_data[2]++;
         Tx_data[3]++;
         SerialSendPackage (4);
         for (uint8_t i = 0; i < 4; i++)
         {
            OLED_ShowHexNum (4, 1 + 3 * i, Tx_data[i], 2);
         }
      }
      
      if (GetFlag () == 1)
      {
         OLED_ShowHexNum (2, 1, Rx_data[0], 2);
         OLED_ShowHexNum (2, 4, Rx_data[1], 2);
         OLED_ShowHexNum (2, 7, Rx_data[2], 2);
         OLED_ShowHexNum (2, 10, Rx_data[3], 2);
         // for (uint8_t i = 0; i < 4; i++)
         // {
         //    OLED_ShowHexNum (2, 1 + 3 * i, Rx_data[i], 2);
         // }
         
      }
      
   }
       
}
