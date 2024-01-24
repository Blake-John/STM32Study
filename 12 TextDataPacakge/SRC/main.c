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
#include "LED.h"
#include <string.h>

uint8_t keynum;

int main()
{
   OLED_Init ();
   SerialInit ();
   LED_Init ();

   OLED_ShowString (1, 1, "Receive : ");
   OLED_ShowString (3, 1, "Send : ");


   while (1)
   {
      if (flag == 1)
      {
         OLED_ShowString (2, 1, "                ");
         OLED_ShowString (2, 1, Rx_data);

         if (strcmp (Rx_data, "LED3_ON") == 0)
         {
            LED3_ON ();
            SerialSendString ("LED A3 is on !\r\n");
            OLED_ShowString (2, 1, "                ");
            OLED_ShowString (2, 1, "LED A3 is on !");
         }
         else if (strcmp (Rx_data, "LED3_OFF") == 0)
         {
            LED3_OFF ();
            SerialSendString ("LED A3 is off !\r\n");
            OLED_ShowString (2, 1, "                ");
            OLED_ShowString (2, 1, "LED A3 is off !");
         }
         
         flag = 0;
      }
      
   }
       
}
