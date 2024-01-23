#include "stm32f10x.h"
#include "delay.h"
#include "LED.h"
#include "KEY.h"

uint8_t Key;

int main (void)
{
    LED_Init ();
    Key_Init ();
    
    LED0_ON ();
    Delay_ms (500);
    LED0_OFF ();

    while (1)
    {
        Key = Key_Get ();
        if (Key == 1)
        {
            LED0_REVERSE ();
        }
        if (Key == 2)
        {
            LED3_REVERSE ();
        }
        
    }
    
}
