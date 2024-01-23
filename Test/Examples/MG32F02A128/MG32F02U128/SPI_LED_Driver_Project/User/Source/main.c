

/**
 ******************************************************************************
 *
 * @file        Sample_main_wizard.C
 * @brief       MG32x02z demo main c Code. 
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.02
 * @date        2023/06/26
 * @author      Megawin Software Center
 * @copyright   Copyright (c) 2017 MegaWin Technology Co., Ltd.
 *              All rights reserved.
 *
 ******************************************************************************* 
 * @par Disclaimer
 * The Demo software is provided "AS IS" without any warranty, either
 * expressed or implied, including, but not limited to, the implied warranties
 * of merchantability and fitness for a particular purpose. The author will
 * not be liable for any special, incidental, consequential or indirect
 * damages due to loss of data or any other reason.
 * These statements agree with the world wide and local dictated laws about
 * authorship and violence against these laws.
 *******************************************************************************
 *******************************************************************************
 */



/* Includes ------------------------------------------------------------------*/
#include "MG32x02z_RGB_API.h"

/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void ChipInit(void);

/* Exported variables --------------------------------------------------------*/
/* Exported functions --------------------------------------------------------*/
/* External vairables --------------------------------------------------------*/



/**
 *******************************************************************************
 * @brief       LED driver IC sample code
 * @details     
 * @return      
 * @exception   
 * @note        Support TLC5948A and MBIA045 (LED driver select by "RGB Function" of "MG32x02z_USBD_Keyboard.h")
 *              LED driver chip update cycle 1ms
 *              Used PWM step 256, duty cycle 50%.
 *              Dot Correction(DC) 7-Bit (128 Steps) with 0% ~ 100%.
 *              Global Brightness Control(BC) 1=7-Bit with 25% ~ 100%.
 *
 * @hardware    Chip Pin            DUT
 *              PB2(SPI_CLK)    <=> SDI(TLC5948A) 
 *              PB3(SPI_MOSI)   <=> DCLK(TLC5948A)
 *              PA8(SPI_NSS)    <=> LE(TLC5948A)
 *              PA1(TM36_OC10)  <=> GCLK(TLC5948A)
 *              PE15(TM36_STR)
 *              PA3(TM36_OC2N)  <=> GCLK, (Not connect)
 *              PB7(GPIO)       <=> Test board LED master switch (Not connect)
 *              PB12(LED_Y0)    <=> Test board LDE Y0 switch (Not connect)
 *              PB11(LED_Y1)    <=> Test board LDE Y1 switch (Not connect)
 *              PD1(LED_Y2)     <=> Test board LDE Y2 switch (Not connect)
 *              PD2(LED_Y3)     <=> Test board LDE Y3 switch (Not connect)
 *              PD3(LED_Y4)     <=> Test board LDE Y4 switch (Not connect)
 *              PD7(LED_Y5)     <=> Test board LDE Y5 switch (Not connect)
 *              PD8(LED_Y6)     <=> Test board LDE Y6 switch (Not connect)
 *              PD9(LED_Y7)     <=> Test board LDE Y7 switch (Not connect)
 *              PD10(LED_Y8)    <=> Test board LDE Y8 switch (Not connect)
 *              PD11(LED_Y9)    <=> Test board LDE Y9 switch (Not connect)
 *              PB13(LED_Y10)   <=> Test board LDE Y10 switch (Not connect)
 *
 *******************************************************************************
 */
int main()
{      
    // ------------------------------------------------------------------------
    // chip initial (User can enable CSC, GPIO, TM, ADC, EXIC ... wizard)
    // ------------------------------------------------------------------------
    ChipInit();
    API_RGB_Init();
    API_RGB_UpdateDataTrigger();
   
    while(1)
    {
        // to do .....
    }
}


