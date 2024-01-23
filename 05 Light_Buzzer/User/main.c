#include "stm32f10x.h"
#include "BUZZER.h"
#include "LIGHT.h"
#include "delay.h"

int main (void)
{
    B_Init ();
    L_Init ();
    B_ON ();
    Delay_ms (1000);
    B_OFF ();
	
    while (1)
    {
        if (L_Get () == 1)
        {
            B_ON ();
        }
        else
        {
            B_OFF ();
        }
        
    }
    
}
