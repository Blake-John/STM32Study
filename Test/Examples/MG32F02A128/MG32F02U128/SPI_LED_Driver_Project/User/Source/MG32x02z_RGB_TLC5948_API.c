


/**
 ******************************************************************************
 *
 * @file        MG32x02z_RGB_TLC5948_API.c
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
#include "MG32x02z_RGB_TLC5948_API.h"

#if MG32x02z_USBD_KEYBOARD_RGB_EN == API_RGB_TLC5948


/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define API_LED_SHIFT_BYTE             32

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t  API_LED_UpdateDataBuf[3][API_LED_SHIFT_BYTE];
static void     API_RGB_UpdateControlTrigger(void);

static uint8_t  API_RGB1_SceneryTmp[API_RGB_TotalLine][API_LED_SHIFT_BYTE];                      
static uint8_t  API_RGB2_SceneryTmp[API_RGB_TotalLine][API_LED_SHIFT_BYTE];     
static uint8_t  API_RGB3_SceneryTmp[API_RGB_TotalLine][API_LED_SHIFT_BYTE]; 

static uint8_t  API_RGB1_Scenery[API_RGB_TotalLine][API_LED_SHIFT_BYTE];                      
static uint8_t  API_RGB2_Scenery[API_RGB_TotalLine][API_LED_SHIFT_BYTE];     
static uint8_t  API_RGB3_Scenery[API_RGB_TotalLine][API_LED_SHIFT_BYTE];     

static uint8_t  LED_RainTable[17] = {0xFF, 0x77, 0x2A, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x77, 0x2A, 0x08, 0x00, 0x00};
    
static uint8_t  Delay_CNT;
static uint8_t  API_RGB1_Order;

/* Private function prototypes -----------------------------------------------*/
void API_RGBData_IRQHandler(void);


/**
 *******************************************************************************
 * @brief	    LED Driver Data buffer to default.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGBLedDriverData_DeInit(void)
{
//    uint32_t RGBLDD_DeInitTmp;

//    for(RGBLDD_DeInitTmp = 0; RGBLDD_DeInitTmp < API_LED_SHIFT_BYTE; RGBLDD_DeInitTmp++)
//    {
//        API_LED_UpdateDataBuf[0][RGBLDD_DeInitTmp] = 0;
//        API_LED_UpdateDataBuf[1][RGBLDD_DeInitTmp] = 0;
//        API_LED_UpdateDataBuf[2][RGBLDD_DeInitTmp] = 0;
//    }
    
//    //====================================================================================
//    //PWM SPI data Inital
    API_LED_UpdateDataBuf[0][0] = 0x00;                 // OUT15 [31:16], PWM 1/16
    API_LED_UpdateDataBuf[0][1] = LED_RainTable[0];     // OUT15 [15:0]
    API_LED_UpdateDataBuf[0][2] = 0x00;                 // OUT14 [31:16], PWM 1/16
    API_LED_UpdateDataBuf[0][3] = LED_RainTable[0];     // OUT14 [15:0]
    API_LED_UpdateDataBuf[0][4] = 0x00;                 // OUT13 [31:16], PWM 1/16
    API_LED_UpdateDataBuf[0][5] = LED_RainTable[0];     // OUT13 [15:0]
    
    API_LED_UpdateDataBuf[0][6] = 0x00;                 // OUT12 [31:16], PWM 4/16
    API_LED_UpdateDataBuf[0][7] = LED_RainTable[1];     // OUT12 [15:0]
    API_LED_UpdateDataBuf[0][8] = 0x00;                 // OUT11 [31:16], PWM 4/16
    API_LED_UpdateDataBuf[0][9] = LED_RainTable[1];     // OUT11 [15:0]
    API_LED_UpdateDataBuf[0][10] = 0x00;                // OUT10 [31:16], PWM 4/16
    API_LED_UpdateDataBuf[0][11] = LED_RainTable[1];    // OUT10 [15:0]
    
    API_LED_UpdateDataBuf[0][12] = 0x00;                // OUT9 [31:16], PWM 7/16
    API_LED_UpdateDataBuf[0][13] = LED_RainTable[2];    // OUT9 [15:0]
    API_LED_UpdateDataBuf[0][14] = 0x00;                // OUT8 [31:16], PWM 7/16
    API_LED_UpdateDataBuf[0][15] = LED_RainTable[2];    // OUT8 [15:0]
    API_LED_UpdateDataBuf[0][16] = 0x00;                // OUT7 [31:16], PWM 7/16
    API_LED_UpdateDataBuf[0][17] = LED_RainTable[2];    // OUT7 [15:0]
    
    API_LED_UpdateDataBuf[0][18] = 0x00;                // OUT6 [31:16], PWM 10/16
    API_LED_UpdateDataBuf[0][19] = LED_RainTable[3];    // OUT6 [15:0]
    API_LED_UpdateDataBuf[0][20] = 0x00;                // OUT5 [31:16], PWM 10/16
    API_LED_UpdateDataBuf[0][21] = LED_RainTable[3];    // OUT5 [15:0]
    API_LED_UpdateDataBuf[0][22] = 0x00;                // OUT4 [31:16], PWM 10/16
    API_LED_UpdateDataBuf[0][23] = LED_RainTable[3];    // OUT4 [15:0]
    
    API_LED_UpdateDataBuf[0][24] = 0x00;                // OUT3 [31:16], PWM 13/16
    API_LED_UpdateDataBuf[0][25] = LED_RainTable[4];    // OUT3 [15:0]
    API_LED_UpdateDataBuf[0][26] = 0x00;                // OUT2 [31:16], PWM 13/16
    API_LED_UpdateDataBuf[0][27] = LED_RainTable[4];    // OUT2 [15:0]
    API_LED_UpdateDataBuf[0][28] = 0x00;                // OUT1 [31:16], PWM 13/16
    API_LED_UpdateDataBuf[0][29] = LED_RainTable[4];    // OUT1 [15:0]
    
    API_LED_UpdateDataBuf[0][30] = 0x00;                // OUT0 [31:16], PWM 00/16
    API_LED_UpdateDataBuf[0][31] = LED_RainTable[5];    // OUT0 [15:0]   
}


/**
 *******************************************************************************
 * @brief	    LED Driver control parameter initial.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGBLedControlParameter_Init(void)
{
    uint32_t RGBLDD_DeInitTmp;
    uint32_t RGBLDD_DeInitTmp2;
    
    //====================================================================================
    //RGB Data Initial
    for( RGBLDD_DeInitTmp = 0; RGBLDD_DeInitTmp < API_RGB_TotalLine ; RGBLDD_DeInitTmp++)
    {
        for( RGBLDD_DeInitTmp2 = 0 ; RGBLDD_DeInitTmp2 < API_LED_SHIFT_BYTE; RGBLDD_DeInitTmp2++)
        {
            API_RGB3_Scenery[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0x00; 
            API_RGB1_Scenery[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0x00;
            API_RGB2_Scenery[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0x00;    
                
            API_RGB1_SceneryTmp[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0;
            API_RGB2_SceneryTmp[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0;
            API_RGB3_SceneryTmp[RGBLDD_DeInitTmp][RGBLDD_DeInitTmp2] = 0;
        }
    }
}

/**
 *******************************************************************************
 * @brief	   Initial the other module for different LED driver.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGBLed_Init(void)
{
    DMA_BaseInitTypeDef     LED_DMA;
    
    /*DMA Initial ( DMA Channel0 )*/
    DMA_Cmd(ENABLE);  
    DMA_Channel_Cmd(DMAChannel0, ENABLE);
        
        
    DMA_BaseInitStructure_Init(&LED_DMA);
    LED_DMA.DMAChx = DMAChannel0;
    LED_DMA.DMALoopCmd           = DISABLE;
    LED_DMA.DestDINCSel          = ENABLE;  
    LED_DMA.SrcSymSel            = DMA_MEM_Read;
    LED_DMA.DestSymSel           = DMA_SPI0_TX;
    LED_DMA.BurstDataSize        = DMA_BurstSize_1Byte;
    LED_DMA.DMATransferNUM       = (API_LED_SHIFT_BYTE-1);
    DMA_Base_Init(&LED_DMA);    
    
    
    /*LED parameter initial*/
    API_RGB_CTR.RGB1_SceneryTmpBuf    = &API_RGB1_SceneryTmp[0][0];
    API_RGB_CTR.RGB2_SceneryTmpBuf    = &API_RGB2_SceneryTmp[0][0];
    API_RGB_CTR.RGB3_SceneryTmpBuf    = &API_RGB3_SceneryTmp[0][0];
    
}

/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        Need 110us in SPI Baudrate is 12Mhz
 *******************************************************************************
 */
void API_RGB_UpdateDataTrigger(void)
{
    API_RGB_CTR.RGB_UpdateStatus = ( API_RGB_UPDATE_GS_BLANK0 | API_RGB_UPDATE_GS_BLANK1 |
                                     API_RGB_UPDATE_GS        | API_RGB3_GS_DATA1        |
                                     API_RGB2_GS_DATA0        | API_RGB2_GS_DATA1        |   
                                     API_RGB1_GS_DATA0        | API_RGB1_GS_DATA1 );
    
    API_RGB_DATA_SIZE(API_RGB_GS_DATA0_BIT);                                                // Set SPI transmit data size = 9-bit
    DMAChannel0->NUM.W = ( API_LED_SHIFT_BYTE - 1);                                         // Setting DMA transfer 31 bytes
    DMAChannel0->B.W = DMAChannel0->B.W | DMA_CH0B_CH0_SINC_mask_w;                         // DMA source memory transfer address auto increased.
    SPI_NSSOutputStatusControl_SW(SPI0, DRV_Low);                                           // SPI NSS = 0
    SPI0->TDAT.H[0] = ( API_RGB_GS_SELECT | API_LED_UpdateDataBuf[0][0]);                   // Transmit shift(1-bit) + 1Byte dat 
}

/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGBData_IRQHandler(void)
{
    API_RGB_CLEAR_UPDATEFALG();
    
    
    if((API_RGB_CTR.RGB_UpdateStatus & API_RGB_UPDATE_CONTROL ) == API_RGB_UPDATE_CONTROL)      // When API RGB update control is hppened
    {
        if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_LATCH )
        {
            API_RGB_DATA_SIZE(API_RGB_CONTROL_RESERVE_BIT);
            
            API_RGB_DATA_SEND1BYTE( (API_RGB_UPDATE_CONTROL >> 24));
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB_CONTROL_LATCH);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_RESERVE)
        {
            SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;
            
            DMA->STA.W = DMA_FLAG_CH0_TCF;
            DMAChannel0->NUM.W = API_RGB_CONTROL_RESERVE_BYTE;
            API_RGB_DMA_SIZE( API_RGB_CONTROL_RESERVE_BYTE);
            DMAChannel0->B.W = DMAChannel0->B.W &(~DMA_CH0B_CH0_SINC_mask_w);
            DMAChannel0->SSA.W = (uint32_t)(&API_RGB_CTR.RGB_DUMMY);
            
            API_RGB_DMA_TRG();
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB_CONTROL_RESERVE);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_FUNC1)
        {
            API_RGB_DATA_SIZE(API_RGB_CONTROL_FUNC1_BIT);
            
            API_RGB_DATA_SEND1BYTE( API_RGB_CTR.Function.B[2]);
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB_CONTROL_FUNC1);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_FUNC0)
        {
            API_RGB_DATA_SIZE(API_RGB_CONTROL_FUNC0_BIT);

            API_RGB_DATA_SEND2BYTE( API_RGB_CTR.Function.H[0]);
        
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB_CONTROL_FUNC0);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_BC)
        {
            API_RGB_DATA_SIZE(API_RGB_CONTROL_BC_BIT);

            API_RGB_DATA_SEND1BYTE( API_RGB_CTR.Brightness);
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB_CONTROL_BC);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_DC)
        {
            SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;
            
            DMA->STA.W = DMA_FLAG_CH0_TCF;
            DMAChannel0->NUM.W = API_RGB_CONTROL_DC_BYTE;
            DMAChannel0->B.W = DMAChannel0->B.W | DMA_CH0B_CH0_SINC_mask_w;
            DMAChannel0->SSA.W = (uint32_t)(&API_RGB_CTR.Dot[0]);

            API_RGB_DMA_TRG();
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus - 1;
            
            if( (API_RGB_CTR.RGB_UpdateStatus & API_RGB_CONTROL_CNTMASK) != 0 )
            {
                API_RGB_CTR.RGB_UpdateStatus =( API_RGB_CTR.RGB_UpdateStatus | 
                                                API_RGB_UPDATE_CONTROL       |  API_RGB_CONTROL_LATCH   | API_RGB_CONTROL_RESERVE | 
                                                API_RGB_CONTROL_FUNC0        |  API_RGB_CONTROL_FUNC1   | API_RGB_CONTROL_BC      | API_RGB_CONTROL_DC );
                return;
            }
            else if((API_RGB_CTR.RGB_UpdateStatus &  API_RGB_UPDATE_GS_BLANK0) == API_RGB_UPDATE_GS_BLANK0)
            {
                API_RGB_CTR.RGB_UpdateStatus = API_RGB_UPDATE_GS_BLANK0;
                
                return;
            }
            else if((API_RGB_CTR.RGB_UpdateStatus &  API_RGB_UPDATE_GS_BLANK1) == API_RGB_UPDATE_GS_BLANK1)
            {
                API_RGB_CTR.RGB_UpdateStatus = API_RGB_UPDATE_GS_BLANK1;
                
                return;
            }
            
            
            API_RGB_CTR.RGB_UpdateStatus = API_LED_IDLE;
            
            return;
        }
    }
    else if((API_RGB_CTR.RGB_UpdateStatus & API_RGB_UPDATE_GS ) == API_RGB_UPDATE_GS)           // When API RGB update event is happened
    {
        if( API_RGB_CTR.RGB_UpdateStatus & API_RGB3_GS_DATA1)                                   // API_RGB3_GS_DATA1
        {
            SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;                                // Enable SPI and DMA
            API_RGB_DATA_SIZE(API_RGB_GS_DATA1_BIT);                                            // Update SPI data size
            DMA->STA.W = DMA_FLAG_CH0_TCF;                                                      // Clear DMA TCF flag
            DMAChannel0->SSA.W = (uint32_t)(&API_LED_UpdateDataBuf[2][1]);                      // Update DMA source 
            DMAChannel0->A.W = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w;
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~(API_RGB3_GS_DATA1));
                                                                                                // Clear GS data event
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB2_GS_DATA0)
        {
            API_RGB_DATA_SIZE(API_RGB_GS_DATA0_BIT);
            
            SPI0->TDAT.H[0] = ( API_RGB_GS_SELECT | API_LED_UpdateDataBuf[1][0]);
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB2_GS_DATA0);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB2_GS_DATA1)
        {
            SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;
            
            API_RGB_DATA_SIZE(API_RGB_GS_DATA1_BIT);
            DMA->STA.W = DMA_FLAG_CH0_TCF;
            DMAChannel0->SSA.W = (uint32_t)(&API_LED_UpdateDataBuf[1][1]);
            DMAChannel0->A.W = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w;
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB2_GS_DATA1);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB1_GS_DATA0)
        {
            API_RGB_DATA_SIZE(API_RGB_GS_DATA0_BIT);
            
            SPI0->TDAT.H[0] = ( API_RGB_GS_SELECT | API_LED_UpdateDataBuf[0][0] );
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB1_GS_DATA0);
            return;
        }
        else if( API_RGB_CTR.RGB_UpdateStatus & API_RGB1_GS_DATA1)
        {
            SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;
            
            API_RGB_DATA_SIZE(API_RGB_GS_DATA1_BIT);
            DMA->STA.W = DMA_FLAG_CH0_TCF;
            DMAChannel0->SSA.W = (uint32_t)(&API_LED_UpdateDataBuf[0][1]);
            DMAChannel0->A.W = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w;
            
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & (uint32_t)(~API_RGB1_GS_DATA1);
            return;
        }
        else if( (API_RGB_CTR.RGB_UpdateStatus & ( API_RGB_UPDATE_GS_BLANK0 | API_RGB_UPDATE_GS_BLANK1)) == ( API_RGB_UPDATE_GS_BLANK0 | API_RGB_UPDATE_GS_BLANK1))
        {                                                                                       // API_RGB_UPDATE_GS_BLANK0 || API_RGB_UPDATE_GS_BLANK1
            SPI0->CR2.W = SPI0->CR2.W | SPI_CR2_NSS_SWO_mask_w;                                 // SPI NSS = 1
            API_RGB_CTR.Function.MBIT.BLANK  = 1;                                               // Set BLANK
            API_RGB_UpdateControlTrigger();                                                     /* Call update control trigger */
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus | API_RGB_UPDATE_GS_BLANK0;
                                                                                                // Update RGB_UpdateStatus
            return;
        }
        
        API_RGB_CTR.RGB_UpdateStatus = API_LED_IDLE;                                            // When others state, set RGB_UpdateStatus idle 
        SPI0->CR2.W = SPI0->CR2.W | SPI_CR2_NSS_SWO_mask_w;                                     // SPI NSS = 1
        
        return;
    }
    else if( API_RGB_CTR.RGB_UpdateStatus == API_RGB_UPDATE_GS_BLANK0)                          // When BLANK0 event is happed
    {
        SPI0->CR2.W = SPI0->CR2.W | SPI_CR2_NSS_SWO_mask_w;                                     // SPI NSS = 1
        API_RGB_CTR.Function.MBIT.BLANK  = 0;                                                   // Set Function BLANK = 0
        API_RGB_UpdateControlTrigger();                                                         /* Call update control trigger */
        API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus | API_RGB_UPDATE_GS_BLANK1; // Update RGB_UpdateStatus 
        return;
    }
    else if( API_RGB_CTR.RGB_UpdateStatus == API_RGB_UPDATE_GS_BLANK1)                          // When BLANK1 event is happed
    {
        API_AllRGB_OFF();                                                                       // Disable output                                                            
        SPI0->CR2.W = SPI0->CR2.W | SPI_CR2_NSS_SWO_mask_w;                                     // SPI NSS = 1
        API_RGB_GCLK_TRG_PIN = 1;                                                               // Tringger TM36
        API_RGB_GCLK_TRG_PIN = 0;
        
        switch( API_RGB_CTR.RGB_LINE_ON)
        {
            case 0:
                    GPIO_ClearPortBit( GPIOB, API_RGB_Y0_PIN);
                    break;
//            case 1:
//            case 10:                
//                    GPIO_ClearPortBit( GPIOB, API_RGB_PWPIN_TABLE[API_RGB_CTR.RGB_LINE_ON]);
//                    break;
            default:
//                    GPIO_ClearPortBit( GPIOD, API_RGB_PWPIN_TABLE[API_RGB_CTR.RGB_LINE_ON]); 
                    break;
        }
        
//        GPIO_ClearPortBit( GPIOB, API_RGB_Y0_PIN);
        
        API_RGB_CTR.RGB_UpdateStatus = API_LED_IDLE;                                            // RGB update state to idle
        return;
    }
    
    SPI0->CR2.W = SPI0->CR2.W | SPI_CR2_NSS_SWO_mask_w;                                         // SPI NSS  = 1
}

/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGB_UpdateNextLineData( FunctionalState RGB_UpdateNewData)
{
    (void)RGB_UpdateNewData;
    
    
    
    if(Delay_CNT >= 200)
    {
        Delay_CNT = 0;
        
        if(API_RGB1_Order >= 10)
        {
            API_RGB1_Order = 0;
        }
        else
        {
            API_RGB1_Order ++;
        }
        
        API_LED_UpdateDataBuf[0][0] = 0x00;                             // OUT15 [31:16], PWM 1/16
        API_LED_UpdateDataBuf[0][1] = LED_RainTable[API_RGB1_Order];    // OUT15 [15:0]
        API_LED_UpdateDataBuf[0][2] = 0x00;                             // OUT14 [31:16], PWM 1/16
        API_LED_UpdateDataBuf[0][3] = LED_RainTable[API_RGB1_Order];    // OUT14 [15:0]
        API_LED_UpdateDataBuf[0][4] = 0x00;                             // OUT13 [31:16], PWM 1/16
        API_LED_UpdateDataBuf[0][5] = LED_RainTable[API_RGB1_Order];    // OUT13 [15:0]
        
        API_LED_UpdateDataBuf[0][6] = 0x00;                                 // OUT12 [31:16], PWM 4/16
        API_LED_UpdateDataBuf[0][7] = LED_RainTable[(API_RGB1_Order + 1)];  // OUT12 [15:0]
        API_LED_UpdateDataBuf[0][8] = 0x00;                                 // OUT11 [31:16], PWM 4/16
        API_LED_UpdateDataBuf[0][9] = LED_RainTable[(API_RGB1_Order + 1)];  // OUT11 [15:0]
        API_LED_UpdateDataBuf[0][10] = 0x00;                                // OUT10 [31:16], PWM 4/16
        API_LED_UpdateDataBuf[0][11] = LED_RainTable[(API_RGB1_Order + 1)]; // OUT10 [15:0]
        
        API_LED_UpdateDataBuf[0][12] = 0x00;                                // OUT9 [31:16], PWM 7/16
        API_LED_UpdateDataBuf[0][13] = LED_RainTable[(API_RGB1_Order + 2)]; // OUT9 [15:0]
        API_LED_UpdateDataBuf[0][14] = 0x00;                                // OUT8 [31:16], PWM 7/16
        API_LED_UpdateDataBuf[0][15] = LED_RainTable[(API_RGB1_Order + 2)]; // OUT8 [15:0]
        API_LED_UpdateDataBuf[0][16] = 0x00;                                // OUT7 [31:16], PWM 7/16
        API_LED_UpdateDataBuf[0][17] = LED_RainTable[(API_RGB1_Order + 2)]; // OUT7 [15:0]
        
        API_LED_UpdateDataBuf[0][18] = 0x00;                                // OUT6 [31:16], PWM 10/16
        API_LED_UpdateDataBuf[0][19] = LED_RainTable[(API_RGB1_Order + 3)]; // OUT6 [15:0]
        API_LED_UpdateDataBuf[0][20] = 0x00;                                // OUT5 [31:16], PWM 10/16
        API_LED_UpdateDataBuf[0][21] = LED_RainTable[(API_RGB1_Order + 3)]; // OUT5 [15:0]
        API_LED_UpdateDataBuf[0][22] = 0x00;                                // OUT4 [31:16], PWM 10/16
        API_LED_UpdateDataBuf[0][23] = LED_RainTable[(API_RGB1_Order + 3)]; // OUT4 [15:0]
        
        API_LED_UpdateDataBuf[0][24] = 0x00;                                // OUT3 [31:16], PWM 13/16
        API_LED_UpdateDataBuf[0][25] = LED_RainTable[(API_RGB1_Order + 4)]; // OUT3 [15:0]
        API_LED_UpdateDataBuf[0][26] = 0x00;                                // OUT2 [31:16], PWM 13/16
        API_LED_UpdateDataBuf[0][27] = LED_RainTable[(API_RGB1_Order + 4)]; // OUT2 [15:0]
        API_LED_UpdateDataBuf[0][28] = 0x00;                                // OUT1 [31:16], PWM 13/16
        API_LED_UpdateDataBuf[0][29] = LED_RainTable[(API_RGB1_Order + 4)]; // OUT1 [15:0]
        
        API_LED_UpdateDataBuf[0][30] = 0x00;                                // OUT0 [31:16], PWM 00/16
        API_LED_UpdateDataBuf[0][31] = LED_RainTable[(API_RGB1_Order + 5)]; // OUT0 [15:0]   
    }
    else
    {
        Delay_CNT ++;
    }
}

/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGB_UpdateDateDramaTmp(void)
{
    uint8_t  API_RGB_UDramaLine = API_RGB_CTR.RGB_RefreshColumn - 6;
    uint8_t  API_RGB_UDramaTmp;
    
    uint16_t API_RGB_UDramaDataTmp;

    for( API_RGB_UDramaTmp = 0; API_RGB_UDramaTmp < API_RGB_KBTotalColume; API_RGB_UDramaTmp++)
    {
        
        API_RGB_UDramaDataTmp       = ( API_RGB_PWMData_Table[API_RGB_UDramaLine ][ API_RGB_UDramaTmp] & API_RGB_PWMDATA_MASK);
        
        
        switch(( API_RGB_PWMData_Table[API_RGB_UDramaLine ][ API_RGB_UDramaTmp] & API_RGB_PWMIC_MASK))
        {
            case API_RGB_PWMIC1:
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp    ] = 0;
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp + 1] = API_KBRGB_BColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp + 2] = 0;
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp + 3] = API_KBRGB_RColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp + 4] = 0;
                                API_RGB_CTR.RGB1_SceneryTmpBuf[API_RGB_UDramaDataTmp + 5] = API_KBRGB_GColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                break;
            case API_RGB_PWMIC2:
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp    ] = 0;
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp + 1] = API_KBRGB_BColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp + 2] = 0;
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp + 3] = API_KBRGB_RColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp + 4] = 0;
                                API_RGB_CTR.RGB2_SceneryTmpBuf[API_RGB_UDramaDataTmp + 5] = API_KBRGB_GColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                break;
            case API_RGB_PWMIC3:
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp    ] = 0;
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp + 1] = API_KBRGB_BColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp + 2] = 0;
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp + 3] = API_KBRGB_RColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp + 4] = 0;
                                API_RGB_CTR.RGB3_SceneryTmpBuf[API_RGB_UDramaDataTmp + 5] = API_KBRGB_GColorScenery[API_RGB_UDramaLine][API_RGB_UDramaTmp];
                                break;
            default:
                                break;
        }
    }
}


/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        Need 110us in SPI Baudrate is 12Mhz
 *******************************************************************************
 */
static void API_RGB_UpdateControlTrigger(void)
{
    API_RGB_CTR.RGB_UpdateStatus = ( API_RGB_UPDATE_CONTROL  | API_RGB_CONTROL_RESERVE |        //
                                     API_RGB_CONTROL_FUNC0   | API_RGB_CONTROL_FUNC1   | 
                                     API_RGB_CONTROL_BC | API_RGB_CONTROL_DC | 
                                     API_RGB_DRIVER_TOTAL);


    API_RGB_DATA_SIZE(API_RGB_CONTROL_RESERVE_BIT);                                             // Set SPI transmit data size = 8-bit
    API_RGB_CTR.RGB_DUMMY = 0xFF;                                                               // Setting DMA transmit DUMMY = 0xFF
    SPI0->CR2.W = SPI0->CR2.W & (~SPI_CR2_NSS_SWO_mask_w);                                      // SPI NSS = 0
    SPI0->TDAT.B[0] = (API_RGB_UPDATE_CONTROL >> 24);                                           // Transmit 0x80
}


#endif


