

/**
 ******************************************************************************
 *
 * @file        MG32x02z_RGB_MBIA045_API.c
 * @brief       The MBIA045 LED Driver C file.
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
#include "MG32x02z_RGB_MBIA045_API.h"

#if MG32x02z_USBD_KEYBOARD_RGB_EN == API_RGB_MBIA045

/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

//Module mapping
#define LED_URTX                       URT2
#define API_LED_URT_IRQ                URT123_IRQn
#define API_LEDDataLatch_IRQHandler    URT123_IRQHandler

//GPIO
#define API_SPI_CLK_SPI0_CLK()         IOMB->CR2.W = 0x0000200A
#define API_SPI_CLK_URTn_TX()          IOMB->CR2.W = 0x0000400A
#define API_SPI_D0_GPIO()              IOMB->CR3.W = 0x0000000A
#define API_SPI_D0_SPI0_MOSI()         IOMB->CR3.W = 0x0000200A

#define API_SPI_D0_PIN                 PB3

//For MBI5042 status control.
#define API_LED_IDLE                   0x00000000

#define API_LED_CNTMASK                0x000000FF
#define API_LED_bDATALATCH             0x00000100
#define API_LED_aDATALACTH             0x00000200

#define API_LED_bGLOBALLATCH           0x00001000
#define API_LED_aGLOBALLATCH           0x00002000

//MBI5045 
#define LED_DATA_LACTH_URTDATA         0xFF
#define LED_GLOBAL_LACTH_URTDATA       0xF5

#define LED_SHIFT_BYTE                 32

#define LED_DATA_LATCH_DMA_BYTE        5
#define LED_DATA_LATCH_TIME            16
#define LED_DATA_LATCH_BYTE            (16*2*3)                              // 16 channel * 16bit (2 byte) * 3 MBIA045
#define LED_DATA_LATCH_UPDATE          (LED_DATA_LATCH_BYTE/(3*2))           
#define LED_DATA0_LATCH_FIRST          (LED_DATA_LATCH_BYTE - 1)             //  1st MBIA045 first data 
#define LED_DATA1_LATCH_FIRST          (LED_DATA_LATCH_BYTE - 3)             //  2nd MBIA045 first data
#define LED_DATA2_LATCH_FIRST          (LED_DATA_LATCH_BYTE - 5)             //  3rd MBIA045 first data


/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

static uint8_t   API_LED_UpdateDataBuf[LED_DATA_LATCH_BYTE];

static uint8_t   API_RGB_Scenery[API_RGB_TotalLine][LED_DATA_LATCH_BYTE];
static uint8_t   API_RGB_SceneryTmp[API_RGB_TotalLine][LED_DATA_LATCH_BYTE];
    
static uint8_t   LED_RainTable[17] = {0xFF, 0x77, 0x2A, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x77, 0x2A, 0x08, 0x00, 0x00};
  
static uint8_t   API_LED_pUpdateDataBuf;                                     // API_LED_UpdateDataBuf pointer
static uint8_t   LED_DataLatch_Tmp;
static uint8_t   LED_DataLatch_LastBit;

static uint8_t   LED_RainDelay;
static uint8_t   LED_RainCNT;
static uint8_t   LED_RainUpdateEvent;

/* Private function prototypes -----------------------------------------------*/
static void API_MBIA045_EnableWriteConfiguration_Trigger(void);
static void API_MBIA045_WriteConfiguration_Trigger(uint16_t ConfigurationData );
static void API_MBIA045_GlobalLatch_Trigger(void);

void API_RGBData_IRQHandler(void);
void API_LEDDataLatch_IRQHandler(void);

/**
 *******************************************************************************
 * @brief	    RGB Data buffer to default.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGBLedDriverData_DeInit(void)
{
    uint32_t RGBLDD_DeInitTmp;

    for(RGBLDD_DeInitTmp = 0; RGBLDD_DeInitTmp < LED_DATA_LATCH_BYTE; RGBLDD_DeInitTmp++)
    {
        API_LED_UpdateDataBuf[RGBLDD_DeInitTmp]= 0;
    }
    
//    API_LED_UpdateDataBuf[0]  = 0x00;    // 
//    API_LED_UpdateDataBuf[1]  = 0x00;    // None
//    API_LED_UpdateDataBuf[2]  = 0x00;    // 
//    API_LED_UpdateDataBuf[3]  = 0x00;    // ";" B
//    API_LED_UpdateDataBuf[4]  = 0x00;    // 
//    API_LED_UpdateDataBuf[5]  = 0x77;    // "F5" B
//    
//    // OUT14 (G)(U1,U3,U4) = (G4,G9,)
//    API_LED_UpdateDataBuf[6]  = 0x00;    // 
//    API_LED_UpdateDataBuf[7]  = 0x00;    // None
//    API_LED_UpdateDataBuf[8]  = 0x00;    // 
//    API_LED_UpdateDataBuf[9]  = 0x00;    // ";" R
//    API_LED_UpdateDataBuf[10] = 0x00;    // 
//    API_LED_UpdateDataBuf[11] = 0x77;    // "F5" R
//    
//    // OUT13 (R)(U1,U3,U4) = (R4,R9,)
//    API_LED_UpdateDataBuf[12] = 0x00;    // 
//    API_LED_UpdateDataBuf[13] = 0x00;    // None
//    API_LED_UpdateDataBuf[14] = 0x00;    // 
//    API_LED_UpdateDataBuf[15] = 0x00;    // ";" G
//    API_LED_UpdateDataBuf[16] = 0x00;    // 
//    API_LED_UpdateDataBuf[17] = 0x77;    // "F5" G
//    
//    /* Confirm complete */
//    // OUT12 (B)(U1,U3,U4) = (B3,B8,)
//    API_LED_UpdateDataBuf[18] = 0x00;    // 
//    API_LED_UpdateDataBuf[19] = 0x00;    // None
//    API_LED_UpdateDataBuf[20] = 0x00;    // 
//    API_LED_UpdateDataBuf[21] = 0x00;    // "P" B
//    API_LED_UpdateDataBuf[22] = 0x00;    // 
//    API_LED_UpdateDataBuf[23] = 0x2A;    // "F4" B
//    
//    // OUT11 (G)(U1,U3,U4) = (G3,G8,)
//    API_LED_UpdateDataBuf[24] = 0x00;    // 
//    API_LED_UpdateDataBuf[25] = 0x00;    // None
//    API_LED_UpdateDataBuf[26] = 0x00;    // 
//    API_LED_UpdateDataBuf[27] = 0x00;    // "P" R
//    API_LED_UpdateDataBuf[28] = 0x00;    // 
//    API_LED_UpdateDataBuf[29] = 0x2A;    // "F4" R
//    
//    // OUT10 (R)(U1,U3,U4) = (R3,R8,)
//    API_LED_UpdateDataBuf[30] = 0x00;    // 
//    API_LED_UpdateDataBuf[31] = 0x00;    // None
//    API_LED_UpdateDataBuf[32] = 0x00;    // 
//    API_LED_UpdateDataBuf[33] = 0x00;    // "P" G
//    API_LED_UpdateDataBuf[34] = 0x00;    // 
//    API_LED_UpdateDataBuf[35] = 0x2A;    // "F4" G
//    
//    /* Confirm complete */
//    // OUT09 (B)(U1,U3,U4) = (B2,B7,)
//    API_LED_UpdateDataBuf[36] = 0x00;    // 
//    API_LED_UpdateDataBuf[37] = 0x00;    // None
//    API_LED_UpdateDataBuf[38] = 0x00;    // 
//    API_LED_UpdateDataBuf[39] = 0x00;    // "0" B
//    API_LED_UpdateDataBuf[40] = 0x00;    // 
//    API_LED_UpdateDataBuf[41] = 0x08;    // "F3" B
//    
//    // OUT08 (G)(U1,U3,U4) = (G2,G7,)
//    API_LED_UpdateDataBuf[42] = 0x00;    // 
//    API_LED_UpdateDataBuf[43] = 0x00;    // None
//    API_LED_UpdateDataBuf[44] = 0x00;    // 
//    API_LED_UpdateDataBuf[45] = 0x00;    // "0" R
//    API_LED_UpdateDataBuf[46] = 0x00;    // 
//    API_LED_UpdateDataBuf[47] = 0x08;    // "F3" R
//    
//    // OUT07 (R)(U1,U3,U4) = (R2,R7,)
//    API_LED_UpdateDataBuf[48] = 0x00;    // 
//    API_LED_UpdateDataBuf[49] = 0x00;    // None
//    API_LED_UpdateDataBuf[50] = 0x00;    // 
//    API_LED_UpdateDataBuf[51] = 0x00;    // "0" G
//    API_LED_UpdateDataBuf[52] = 0x00;    // 
//    API_LED_UpdateDataBuf[53] = 0x08;    // "F3" G
//    
//    /* Confirm complete */
//    // OUT06 (B)(U1,U3,U4) = (B1,B6,B11)
//    API_LED_UpdateDataBuf[54] = 0x00;    // 
//    API_LED_UpdateDataBuf[55] = 0x00;    // "Text" B
//    API_LED_UpdateDataBuf[56] = 0x00;    // 
//    API_LED_UpdateDataBuf[57] = 0x00;    // "F10" B
//    API_LED_UpdateDataBuf[58] = 0x00;    // 
//    API_LED_UpdateDataBuf[59] = 0x00;    // "F2" B
//    
//    // OUT05 (G)(U1,U3,U4) = (G1,G6,G11)
//    API_LED_UpdateDataBuf[60] = 0x00;    // 
//    API_LED_UpdateDataBuf[61] = 0x00;    // "Text" R
//    API_LED_UpdateDataBuf[62] = 0x00;    // 
//    API_LED_UpdateDataBuf[63] = 0x00;    // "F10" R
//    API_LED_UpdateDataBuf[64] = 0x00;    // 
//    API_LED_UpdateDataBuf[65] = 0x00;    // "F2" R
//    
//    // OUT04 (R)(U1,U3,U4) = (R1,R6,R11) ???
//    API_LED_UpdateDataBuf[66] = 0x00;    // 
//    API_LED_UpdateDataBuf[67] = 0x00;    // "Text" G
//    API_LED_UpdateDataBuf[68] = 0x00;    // 
//    API_LED_UpdateDataBuf[69] = 0x00;    // "F10" G
//    API_LED_UpdateDataBuf[70] = 0x00;    // 
//    API_LED_UpdateDataBuf[71] = 0x00;    // "F2" G
//    
//    /* Confirm complete */                              
//    // OUT03 (B)(U1,U3,U4) = (B0,B5,B10) 
//    API_LED_UpdateDataBuf[72] = 0x00;    // 
//    API_LED_UpdateDataBuf[73] = 0x00;    // "." B
//    API_LED_UpdateDataBuf[74] = 0x00;    // 
//    API_LED_UpdateDataBuf[75] = 0xFF;    // "F6" B
//    API_LED_UpdateDataBuf[76] = 0x00;    // 
//    API_LED_UpdateDataBuf[77] = 0x00;    // "F1" B
//    
//    // OUT02 (G)(U1,U3,U4) = (G0,G5,G10)
//    API_LED_UpdateDataBuf[78] = 0x00;    // 
//    API_LED_UpdateDataBuf[79] = 0x00;    // "." R
//    API_LED_UpdateDataBuf[80] = 0x00;    // 
//    API_LED_UpdateDataBuf[81] = 0xFF;    // "F6" R
//    API_LED_UpdateDataBuf[82] = 0x00;    // 
//    API_LED_UpdateDataBuf[83] = 0x00;    // "F1" R
//    
//    // OUT01 (R)(U1,U3,U4) = (R0,R5,R10)
//    API_LED_UpdateDataBuf[84] = 0x00;    // 
//    API_LED_UpdateDataBuf[85] = 0x00;    // "." G
//    API_LED_UpdateDataBuf[86] = 0x00;    // 
//    API_LED_UpdateDataBuf[87] = 0xFF;    // "F6" G
//    API_LED_UpdateDataBuf[88] = 0x00;    // 
//    API_LED_UpdateDataBuf[89] = 0x00;    // "F1" G
//    /**/
//    // OUT00 (Null)
//    API_LED_UpdateDataBuf[90] = 0x00;    // 
//    API_LED_UpdateDataBuf[91] = 0x00;    // None
//    API_LED_UpdateDataBuf[92] = 0x00;    // 
//    API_LED_UpdateDataBuf[93] = 0x00;    // None
//    API_LED_UpdateDataBuf[94] = 0x00;    // 
//    API_LED_UpdateDataBuf[95] = 0x00;    // None
    
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
    API_LED_pUpdateDataBuf = 0;
    LED_DataLatch_Tmp      = 0;
    LED_DataLatch_LastBit  = 0;
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
    URT_BRG_TypeDef         URT_BRG;
    URT_Data_TypeDef        DataDef;
    DMA_BaseInitTypeDef     MBIA045_DMA;
    
    /*URT Inital (Use for make up number of clocks) */
    #if 1
        //Set BaudRate
        URT_BRG.URT_InternalClockSource = URT_BDClock_PROC;
        URT_BRG.URT_BaudRateMode = URT_BDMode_Separated;
        URT_BRG.URT_PrescalerCounterReload = 0;	                    //Set PSR
        URT_BRG.URT_BaudRateCounterReload  = 0;	                    //Set RLR
        URT_BaudRateGenerator_Config(LED_URTX, &URT_BRG);   		//BR115200 = f(CK_URTx)/(PSR+1)/(RLR+1)/(OS_NUM+1)
        URT_BaudRateGenerator_Cmd(LED_URTX, ENABLE);	            //Enable BaudRateGenerator
        //TX/RX Clock
        URT_TXClockSource_Select(LED_URTX, URT_TXClock_Internal);	//URT_TX use BaudRateGenerator
        URT_RXClockSource_Select(LED_URTX, URT_RXClock_Internal);	//URT_RX use BaudRateGenerator
        URT_TXOverSamplingSampleNumber_Select(LED_URTX, 1);	        //Set TX OS_NUM
        URT_RXOverSamplingSampleNumber_Select(LED_URTX, 1);	        //Set RX OS_NUM
        URT_RXOverSamplingMode_Select(LED_URTX, URT_RXSMP_3TIME);
        URT_TX_Cmd(LED_URTX, ENABLE);	                            //Enable TX
        URT_RX_Cmd(LED_URTX, ENABLE);	                            //Enable RX 

        //Set Data character config
        DataDef.URT_TX_DataLength  = URT_DataLength_7;
        DataDef.URT_RX_DataLength  = URT_DataLength_7;
        DataDef.URT_TX_DataOrder   = URT_DataTyped_LSB;
        DataDef.URT_RX_DataOrder   = URT_DataTyped_LSB;
        DataDef.URT_TX_Parity      = URT_Parity_No;
        DataDef.URT_RX_Parity      = URT_Parity_No;
        DataDef.URT_TX_StopBits    = URT_StopBits_0_5;
        DataDef.URT_RX_StopBits    = URT_StopBits_0_5;
        DataDef.URT_TX_DataInverse = DISABLE;
        DataDef.URT_RX_DataInverse = DISABLE;
        URT_DataCharacter_Config(LED_URTX, &DataDef);
        
        //TX signal inverse
        URT_TXInverse_Cmd(LED_URTX,ENABLE);
        
        //Enable URT Interrupt
        URT_IT_Config(LED_URTX, URT_IT_TC, ENABLE);
        URT_ITEA_Cmd(LED_URTX, ENABLE);
        NVIC_EnableIRQ(API_LED_URT_IRQ);
        
        //Enable URT
        URT_Cmd(LED_URTX, ENABLE);
    #endif
    /*DMA Inital*/
    #if 1
        DMA_Cmd(ENABLE);  
        DMA_Channel_Cmd(DMAChannel0, ENABLE);
        
        
        DMA_BaseInitStructure_Init(&MBIA045_DMA);
        MBIA045_DMA.DMAChx = DMAChannel0;
        MBIA045_DMA.DMALoopCmd           = DISABLE;
        MBIA045_DMA.DestDINCSel          = ENABLE;  
        MBIA045_DMA.SrcSymSel            = DMA_MEM_Read;
        MBIA045_DMA.DestSymSel           = DMA_SPI0_TX;
        MBIA045_DMA.BurstDataSize        = DMA_BurstSize_1Byte;
        MBIA045_DMA.DMATransferNUM       = (LED_SHIFT_BYTE-1);
        DMA_Base_Init(&MBIA045_DMA);    
        
        DMAChannel0->B.W = DMAChannel0->B.W | DMA_CH0B_CH0_SINC_mask_w;
        DMA->STA.W = DMA_FLAG_CH0_TCF;
    #endif
    /*
    Set MBIA045 :
      1. 10-bit PWM counter mode    
      2. Enable GCLK rising / falling edge trigger.
    */
    API_MBIA045_EnableWriteConfiguration_Trigger();
    API_MBIA045_WriteConfiguration_Trigger(0x02BA);
    
}

/**
 *******************************************************************************
 * @brief	   Trigger Data Latch.
 * @details     
 * @return      
 * @exception   
 * @note       SDI can't control in LE = H. 
 *******************************************************************************
 */
void API_RGB_UpdateDataTrigger(void)
{

    LED_RainDelay ++;
    if(LED_RainDelay >= 250)
    {
        LED_RainUpdateEvent = 1;
        LED_RainDelay = 0;
    }
    
    if (LED_RainUpdateEvent != 0)
    {
        LED_RainUpdateEvent = 0;
        
        LED_RainCNT++;
        if(LED_RainCNT > 10)
        {
            LED_RainCNT = 0;
        }
        
        /* Update F1 ~ F6 LED data */
        API_LED_UpdateDataBuf[77] = LED_RainTable [LED_RainCNT +5];     // "F1" B
        API_LED_UpdateDataBuf[83] = LED_RainTable [LED_RainCNT +5];     // "F1" R
        API_LED_UpdateDataBuf[89] = LED_RainTable [LED_RainCNT +5];     // "F1" G

        API_LED_UpdateDataBuf[59] = LED_RainTable [LED_RainCNT +4];     // "F2" B
        API_LED_UpdateDataBuf[65] = LED_RainTable [LED_RainCNT +4];     // "F2" R
        API_LED_UpdateDataBuf[71] = LED_RainTable [LED_RainCNT +4];     // "F2" G
           
        API_LED_UpdateDataBuf[41] = LED_RainTable [LED_RainCNT +3];     // "F3" B
        API_LED_UpdateDataBuf[47] = LED_RainTable [LED_RainCNT +3];     // "F3" R
        API_LED_UpdateDataBuf[53] = LED_RainTable [LED_RainCNT +3];     // "F3" G
        
        API_LED_UpdateDataBuf[23] = LED_RainTable [LED_RainCNT +2];     // "F4" B
        API_LED_UpdateDataBuf[29] = LED_RainTable [LED_RainCNT +2];     // "F4" R
        API_LED_UpdateDataBuf[35] = LED_RainTable [LED_RainCNT +2];     // "F4" G    
        
        API_LED_UpdateDataBuf[5]  = LED_RainTable [LED_RainCNT +1];     // "F5" B
        API_LED_UpdateDataBuf[11] = LED_RainTable [LED_RainCNT +1];     // "F5" R
        API_LED_UpdateDataBuf[17] = LED_RainTable [LED_RainCNT +1];     // "F5" G
        
        API_LED_UpdateDataBuf[75] = LED_RainTable [LED_RainCNT];        // "F6" G
        API_LED_UpdateDataBuf[81] = LED_RainTable [LED_RainCNT];        // "F6" G
        API_LED_UpdateDataBuf[87] = LED_RainTable [LED_RainCNT];        // "F6" G
        
        
    }
    
    /*LED software flow status*/
    API_RGB_CTR.RGB_UpdateStatus = (API_LED_bDATALATCH   | API_LED_aDATALACTH   | LED_DATA_LATCH_TIME );

    /*DMA byte */
    DMAChannel0->NUM.W = LED_DATA_LATCH_DMA_BYTE;                                   // Set SPI DMA byte.
                                                                                    
    /*SPI DMA */                                                                    
    SPI0->CR0.W = SPI0->CR0.W | SPI_CR0_DMA_TXEN_mask_w;                            // Enable DMA of SPI module.
                                                                                    
    /*DMA data source*/                                                             
    DMAChannel0->SSA.W = (uint32_t)(&API_LED_UpdateDataBuf[0]);                     
    API_LED_pUpdateDataBuf = LED_DATA_LATCH_DMA_BYTE;                               // Set next API_LED_UpdateDataBuf pointer.
                                                                                
    SPI0->CR2.W           = 0x00080000;                                             // LE = L + SPI Data bit = 8bit
    LED_DataLatch_Tmp     = (API_LED_UpdateDataBuf[API_LED_pUpdateDataBuf]>>1);
    LED_DataLatch_LastBit = API_LED_UpdateDataBuf[API_LED_pUpdateDataBuf] & 0x01;
    DMAChannel0->A.W      = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w;             // DMA request
    
    SPI0->INT.W = SPI_INT_TX_IE_mask_w | SPI_INT_IEA_mask_w;                        // SPI Interrupt enable : SPI_IEA + SPI_TX
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
    if( API_RGB_CTR.RGB_UpdateStatus & API_LED_bDATALATCH)
    {          
        API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus & ((uint32_t)(~API_LED_bDATALATCH));
        API_LED_pUpdateDataBuf = API_LED_pUpdateDataBuf + 1;        
        while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
        SPI0->CR2.W    = 0x00070000;                                                        // LE is L + SPI Data bit = 7bit  
        SPI0->STA.W    = SPI_STA_TXF_mask_w;
        SPI0->INT.W    = SPI_INT_IEA_mask_w;
        SPI0->TDAT.B[0]= LED_DataLatch_Tmp;
        
    }
    if( API_RGB_CTR.RGB_UpdateStatus & API_LED_aDATALACTH)
    {
        while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
        
        SPI0->CR2.W = 0x01080000;                                                           // LE is H + SPI Data bit = 8bit 
        
        API_SPI_D0_PIN = LED_DataLatch_LastBit;
        API_SPI_D0_GPIO();
        
        API_SPI_CLK_URTn_TX();                                                              // SPI_CLK function = URTn_TX
        LED_URTX->TDAT.B[0] = LED_DATA_LACTH_URTDATA;                                       // Send URT TX Data.(Make up 1 clock in LE is H)
        API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus - 1; 
        DMA->STA.W = DMA_FLAG_CH0_TCF;        
        return;        
    }                                                                                       
    
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}

    SPI0->CR2.W = 0x00080000;                                                           // LE is L + SPI Data bit = 8bit 
    API_RGB_CTR.RGB_UpdateStatus = API_LED_IDLE;
    SPI0->INT.W = SPI_INT_IEA_mask_w;
    DMA->STA.W = DMA_FLAG_CH0_TCF;
    return; 
}

/**
 *******************************************************************************
 * @brief	    URT IRQ Handler
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_LEDDataLatch_IRQHandler(void)
{
    LED_URTX->STA.W = URT_STA_TCF_mask_w;

    API_SPI_CLK_SPI0_CLK();                                                                      // SPI_CLK function = SPI0_CLK
    API_SPI_D0_SPI0_MOSI();
    
    if( API_RGB_CTR.RGB_UpdateStatus & API_LED_aDATALACTH)
    {
        /*Send Next Data Latch*/
        if( (API_RGB_CTR.RGB_UpdateStatus & API_LED_CNTMASK)!=0)
        {
            SPI0->CR2.W        = 0x00080000;                                                   // LE = Low
            DMAChannel0->SSA.W = (uint32_t)(&API_LED_UpdateDataBuf[API_LED_pUpdateDataBuf]);   // Set DMA data source.
            DMAChannel0->A.W   = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w;                   // DMA request
            SPI0->CR0.W        = (0x00A00911 | SPI_CR0_DMA_TXEN_mask_w);                       // Enable SPI0 TX DMA
            SPI0->STA.W        = (SPI_STA_TXF_mask_w | SPI_STA_TCF_mask_w);
            SPI0->INT.W        = SPI_INT_TX_IE_mask_w | SPI_INT_IEA_mask_w;                    // SPI Interrupt enable : SPI_IEA + SPI_TX 
            
            API_LED_pUpdateDataBuf       = API_LED_pUpdateDataBuf + 5;
            API_RGB_CTR.RGB_UpdateStatus = API_RGB_CTR.RGB_UpdateStatus | API_LED_bDATALATCH;
            LED_DataLatch_Tmp            = (API_LED_UpdateDataBuf[API_LED_pUpdateDataBuf]>>1);
            LED_DataLatch_LastBit        = API_LED_UpdateDataBuf[API_LED_pUpdateDataBuf] & 0x01;
            return;
        }
        /*Data Latch complete.*/
        API_MBIA045_GlobalLatch_Trigger();
        
        /*Change ARGB power line*/
        API_AllRGB_OFF();
        GPIO_ClearPortBit(GPIOB, API_RGB_Y0_PIN);
        
        /*Trigger GCLK0 , GCLK1 output.*/
        __NOP();
        __NOP();
        __NOP();
        API_RGB_GCLK_TRG_PIN = 1;                                                               // Trigger GCLK_0 , GCLK_1 output
        API_RGB_GCLK_TRG_PIN = 0;
    }
    SPI0->CR2.W = 0x00080000;                                                                   // LE is L + SPI Data bit = 8bit
    API_RGB_CTR.RGB_UpdateStatus = API_LED_IDLE;
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
    uint8_t RGB_UpNLData_Tmp;
    
    if( RGB_UpdateNewData == ENABLE)
    {
        for( RGB_UpNLData_Tmp = 0; RGB_UpNLData_Tmp < LED_DATA_LATCH_BYTE; RGB_UpNLData_Tmp++)
        {
            // Updata Led data.
            API_RGB_Scenery[API_RGB_CTR.RGB_LINE_ON][RGB_UpNLData_Tmp] = API_RGB_SceneryTmp[API_RGB_CTR.RGB_LINE_ON][RGB_UpNLData_Tmp];                                               
            API_LED_UpdateDataBuf[RGB_UpNLData_Tmp]                    = API_RGB_Scenery[API_RGB_CTR.RGB_LINE_ON][RGB_UpNLData_Tmp];   
        }
    }
    else
    {
        for( RGB_UpNLData_Tmp = 0; RGB_UpNLData_Tmp < LED_DATA_LATCH_BYTE; RGB_UpNLData_Tmp++)
        {
            API_LED_UpdateDataBuf[RGB_UpNLData_Tmp] = API_RGB_Scenery[API_RGB_CTR.RGB_LINE_ON][RGB_UpNLData_Tmp];
        }  
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
    uint16_t API_RGB_UDramaDLineTmp;
    
    for( API_RGB_UDramaTmp = 0; API_RGB_UDramaTmp < API_RGB_KBTotalColume; API_RGB_UDramaTmp++)
    {
        API_RGB_UDramaDLineTmp   = ((API_RGB_PWMData_Table[API_RGB_UDramaLine ][ API_RGB_UDramaTmp] & API_RGB_PWMIC_MASK)>>API_RGB_PWMIC_SHIFT);
        API_RGB_UDramaDataTmp    = ( API_RGB_PWMData_Table[API_RGB_UDramaLine ][ API_RGB_UDramaTmp] & API_RGB_PWMDATA_MASK);
        
        if(API_RGB_UDramaDLineTmp < API_RGB_TotalLine)
        {
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp]    = 0;
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp+1]  = 0;
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp+6]  = 0;
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp+7]  = 0;
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp+12] = 0;
            API_RGB_SceneryTmp[API_RGB_UDramaDLineTmp][API_RGB_UDramaDataTmp+13] = API_RGB_UDramaTmp * 11;
        }
    }
}


/**
 *******************************************************************************
 * @brief	   Trigger Global Latch.
 * @details     
 * @return      
 * @exception   
 * @note       SDI can't control in LE = H.  
 *******************************************************************************
 */
static void API_MBIA045_GlobalLatch_Trigger(void)
{
    URT_ITEA_Cmd(LED_URTX, DISABLE);
    
    SPI0->CR2.W     = 0x000D0000;                                       // LE = L + SPI Data bit = 13bit
    SPI0->TDAT.H[0] = 0x0000;                                           // Global latch data don't care
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
    SPI0->CR2.W     = 0x01080000;                                       // LE is H
    API_SPI_CLK_URTn_TX();                                              // SPI_CLK function = URTn_TX
    LED_URTX->TDAT.B[0] = LED_GLOBAL_LACTH_URTDATA;                     // Send URT TX Data.(Make up 3 clock in LE is H)
    while((LED_URTX->STA.W & URT_STA_TCF_mask_w)==0){__NOP();} 
    SPI0->CR2.W = 0x00080000;                                           // LE is L + SPI Data bit = 8bit
    API_SPI_CLK_SPI0_CLK();                                             // SPI_CLK function = SPI0_CLK
    
    URT_ITEA_Cmd(LED_URTX, ENABLE);
}


/**
 *******************************************************************************
 * @brief	    Trigger Enable Write Configuration.
 * @details     
 * @return      
 * @exception   
 * @note        about 3.6us
 *******************************************************************************
 */
static void API_MBIA045_EnableWriteConfiguration_Trigger(void)
{
    SPI0->CR2.W     = 0x010F0000;                                       // LE = H + SPI Data bit = 15bit
    SPI0->TDAT.H[0] = 0x0000;
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
    SPI0->CR2.W     = 0x00080000;                                       // LE is L + SPI Data bit = 8bit 
}


/**
 *******************************************************************************
 * @brief	   Trigger Write Configuration.
 * @details     
 * @return      
 * @exception   
 * @note       about 4.2us 
 *******************************************************************************
 */
static void API_MBIA045_WriteConfiguration_Trigger(uint16_t ConfigurationData )
{
    ctype     API_LED_WriteConfiguration;                               // For Write Configuration buffer.  
    
    API_LED_WriteConfiguration.H[0] = API_LED_WriteConfiguration.H[1] = ConfigurationData;
    
    SPI0->CR2.W     = 0x00100000;                                       // LE = L + SPI Data bit = 32bit
    SPI0->TDAT.W    = API_LED_WriteConfiguration.W;
    API_LED_WriteConfiguration.B[2] = (API_LED_WriteConfiguration.B[1]>>3);
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
    SPI0->CR2.W     = 0x00050000;                                       // LE = L + SPI Data bit = 5bit
    SPI0->TDAT.B[0] = API_LED_WriteConfiguration.B[2];
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
    SPI0->CR2.W     = 0x010B0000;                                       // LE = H + SPI Data bit = 11bit
    SPI0->TDAT.H[0] = API_LED_WriteConfiguration.H[0];
    while((SPI0->STA.W & SPI_STA_TCF_mask_w)==0){__NOP();}
    SPI0->CR2.W     = 0x00080000;                                       // LE is L + SPI Data bit = 8bit 
}


#endif









