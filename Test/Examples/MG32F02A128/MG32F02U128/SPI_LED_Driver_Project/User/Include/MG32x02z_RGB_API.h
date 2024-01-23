

#ifndef __MG32x02z_LED_API_H
#define __MG32x02z_LED_API_H


 /**
 ******************************************************************************
 *
 * @file        MG32x02z_LED_API.h
 * @brief       The LED Code's h file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.00
 * @date        2020/12/13
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
 
#include "MG32x02z.h" 
#include "MG32x02z_SPI.h"
#include "MG32x02z_USBD_Keyboard_API.h"

/**
 * @name LED Mode Define
 *   		
 */ 
///@{

#define API_RGB_DISABLE          0
#define API_RGB_TLC5948          1
#define API_RGB_MBIA045          2

///@}

#if MG32x02z_USBD_KEYBOARD_RGB_EN != API_RGB_DISABLE

/**
 * @name LED Control Related Pin
 *   		
 */ 
///@{

#define API_RGB_ON               0
#define API_RGB_OFF              1


#define API_RGB_ICPW_PIN         PB7
#define API_RGB_GCLK_TRG_PIN     PE15

#define API_RGB_ICPW_ON          API_RGB_ICPW_PIN =  API_RGB_ON
#define API_RGB_ICPW_OFF         API_RGB_ICPW_PIN =  API_RGB_OFF

#define API_RGB_Y0_PIN           PX_Pin_12
#define API_RGB_Y1_PIN           PX_Pin_11
#define API_RGB_Y2_PIN           PX_Pin_1
#define API_RGB_Y3_PIN           PX_Pin_2
#define API_RGB_Y4_PIN           PX_Pin_3
#define API_RGB_Y5_PIN           PX_Pin_7
#define API_RGB_Y6_PIN           PX_Pin_8
#define API_RGB_Y7_PIN           PX_Pin_9
#define API_RGB_Y8_PIN           PX_Pin_10
#define API_RGB_Y9_PIN           PX_Pin_11
#define API_RGB_Y10_PIN          PX_Pin_13

///@}

/*
 * @name RGB Control Related Register 
 *   		
 */ 
///@{
#define API_RGB_CLEAR_UPDATEFALG()          SPI0->STA.W = SPI_TCF
#define API_RGB_CLEAR_REFRESHFLAG()         TM10->STA.W = TMx_TOF

#define API_RGB_DATA_SIZE(__HANDLE__)       SPI0->CR2.MBIT.DSIZE = (__HANDLE__)
#define API_RGB_DATA_SEND1BYTE(__HANDLE__)  SPI0->TDAT.B[0] = (__HANDLE__)     
#define API_RGB_DATA_SEND2BYTE(__HANDLE__)  SPI0->TDAT.H[0] = (__HANDLE__)

#define API_RGB_DMA_SIZE(__HANDLE__)        DMAChannel0->NUM.W = (__HANDLE__)
#define API_RGB_DMA_TRG()                   DMAChannel0->A.W = DMAChannel0->A.W | DMA_CH0A_CH0_REQ_mask_w 
#define API_RGB_DMA_Source(__HANDLE__)      
///@}



/**
 * @name RGB Control Related Define
 *   		
 */ 
///@{  
 
//===========================================================
//RGB Interrupt Relationship
#define API_RGBData_IRQHandler         SPI0_IRQHandler
#define API_RGBTime_IRQHandler         TM1x_IRQHandler                                  
                
//==========================================================
//RGB Key Control Relationship
#define API_RGB_KB_MODE                0xF0
#define API_RGB_KB_SUBMODE             0xF1
#define API_RGB_KB_COLOR               0xF2

                
//===========================================================
//LED Driver IC Control Relationship
#define API_RGB_DRIVER_TOTAL           3                                



                  
                                                     
#define API_LED_IDLE                   0x00000000
                                       
#define API_RGB_UPDATE_MASK            0xF0000000
#define API_RGB_UPDATE_GS              0x10000000
#define API_RGB_UPDATE_GS_BLANK0       0x20000000
#define API_RGB_UPDATE_GS_BLANK1       0x40000000
#define API_RGB_UPDATE_CONTROL         0x80000000
   
     
#define API_RGB1_GS_DATA0              0x00010000
#define API_RGB1_GS_DATA1              0x00020000
#define API_RGB2_GS_DATA0              0x00100000
#define API_RGB2_GS_DATA1              0x00200000
#define API_RGB3_GS_DATA0              0x01000000
#define API_RGB3_GS_DATA1              0x02000000
                                       
                                       
#define API_RGB_GS_SELECT              0x000                                       
                                       
#define API_RGB_GS_DATA0_BIT           9
#define API_RGB_GS_DATA1_BIT           8
                                       
                                       
#define API_RGB_CONTROL_CNTMASK        0x000000FF
#define API_RGB_CONTROL_LATCH          0x00000100
#define API_RGB_CONTROL_RESERVE        0x00000200
#define API_RGB_CONTROL_FUNC0          0x00000400
#define API_RGB_CONTROL_FUNC1          0x00000800
#define API_RGB_CONTROL_BC             0x00001000
#define API_RGB_CONTROL_DC             0x00008000
                                       
#define API_RGB_CONTROL_SELECT         0x80

#define API_RGB_CONTROL_RESERVE_BIT    8
#define API_RGB_CONTROL_FUNC0_BIT      14
#define API_RGB_CONTROL_FUNC1_BIT      4
#define API_RGB_CONTROL_BC_BIT         7
#define API_RGB_CONTROL_DC_BIT         7

#define API_RGB_CONTROL_RESERVE_BYTE   14
#define API_RGB_CONTROL_DC_BYTE        16

//=============================================================
//Total RGB Function Control Relationsip 
#define API_RGB_TotalLine              11
#define API_RGB_TotalColume            15

#define API_RGB_KBTotalLine            6
#define API_RGB_KBTotalColume          23

#define API_RGB_PWMIC_MASK             0xF000
#define API_RGB_PWMDATA_MASK           0x0FFF

#define API_RGB_PWMIC_SHIFT            12

#define API_RGB_PWMIC1                 0x1000
#define API_RGB_PWMIC2                 0x2000
#define API_RGB_PWMIC3                 0x3000

//=============================================================
//Main Status Control Relationship 
#define API_RGB_MAIN_IDLE                          0x00000000
                                                   
#define API_RGB_MAIN_MODE_UPDATE                   0x80000000
#define API_RGB_MAIN_SYNC                          0x40000000
#define API_RGB_MAIN_DYNAMIC                       0x20000000
#define API_RGB_MAIN_COLOR_MASK                    0x000F0000
#define API_RGB_MAIN_MODE_MASK                     0x0000FF00
#define API_RGB_MAIN_SUMODE_MASK                   0x000000FF


#define API_RGB_MAIN_MODE_INC_MASK                 0x00000100
#define API_RGB_MAIN_COLOR_INC_MASK                0x00010000


#define API_RGB_MAIN_MODE_DISABLE                  0x00000000
#define API_RGB_MAIN_MODE_STATIC_USER              0x00000100
#define API_RGB_MAIN_MODE_STATIC                   0x00000200
#define API_RGB_MAIN_MODE_BREATH                   0x00000300
#define API_RGB_MAIN_MODE_RAINBOW                  0x00000400
#define API_RGB_MAIN_MODE_MORPHING                 0x00000500
#define API_RGB_MAIN_MODE_KBINTERLOCK              0x00000600

#define API_RGB_STATIC_COLORFUL                    0x00000000


#define API_RGB_SYNC_TIMEOUT                       20
#define API_RGB_REFRESH_TIME                       9

//=============================================================
//RGB Color Control Relationship 
#define API_RGB_Color_R                0
#define API_RGB_Color_G                1
#define API_RGB_Color_B                2

#define API_RGB_NA                     22



///@}
 
/**
 * @name	============== RGB Control Struct Relationship ==============
 *   		
 */ 
///@{  


typedef struct
{    
    //=========================================================
    //RGB status control parameter
    uint32_t   RGB_UpdateStatus;
    //==========================================================
    //Software Color Control Relationship Parameter
    uint8_t    Color0[3];
    uint8_t    Color1[3];
    //==========================================================
    //Software Drama Control Relationship Parameter
    uint8_t    RGB_TimeBaseCount;
    uint8_t    RGB_SYNC_TimeoutCount;
    uint32_t   RGB_MainStatus;
    uint8_t    RGB_RefreshData_TRG;
    uint8_t    RGB_RefreshData_TimeoutCount;
    
    uint8_t    RGB_RefreshColumn;
    uint8_t    RGB_RefreshRow;
    
    uint32_t   RGB_DramaMain;
    uint32_t   RGB_DramaMainCmp;
    uint32_t   RGB_DramaSub;
    uint32_t   RGB_DramaSubCmp;
    uint32_t   RGB_DramaTime;
    uint32_t   RGB_DramaTimeCmp;

    uint8_t    *RGB1_SceneryTmpBuf;
    uint8_t    *RGB2_SceneryTmpBuf;
    uint8_t    *RGB3_SceneryTmpBuf;
    uint32_t   *KB_Map_RGB_pBuf;
    //==========================================================
    //Hardware Control Relationship Parameter
    union 
    {
        __IO        uint32_t  W;
        __IO        uint16_t  H[2];
        __IO        uint8_t   B[4];

        struct 
        {
            __IO        uint8_t    BLANK    :  1;
            __IO        uint8_t    DSPRPS   :  1;
            __IO        uint8_t    TMGRST   :  1;
            __IO        uint8_t    ESPWM    :  1;
            __IO        uint8_t    LODVLT   :  2;
            __IO        uint8_t    LSDVLT   :  2;
            
            __IO        uint8_t    LATTMG   :  2;
            __IO        uint8_t    IDMENA   :  1;
            __IO        uint8_t    IDMRPT   :  1;
            __IO        uint8_t    IDMCUR   :  2;
            __I         uint8_t             :  2;

            __IO        uint8_t    OLDENA   :  1;
            __IO        uint8_t    PSMODE   :  3;
            __I         uint8_t             :  4;
            __I         uint8_t             :  8;
        }MBIT;
    }Function; 
    
    uint8_t     RGB_LINE_ON;                           
    uint8_t     RGB_DUMMY;
    
    uint8_t     Brightness;
    uint8_t     Dot[16];
    uint8_t     _PADDING;          // The parameter is for struct alignment boundary.
}API_RGB_TypeDef;


extern API_RGB_TypeDef API_RGB_CTR;


///@}
 
/**
 * @name	============== RGB Relationship Table ==============
 *   		
 */ 
///@{
extern uint8_t  const API_KB_ATable[KB_TOTAOL_KEY];   

extern uint16_t const API_RGB_PWMData_Table[ API_RGB_KBTotalLine][API_RGB_KBTotalColume ];


extern uint16_t const API_KBRGBDefault_RColorTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];
extern uint16_t const API_KBRGBDefault_GColorTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];
extern uint16_t const API_KBRGBDefault_BColorTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];

extern uint8_t const API_KBRGBDemo_RColorTable[6];
extern uint8_t const API_KBRGBDemo_GColorTable[6];
extern uint8_t const API_KBRGBDemo_BColorTable[6];

extern uint8_t API_KBRGB_RColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Red value in Keyboard map.   */
extern uint8_t API_KBRGB_GColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Green value in Keyboard map. */
extern uint8_t API_KBRGB_BColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Bule value in Keyboard map.  */

extern uint16_t  API_RGB_PWPIN_TABLE[11];
extern uint8_t   API_RGB_DOT_TABLE[45];

extern uint32_t  API_KB_ActDrama[API_RGB_KBTotalLine][API_RGB_KBTotalColume];

///@}

/**
 * @name	============== RGB Control Function ==============
 *   		
 */ 
///@{ 
  
void API_AllRGB_OFF(void);  

void API_RGB_Data_DeInit(void);
void API_RGB_ControlParameter_Init(void);
void API_RGB_Init(void);

void API_RGB_UpdateDataTrigger(void);  


void API_RGB_Mode_Config( uint32_t RGB_Mode);
void API_RGB_KBMain(void);
void API_RGB_Main(void);




///@}  
  
#endif  
  
#endif
 
