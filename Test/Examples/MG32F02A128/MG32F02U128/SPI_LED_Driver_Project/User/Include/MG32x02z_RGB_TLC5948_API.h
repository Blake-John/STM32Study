

/**
 ******************************************************************************
 *
 * @file        MG32x02z_RGB_TLC5948_API.h
 * @brief       The TLC5948 LED Driver C file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2023/04/26
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
#include "MG32x02z.h"
#include "MG32x02z_SPI_DRV.h"
#include "MG32x02z_DMA_DRV.h"
#include "MG32x02z_USBD_Keyboard_API.h"
#include "MG32x02z_RGB_API.h"

#if MG32x02z_USBD_KEYBOARD_RGB_EN == API_RGB_TLC5948

/* Define --------------------------------------------------------------------*/
//SPI    
#define RGB_SPI_DIVIDER            SPI_DIV_2
#define RGB_SPI_INIT_INT           (SPI_INT_TC)
#define RGB_SPI_INIT_INT_STATUS    ENABLE
#define REG_SPI_IDLSTATUS          SPI_DOUT_IDL_LastBit

//GCLK
#define GCLK_TM_PRESCALER          0
#define GCLK_TM_PERIOD             156
#define GCLK_TM_CCxB               78
#define GCLK_TM_REPCOUNTER         0
#define GCLK_TM_REPRELOAD          255




/* Exported functions --------------------------------------------------------*/

void API_RGBLedDriverData_DeInit(void);
void API_RGBLedControlParameter_Init(void);
void API_RGBLed_Init(void);
void API_RGB_UpdateDataTrigger(void);
void API_RGB_UpdateNextLineData( FunctionalState RGB_UpdateNewData);
void API_RGB_UpdateDateDramaTmp(void);

#endif





