

 /**
 ******************************************************************************
 *
 * @file        MG32x02z_RGB_API.c
 * @brief       The RGB Code's c file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V2.00
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
#include "MG32x02z_TM_DRV.h"
#include "MG32x02z_GPL_DRV.h"
#include "MG32x02z_USBD_Keyboard_API.h"
#include "MG32x02z_RGB_API.h"

#if MG32x02z_USBD_KEYBOARD_RGB_EN == API_RGB_TLC5948
#include "MG32x02z_RGB_TLC5948_API.h"
#endif
#if MG32x02z_USBD_KEYBOARD_RGB_EN == API_RGB_MBIA045
#include "MG32x02z_RGB_MBIA045_API.h"
#endif


/* Wizard menu ---------------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
#if MG32x02z_USBD_KEYBOARD_RGB_EN != API_RGB_DISABLE 
 
API_RGB_TypeDef API_RGB_CTR;
 
static uint8_t   API_RGB_Numerator , API_RGB_Denominator; 
 

uint32_t  API_KB_ActDrama[API_RGB_KBTotalLine][API_RGB_KBTotalColume];

static uint8_t  API_KBRGB_RColorSceneryTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];
static uint8_t  API_KBRGB_GColorSceneryTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];
static uint8_t  API_KBRGB_BColorSceneryTable[API_RGB_KBTotalLine][API_RGB_KBTotalColume];

       uint8_t  API_KBRGB_RColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Red value in Keyboard map.   */
       uint8_t  API_KBRGB_GColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Green value in Keyboard map. */
       uint8_t  API_KBRGB_BColorScenery[API_RGB_KBTotalLine][API_RGB_KBTotalColume];               /*!< Bule value in Keyboard map.  */

/* Private function prototypes -----------------------------------------------*/
void TM10_IRQHandler(void);
void API_RGBData_IRQHandler(void);

static void API_RGB_KBIterlockDrama1(void);
static void API_RGB_KBIterlockDrama0(void);
static void API_RGB_MarphingDrama(void);
static void API_RGB_RainDrama2(void);
static void API_RGB_RainDrama1(void);
static void API_RGB_RainDrama0(void);
static void API_RGB_BreathDrama(void);
static void API_RGB_BreathDramaAct(void);
static void API_RGB_StaticDrama(void);
static void API_RGB_StaticUserDrama(void);
static void API_RGB_SetNextDrama(void);


/* Exported variables --------------------------------------------------------*/
/* External functions --------------------------------------------------------*/
/* External variables --------------------------------------------------------*/

/**
 * @name  
 *          
 */
///@{
/**
 *******************************************************************************
 * @brief	    All RGB LED power off.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_AllRGB_OFF()
{
    GPIO_SetPortBit(GPIOB,( API_RGB_Y0_PIN | API_RGB_Y1_PIN | API_RGB_Y10_PIN));
    GPIO_SetPortBit(GPIOD,( API_RGB_Y2_PIN | API_RGB_Y3_PIN | API_RGB_Y4_PIN | 
                            API_RGB_Y5_PIN | API_RGB_Y6_PIN | API_RGB_Y7_PIN |
                            API_RGB_Y8_PIN | API_RGB_Y9_PIN));
} 

/**
 *******************************************************************************
 * @brief	    RGB Data buffer to default.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGB_Data_DeInit(void)
{
    uint32_t LED_DataInit_Tmp;
    uint32_t LED_DataInit_Tmp2;
    
    //====================================================================================
    //RGB SPI data Initial
    API_RGBLedDriverData_DeInit();
    
    //====================================================================================
    //KB RGB Data Initial
    for( LED_DataInit_Tmp = 0; LED_DataInit_Tmp < API_RGB_KBTotalLine ; LED_DataInit_Tmp++)
    {
        for( LED_DataInit_Tmp2 = 0 ; LED_DataInit_Tmp2 < API_RGB_KBTotalColume; LED_DataInit_Tmp2++)
        {
            API_KB_ActDrama[LED_DataInit_Tmp][LED_DataInit_Tmp2]    = 0;
            
            API_KBRGB_RColorScenery[LED_DataInit_Tmp][LED_DataInit_Tmp2] = 0;
            API_KBRGB_GColorScenery[LED_DataInit_Tmp][LED_DataInit_Tmp2] = 0;
            API_KBRGB_BColorScenery[LED_DataInit_Tmp][LED_DataInit_Tmp2] = 0;
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
void API_RGB_ControlParameter_Init(void)
{
    uint8_t LED_CPInit_Tmp;
    
    
    //==============================================
    //Function Control Initial
    API_RGB_CTR.Function.MBIT.BLANK  = 1;     // 190    
    API_RGB_CTR.Function.MBIT.DSPRPS = 0;     // 120 
    API_RGB_CTR.Function.MBIT.TMGRST = 0;     // 121
    API_RGB_CTR.Function.MBIT.ESPWM  = 0;     // 122
    API_RGB_CTR.Function.MBIT.LODVLT = 0;     // 123 , 124
    API_RGB_CTR.Function.MBIT.LSDVLT = 0;     // 125 , 126
    API_RGB_CTR.Function.MBIT.LATTMG = 0;     // 127 , 128
    API_RGB_CTR.Function.MBIT.IDMENA = 0;     // 129
    API_RGB_CTR.Function.MBIT.IDMRPT = 0;     // 130
    API_RGB_CTR.Function.MBIT.IDMCUR = 0;     // 131 , 132
    API_RGB_CTR.Function.MBIT.OLDENA = 0;     // 133
    API_RGB_CTR.Function.MBIT.PSMODE = 0;     // 134 - 136
    

    //===============================================
    //Global Brightness Initial
    API_RGB_CTR.Brightness    = 127;           // 0 ~ 127 ( 25% ~ 100% )
    
    //==============================================
    //Dot Correction Data Initial
    for( LED_CPInit_Tmp = 0; LED_CPInit_Tmp < 16; LED_CPInit_Tmp ++)
    {
        API_RGB_CTR.Dot[ LED_CPInit_Tmp] = API_RGB_DOT_TABLE[LED_CPInit_Tmp];    
    }
    
    //===============================================
    //Control LED Driver parameter inital.
    API_RGBLedControlParameter_Init();
}

/**
 *******************************************************************************
 * @brief	    RGB LED function inital.
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void API_RGB_Init(void)
{
    PIN_InitTypeDef         LED_GPIOX;
    TM_TimeBaseInitTypeDef  LED_TimeBase;

    //===============================================
    //1. LED IC power : OFF
    //2. All LED power : OFF 
    API_AllRGB_OFF();
    API_RGB_ICPW_OFF;
    
    //===============================================
    //GPIO Mode Initial
    #if 1
        LED_GPIOX.PINX_Pin                = (PX_Pin_7 | PX_Pin_11 | PX_Pin_12 | PX_Pin_13);
        LED_GPIOX.PINX_Mode               = PINX_Mode_OpenDrain_O;
        LED_GPIOX.PINX_PUResistant        = PINX_PUResistant_Enable;
        LED_GPIOX.PINX_Speed              = PINX_Speed_Low;
        LED_GPIOX.PINX_Inverse            = PINX_Inverse_Disable;
        LED_GPIOX.PINX_OUTDrive           = PINX_OUTDrive_Level0;
        LED_GPIOX.PINX_FilterDivider      = PINX_FilterDivider_Bypass;
        LED_GPIOX.PINX_Alternate_Function = 0;                          
        GPIO_PortMode_Config(IOMB,&LED_GPIOX);
        
        LED_GPIOX.PINX_Pin                = (PX_Pin_1 | PX_Pin_2 | PX_Pin_3 | PX_Pin_7 | PX_Pin_8 | PX_Pin_9 | PX_Pin_10 | PX_Pin_11);
        GPIO_PortMode_Config(IOMD,&LED_GPIOX);
        
        LED_GPIOX.PINX_Pin                = PX_Pin_8;                              // LE ( SPI0_NSS)
        LED_GPIOX.PINX_Mode               = PINX_Mode_PushPull_O;
        LED_GPIOX.PINX_PUResistant        = PINX_PUResistant_Disable;
        LED_GPIOX.PINX_Speed              = PINX_Speed_High;
        LED_GPIOX.PINX_Alternate_Function = 7;                          
        GPIO_PortMode_Config(IOMA,&LED_GPIOX);
        
        
        LED_GPIOX.PINX_Pin                = PX_Pin_1 | PX_Pin_3;                   // GCLK_0 ( TM36_OC10) , GCLK_1 (TM36_OC2N)
        LED_GPIOX.PINX_Alternate_Function = 10;    
        GPIO_PortMode_Config(IOMA,&LED_GPIOX);
        
        
        LED_GPIOX.PINX_Pin                = PX_Pin_2 | PX_Pin_3;                   // SPI_SI (SPI0_MOSI) , SPI_CLK (SPI0_CLK)
        LED_GPIOX.PINX_Alternate_Function = 2;    
        GPIO_PortMode_Config(IOMB,&LED_GPIOX);
        
        LED_GPIOX.PINX_Pin                = PX_Pin_15;                             // GCLK_0 , GCLK_1 Control Pin
        LED_GPIOX.PINX_Alternate_Function = 5; 
        GPIO_PortMode_Config(IOME,&LED_GPIOX);
    #endif
    
    //==============================================
    //SPI Initial
    //    1. Baudrate = CK_APB / 2   
    #if 1
        SPI_DeInit( SPI0);
        
        SPI_ModeAndNss_Select(SPI0, SPI_MasterWithNss);
        SPI_NssInputOutputSoftwareControl_Cmd( SPI0, ENABLE);
        SPI_SlaveAsynchronous_Cmd(SPI0, DISABLE);
        
        SPI_ClockPhase_Select(SPI0, SPI_LeadingEdge); 
        
        SPI_ClockPolarity_Select(SPI0, SPI_Low); 
        SPI_FirstBit_Select(SPI0, SPI_MSB);
        SPI_DataSize_Select(SPI0, SPI_8bits); 
        SPI_DataLine_Select(SPI0, SPI_Standard);
        SPI_LoopBackMode_Cmd(SPI0, DISABLE); 
        SPI_DataLineOutput_Cmd(SPI0, ENABLE);
        SPI_SlaveModeReceivedThreshold_Select(SPI0, SPI_1Byte);
        
        SPI_IdleStateDataMode_Select( SPI0, SPI_OutputWithDriving);
        SPI_MasterDataOutIdleState_Select( SPI0 , REG_SPI_IDLSTATUS);
        
        SPI_PreDivider_Select( SPI0 , SPI_PDIV_1);
        SPI_Prescaler_Select( SPI0, SPI_PSC_1);
        SPI_Divider_Select( SPI0 , RGB_SPI_DIVIDER);
        
        
        SPI_ClearRxData( SPI0);
        SPI_ClearTxData( SPI0);
        
        
        SPI_ClearFlag(SPI0, SPI_TCF);
        
        SPI_Cmd(SPI0, ENABLE);
        
        SPI_IT_Config( SPI0 , RGB_SPI_INIT_INT , RGB_SPI_INIT_INT_STATUS);
        SPI_ITEA_Cmd( SPI0 , ENABLE);
        NVIC_EnableIRQ( SPI0_IRQn);
    #endif
    //=============================================
    //GCLK Initial (Use TM36)
    //    GCLK frequency = CK_APB / ( 2 * 100)
    #if 1
        TM_DeInit(TM36);
        TM_TimeBaseStruct_Init(&LED_TimeBase);
        LED_TimeBase.TM_MainClockSource    = TM_CK_INT;
        LED_TimeBase.TM_MainClockDirection = TM_UpCount;
//        LED_TimeBase.TM_Prescaler          = GCLK_TM_PRESCALER;
//        LED_TimeBase.TM_Period             = GCLK_TM_PERIOD;
        LED_TimeBase.TM_Prescaler          = 0;
        LED_TimeBase.TM_Period             = 180;
        
        LED_TimeBase.TM_CounterMode        = Separate;
        TM_TimeBase_Init(TM36, &LED_TimeBase);
        
        API_RGB_GCLK_TRG_PIN = 0;
        TM_TriggerSource_Select(TM36, TRGI_ETR);
        TM_TRGICounter_Select(TM36, TRGI_StartupFalling);
        TM_TRGIPrescaler_Select(TM36, TRGI_StartupFalling);

        TM_CH1Function_Config(TM36, TM_16bitPWM);
        TM_CH2Function_Config(TM36, TM_16bitPWM);
        
        TM_OC1zOutputState_Init(TM36, CLR);
        TM_OC2OutputState_Init(TM36, CLR);
        TM_InverseOC2N_Cmd( TM36 , ENABLE);
        
//        TM_SetCC1B( TM36, GCLK_TM_CCxB);
//        TM_SetCC2B( TM36, GCLK_TM_CCxB);
        TM_SetCC1B( TM36, 90);
        TM_SetCC2B( TM36, 90);
        
        TM_OC10Output_Cmd(TM36,ENABLE);  
        TM_OC2NOutput_Cmd(TM36,ENABLE);
        
        TM_RepetitionCounterClock_Select(TM36, TM_RCNT_CKMAIN);
        TM_RepetitionCounter_Config(TM36, GCLK_TM_REPCOUNTER, GCLK_TM_REPRELOAD);
        TM_RepetitionCounter_Cmd(TM36, ENABLE);
        TM_ControlPWM_Cmd(TM36, ENABLE);
        

        TM_Timer_Cmd(TM36,ENABLE);
        
        
    #endif
    //===============================================
    //1. LED parameter initial
    //2. LED Driver initial
    #if 1
        API_RGB_Data_DeInit();
        API_RGB_ControlParameter_Init();
        
        API_RGB_CTR.RGB_LINE_ON                  = 0;
        API_RGB_CTR.RGB_RefreshData_TRG          = 0;
        API_RGB_CTR.RGB_RefreshColumn            = 0;
        API_RGB_CTR.RGB_RefreshRow               = 0;
        API_RGB_CTR.RGB_TimeBaseCount            = 0;
        API_RGB_CTR.RGB_SYNC_TimeoutCount        = 0;
        API_RGB_CTR.RGB_RefreshData_TimeoutCount = 0;
        API_RGB_CTR.KB_Map_RGB_pBuf              = &API_KB_ActDrama[0][0];
        
        API_RGB_Mode_Config( API_RGB_MAIN_MODE_STATIC_USER);
        
        API_RGB_ICPW_ON;                        // Power on LED Driver power.
        
        /*=== Debug 2023_0523 ===*/
//        KB_Delay(KB_DELAY_1ms);
        
    #endif
    //===============================================
    //Inital the other module for LED driver
    API_RGBLed_Init();
    
    //===============================================
    //Update Time ( Use TM10)
    //    1. 1ms in 48MHz
    #if 1
        TM_TimeBaseStruct_Init(&LED_TimeBase);
        LED_TimeBase.TM_Period      = 119; 
        LED_TimeBase.TM_Prescaler   = 99;
        LED_TimeBase.TM_CounterMode = Cascade;

        

        TM_TimeBase_Init(TM10, &LED_TimeBase);
        TM_ClearFlag(TM10 , TMx_TOF);
        TM_IT_Config(TM10 , TMx_TIE_IE , ENABLE);
        TM_ITEA_Cmd( TM10 , ENABLE);
        NVIC_EnableIRQ( TM10_IRQn);
        
        
        TM_Timer_Cmd(TM10 , ENABLE);
    #endif    
}


///@}

/**
 *******************************************************************************
 * @brief	    
 * @details     
 * @return      
 * @exception   
 * @note        
 *******************************************************************************
 */
void TM10_IRQHandler(void)
{
    API_RGB_CLEAR_REFRESHFLAG();

    //========================================================================================
    if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_SYNC) == 0)
    {
        API_RGB_CTR.RGB_TimeBaseCount = API_RGB_CTR.RGB_TimeBaseCount + 1;
    }
    else
    {
        API_RGB_CTR.RGB_SYNC_TimeoutCount = API_RGB_CTR.RGB_SYNC_TimeoutCount + 1;
        
        if( API_RGB_CTR.RGB_SYNC_TimeoutCount == API_RGB_SYNC_TIMEOUT)
        {
            API_RGB_CTR.RGB_MainStatus = API_RGB_CTR.RGB_MainStatus & (uint32_t)(~API_RGB_MAIN_SYNC);
        }
    }
    //========================================================================================
    //Change ARGB display line.
    if( API_RGB_CTR.RGB_LINE_ON == ( API_RGB_TotalLine - 1))
    {
        API_RGB_CTR.RGB_LINE_ON  = 0;
    }
    else
    {
        API_RGB_CTR.RGB_LINE_ON  = API_RGB_CTR.RGB_LINE_ON  + 1;
    }
    
     //========================================================================================
    if( API_RGB_CTR.RGB_RefreshData_TRG !=0)
    {
#if MG32x02z_USBD_KEYBOARD_RGB_EN == 1
        API_RGB_UpdateNextLineData( ENABLE);
#endif 
        API_RGB_CTR.RGB_RefreshData_TRG  = API_RGB_CTR.RGB_RefreshData_TRG - 1;
    }
    else
    {
#if MG32x02z_USBD_KEYBOARD_RGB_EN == 1  
        API_RGB_UpdateNextLineData(DISABLE);  
#endif         
    }
    

    API_RGB_UpdateDataTrigger();
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
void API_RGB_Mode_Config( uint32_t RGB_Mode)
{
    uint8_t API_RGB_ModeConfigTmp1;
    uint8_t API_RGB_ModeConfigTmp2;
    
    
    
    //-----------------------------------------------------------
    //Set RGB Display Relationship Paramter. 
    switch(RGB_Mode)
    {
        case API_RGB_MAIN_MODE_STATIC_USER:
                                               for( API_RGB_ModeConfigTmp1 = 0; API_RGB_ModeConfigTmp1 < API_RGB_KBTotalLine ; API_RGB_ModeConfigTmp1++)
                                               {
                                                   for( API_RGB_ModeConfigTmp2 = 0; API_RGB_ModeConfigTmp2 < API_RGB_KBTotalColume ; API_RGB_ModeConfigTmp2++)
                                                   {
                                                       API_KBRGB_RColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_RColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                       API_KBRGB_GColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_GColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                       API_KBRGB_BColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_BColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                   }
                                               }   
                                               API_RGB_CTR.RGB_MainStatus =  ( API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_MODE_STATIC_USER );                                               
                                               break;
        case API_RGB_MAIN_MODE_STATIC:
                                               API_KBRGB_RColorSceneryTable[0][0] =  API_KBRGBDemo_RColorTable[0];
                                               API_KBRGB_GColorSceneryTable[0][0] =  API_KBRGBDemo_GColorTable[0];
                                               API_KBRGB_BColorSceneryTable[0][0] =  API_KBRGBDemo_BColorTable[0];
        
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_MODE_STATIC);  
                                               break;                                       
        case API_RGB_MAIN_MODE_BREATH:           
                                               API_RGB_CTR.RGB_DramaMainCmp = 2 - 1;
                                               API_RGB_CTR.RGB_DramaSubCmp  = 100;
                                               API_RGB_CTR.RGB_DramaTimeCmp = 0;
                                               
                                               API_KBRGB_RColorSceneryTable[0][0] =  API_KBRGBDemo_RColorTable[0];
                                               API_KBRGB_GColorSceneryTable[0][0] =  API_KBRGBDemo_GColorTable[0];
                                               API_KBRGB_BColorSceneryTable[0][0] =  API_KBRGBDemo_BColorTable[0];
        
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_DYNAMIC | API_RGB_MAIN_MODE_BREATH); 
                                               break;            
        case API_RGB_MAIN_MODE_RAINBOW:
                                               API_RGB_CTR.RGB_DramaMainCmp  = 6 - 1;
                                               API_RGB_CTR.RGB_DramaSubCmp   = 10;
                                               API_RGB_CTR.RGB_DramaTimeCmp  = 1;
        
                                               for( API_RGB_ModeConfigTmp1 = 0; API_RGB_ModeConfigTmp1 < 6 ; API_RGB_ModeConfigTmp1++)
                                               {
                                                   API_KBRGB_RColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_RColorTable[API_RGB_ModeConfigTmp1];
                                                   API_KBRGB_GColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_GColorTable[API_RGB_ModeConfigTmp1];
                                                   API_KBRGB_BColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_BColorTable[API_RGB_ModeConfigTmp1];
                                               }
                                               
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_DYNAMIC | API_RGB_MAIN_MODE_RAINBOW); 
                                               break;
        case API_RGB_MAIN_MODE_MORPHING:       
                                               API_RGB_CTR.RGB_DramaMainCmp   = 6 - 1;    
                                               API_RGB_CTR.RGB_DramaSubCmp    = 48;
                                               API_RGB_CTR.RGB_DramaTimeCmp   = 0;
        
        
                                               for( API_RGB_ModeConfigTmp1 = 0; API_RGB_ModeConfigTmp1 < 6 ; API_RGB_ModeConfigTmp1++)
                                               {
                                                   API_KBRGB_RColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_RColorTable[ API_RGB_ModeConfigTmp1 ];
                                                   API_KBRGB_GColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_GColorTable[ API_RGB_ModeConfigTmp1 ];
                                                   API_KBRGB_BColorSceneryTable[0][API_RGB_ModeConfigTmp1] =  API_KBRGBDemo_BColorTable[ API_RGB_ModeConfigTmp1 ];
                                               }
                                               
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_DYNAMIC | API_RGB_MAIN_MODE_MORPHING);
                                               break;
        case API_RGB_MAIN_MODE_KBINTERLOCK:
                                               API_RGB_CTR.RGB_DramaTimeCmp   = 0;    
        
        
                                               for( API_RGB_ModeConfigTmp1 = 0; API_RGB_ModeConfigTmp1 < API_RGB_KBTotalLine ; API_RGB_ModeConfigTmp1++)
                                               {
                                                   for( API_RGB_ModeConfigTmp2 = 0; API_RGB_ModeConfigTmp2 < API_RGB_KBTotalColume ; API_RGB_ModeConfigTmp2++)
                                                   {
                                                       API_KBRGB_RColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_RColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                       API_KBRGB_GColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_GColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                       API_KBRGB_BColorSceneryTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] = ( API_KBRGBDefault_BColorTable[ API_RGB_ModeConfigTmp1 ][API_RGB_ModeConfigTmp2] >> 8);
                                                   }
                                               }  
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_DYNAMIC | API_RGB_MAIN_MODE_KBINTERLOCK);  
                                               break;
        case API_RGB_MAIN_MODE_DISABLE:
        default:
                                               API_RGB_CTR.RGB_MainStatus =  (API_RGB_MAIN_MODE_UPDATE | API_RGB_MAIN_MODE_DISABLE);  
                                               break;
    }
    
    API_RGB_CTR.RGB_DramaTime = API_RGB_CTR.RGB_DramaTimeCmp;
    
    API_RGB_CTR.RGB_RefreshColumn = 0;
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
void API_RGB_KBMain()
{
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
void API_RGB_Main(void)
{

    if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_MODE_UPDATE) == 0)
    {
        return;
    }    
        
    if( API_RGB_CTR.RGB_TimeBaseCount == 0)
    {
        return;   
    }
    
           
     API_RGB_CTR.RGB_TimeBaseCount = API_RGB_CTR.RGB_TimeBaseCount - 1;
     

     if( API_RGB_CTR.RGB_RefreshData_TRG == 1)
     {
         if(API_RGB_CTR.RGB_RefreshData_TimeoutCount > API_RGB_REFRESH_TIME)
         {
             // To do......
         }
         else
         {
             API_RGB_CTR.RGB_RefreshData_TimeoutCount = API_RGB_CTR.RGB_RefreshData_TimeoutCount + 1;
         }
         
         return;
     }
     
     if( API_RGB_CTR.RGB_DramaTime != API_RGB_CTR.RGB_DramaTimeCmp)
     {
         API_RGB_CTR.RGB_DramaTime = API_RGB_CTR.RGB_DramaTime + 1;
         return;
     }
     API_RGB_CTR.RGB_DramaTime = 0;
     
     switch( API_RGB_CTR.RGB_RefreshColumn)
     {
         case 0:
         case 1:
         case 2:
         case 3:
         case 4:
         case 5:
                 switch( API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_MODE_MASK)
                 {
                     case API_RGB_MAIN_MODE_STATIC:
                                                        API_RGB_StaticDrama();
                                                        break;
                     case API_RGB_MAIN_MODE_BREATH:
                                                        API_RGB_BreathDrama();
                                                        break;
                     case API_RGB_MAIN_MODE_RAINBOW:
                                                        if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_SUMODE_MASK) == 0)
                                                        {
                                                            API_RGB_RainDrama0();
                                                        }
                                                        else if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_SUMODE_MASK) == 1 )
                                                        {
                                                            API_RGB_RainDrama1();
                                                        }
                                                        else
                                                        {
                                                            API_RGB_RainDrama2();
                                                        }
                                                        break;
                     case API_RGB_MAIN_MODE_MORPHING:
                                                        API_RGB_MarphingDrama();
                                                        break;
                     case API_RGB_MAIN_MODE_KBINTERLOCK:
                                                        if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_SUMODE_MASK) == 1)
                                                        {
                                                            API_RGB_KBIterlockDrama1();
                                                        }
                                                        else
                                                        {
                                                            API_RGB_KBIterlockDrama0();
                                                        }
                                                        break;
                     case API_RGB_MAIN_MODE_STATIC_USER:
                     case API_RGB_MAIN_MODE_DISABLE:
                     default:
                                                        API_RGB_StaticUserDrama();
                                                        break;
                 }
                 break;
         case 6:
         case 7:
         case 8:
         case 9:
         case 10:
         case 11:
                 API_RGB_UpdateDateDramaTmp();
                 break;
         
         case 12:
                 API_RGB_CTR.RGB_RefreshData_TRG = 11;
                 
                 API_RGB_CTR.RGB_RefreshColumn = 0;
                 API_RGB_CTR.RGB_RefreshData_TimeoutCount = 0;
                 if( (API_RGB_CTR.RGB_MainStatus & API_RGB_MAIN_DYNAMIC) == 0)
                 {
                     API_RGB_CTR.RGB_MainStatus = API_RGB_CTR.RGB_MainStatus & (~API_RGB_MAIN_MODE_UPDATE);
                 }

                 
                 return;
         default:
                 break;
     }
     API_RGB_CTR.RGB_RefreshColumn = API_RGB_CTR.RGB_RefreshColumn + 1;
     
 
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
#define API_RGB_DIFFUSION_MASK        0x0FFFFFFF
#define API_RGB_DIFFUSION_TRG         0x0F000000


#define API_RGB_DIFFUSION_UPTRG       0x08000000
#define API_RGB_DIFFUSION_DOWNTRG     0x04000000
#define API_RGB_DIFFUSION_RIGHTRG     0x02000000
#define API_RGB_DIFFUSION_LEFTRG      0x01000000

#define API_RGB_DIFFUSION_UCNTMASK    0x0000002F
#define API_RGB_DIFFUSION_DCNTMASK    0x00000FC0
#define API_RGB_DIFFUSION_RCNTMASK    0x0002F000
#define API_RGB_DIFFUSION_LCNTMASK    0x00FC0000

#define API_RGB_DIFFUSION_SUCNT       0x00000001
#define API_RGB_DIFFUSION_SDCNT       0x00000040
#define API_RGB_DIFFUSION_SRCNT       0x00001000
#define API_RGB_DIFFUSION_SLCNT       0x00040000

#define API_RGB_DIFFUSION_UCNT        0x00000008
#define API_RGB_DIFFUSION_DCNT        0x00000200
#define API_RGB_DIFFUSION_RCNT        0x00008000
#define API_RGB_DIFFUSION_LCNT        0x00200000
#define API_RGB_DIFFUSION_UDRFCNT     ( API_RGB_DIFFUSION_UCNT | API_RGB_DIFFUSION_DCNT | API_RGB_DIFFUSION_RCNT | API_RGB_DIFFUSION_LCNT)
#define API_RGB_DIFFUSION_DRFCNT      ( API_RGB_DIFFUSION_DCNT | API_RGB_DIFFUSION_RCNT | API_RGB_DIFFUSION_LCNT)
#define API_RGB_DIFFUSION_URFCNT      ( API_RGB_DIFFUSION_UCNT | API_RGB_DIFFUSION_RCNT | API_RGB_DIFFUSION_LCNT)


static void API_RGB_KBIterlockDrama1(void)
{
    uint32_t API_RGB_KBILCKStatusTmp;

    //======================================================================================================================
    for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume;  API_RGB_CTR.RGB_RefreshRow ++)
    {
        //--------------------------------------------------------------------------------------
        //Key trigger.
        if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & 0x80000000)
        {
            API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] &= (~0x80000000);
            
            if(API_RGB_CTR.RGB_RefreshColumn==0)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = ((API_RGB_DIFFUSION_DOWNTRG | API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_LEFTRG) + API_RGB_DIFFUSION_DRFCNT);   
            }
            else if(API_RGB_CTR.RGB_RefreshColumn==5)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = ((API_RGB_DIFFUSION_UPTRG | API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_LEFTRG) + API_RGB_DIFFUSION_URFCNT); 
            }
            else
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = ((API_RGB_DIFFUSION_UPTRG | API_RGB_DIFFUSION_DOWNTRG | API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_LEFTRG) + API_RGB_DIFFUSION_UDRFCNT);   
            }         
        }
        API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] &= (uint32_t)(~0x40000000);
        
        //-----------------------------------------------------------------------------------------
        //Diffusion next status.
        API_RGB_KBILCKStatusTmp = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_TRG;
        
        if( API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_UPTRG )
        {
            if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_UCNTMASK)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] - API_RGB_DIFFUSION_SUCNT;
            }
            else if( API_RGB_CTR.RGB_RefreshColumn !=0)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_UPTRG);
                
                API_KB_ActDrama[ (API_RGB_CTR.RGB_RefreshColumn - 1 ) ][API_RGB_CTR.RGB_RefreshRow] |=  (API_RGB_DIFFUSION_UPTRG | API_RGB_DIFFUSION_UCNT);
            }
            else
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_UPTRG);
            }
        }
        if( API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_DOWNTRG )
        {
            if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_DCNTMASK)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] - API_RGB_DIFFUSION_SDCNT;
            }
            else if( API_RGB_CTR.RGB_RefreshColumn != ( API_RGB_KBTotalLine - 1))
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_DOWNTRG);
                
                API_KB_ActDrama[ (API_RGB_CTR.RGB_RefreshColumn + 1 ) ][API_RGB_CTR.RGB_RefreshRow] |= (API_RGB_DIFFUSION_DOWNTRG | API_RGB_DIFFUSION_DCNT);
            }
            else
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_DOWNTRG);
            }
        }
        if( API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_RIGHTRG )
        {
            if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_RCNTMASK)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] - API_RGB_DIFFUSION_SRCNT;
            }
            else if( API_RGB_CTR.RGB_RefreshRow!=( API_RGB_KBTotalColume - 1))
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_RIGHTRG);
                
                API_KB_ActDrama[ (API_RGB_CTR.RGB_RefreshColumn  ) ][API_RGB_CTR.RGB_RefreshRow + 1] |= (API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_RCNT);
            
                if( (API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_UPTRG) && API_RGB_CTR.RGB_RefreshColumn!=0)
                {
                    API_KB_ActDrama[ API_RGB_CTR.RGB_RefreshColumn - 1 ][API_RGB_CTR.RGB_RefreshRow + 1] = ( API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_UPTRG | API_RGB_DIFFUSION_RCNT | API_RGB_DIFFUSION_UCNT);
                }
                if( (API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_DOWNTRG) && API_RGB_CTR.RGB_RefreshColumn!= (API_RGB_KBTotalLine-1))
                {
                    API_KB_ActDrama[ API_RGB_CTR.RGB_RefreshColumn + 1 ][API_RGB_CTR.RGB_RefreshRow + 1] = ( API_RGB_DIFFUSION_RIGHTRG | API_RGB_DIFFUSION_DOWNTRG | API_RGB_DIFFUSION_RCNT | API_RGB_DIFFUSION_DCNT);
                }
            }
            else
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_RIGHTRG);
            }
        }
        if( API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_LEFTRG )
        {
            if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_LCNTMASK)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] - API_RGB_DIFFUSION_SLCNT;
            }
            else if(API_RGB_CTR.RGB_RefreshRow!=0)
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_LEFTRG);
                
                API_KB_ActDrama[ (API_RGB_CTR.RGB_RefreshColumn  ) ][API_RGB_CTR.RGB_RefreshRow - 1] |= ( API_RGB_DIFFUSION_LEFTRG |  API_RGB_DIFFUSION_LCNT);
            
                if( (API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_UPTRG) && API_RGB_CTR.RGB_RefreshColumn!=0)
                {
                    API_KB_ActDrama[ API_RGB_CTR.RGB_RefreshColumn - 1 ][API_RGB_CTR.RGB_RefreshRow - 1] = ( API_RGB_DIFFUSION_LEFTRG | API_RGB_DIFFUSION_UPTRG | API_RGB_DIFFUSION_SLCNT | API_RGB_DIFFUSION_UCNT);
                }
                if( (API_RGB_KBILCKStatusTmp & API_RGB_DIFFUSION_DOWNTRG) && API_RGB_CTR.RGB_RefreshColumn!= (API_RGB_KBTotalLine-1))
                {
                    API_KB_ActDrama[ API_RGB_CTR.RGB_RefreshColumn + 1 ][API_RGB_CTR.RGB_RefreshRow - 1] = ( API_RGB_DIFFUSION_LEFTRG | API_RGB_DIFFUSION_DOWNTRG | API_RGB_DIFFUSION_SLCNT | API_RGB_DIFFUSION_DCNT);
                }
            }
            else
            {
                API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & (uint32_t)(~API_RGB_DIFFUSION_LEFTRG);
            }
        }
    }
    //======================================================================================================================
    API_RGB_KBILCKStatusTmp = API_RGB_CTR.RGB_RefreshColumn-1;
    
    if(API_RGB_CTR.RGB_RefreshColumn==( API_RGB_KBTotalLine - 1))
    {
        for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume;  API_RGB_CTR.RGB_RefreshRow ++)
        {
            
            if( API_KB_ActDrama[API_RGB_KBILCKStatusTmp][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_TRG)
            {

                API_KBRGB_RColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorSceneryTable[0][0];
                API_KBRGB_GColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorSceneryTable[0][0];
                API_KBRGB_BColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorSceneryTable[0][0];
            }
            else
            {
                API_KBRGB_RColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_GColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_BColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
            }
            
            if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_TRG)
            {
                API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorSceneryTable[0][0];
                API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorSceneryTable[0][0];
                API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorSceneryTable[0][0];
            }
            else
            {
                API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
            }
            
            
        }
    }
    else if( API_RGB_CTR.RGB_RefreshColumn !=0)
    {
        for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume;  API_RGB_CTR.RGB_RefreshRow ++)
        {
            if( API_KB_ActDrama[API_RGB_KBILCKStatusTmp][API_RGB_CTR.RGB_RefreshRow] & API_RGB_DIFFUSION_TRG)
            {
                API_KBRGB_RColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorSceneryTable[0][0];
                API_KBRGB_GColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorSceneryTable[0][0];
                API_KBRGB_BColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorSceneryTable[0][0];
            }
            else
            {
                API_KBRGB_RColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_GColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
                API_KBRGB_BColorScenery[ API_RGB_KBILCKStatusTmp ][ API_RGB_CTR.RGB_RefreshRow ] = 0;
            }
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
static void API_RGB_KBIterlockDrama0(void)
{    
    uint8_t API_RGB_KBIterLCKDramaTmp;
    
    for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume;  API_RGB_CTR.RGB_RefreshRow ++)
    {
        if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & 0x80000000)
        {
            API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow];
            API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow];
            API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow];
        }
        else if(API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & 0x40000000)
        {
            API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = 72;
        }
        else if( API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] != 0)
        {
            API_RGB_KBIterLCKDramaTmp = ((API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] & 0x000000FF) - 1);
            
            GPL->DIVD.W   = API_KBRGB_RColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow] * API_RGB_KBIterLCKDramaTmp;
            GPL->DIVS.W   = 72;
            GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;                    
            while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
        
            API_RGB_CTR.Color0[API_RGB_Color_R] = GPL->QUT.B[0];
            
            GPL->DIVD.W   = API_KBRGB_GColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow] * API_RGB_KBIterLCKDramaTmp;
            GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;                    
            while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
        
            API_RGB_CTR.Color0[API_RGB_Color_G] = GPL->QUT.B[0];
            
            GPL->DIVD.W   = API_KBRGB_BColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow] * API_RGB_KBIterLCKDramaTmp;
            GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;                    
            while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
        
            API_RGB_CTR.Color0[API_RGB_Color_B] = GPL->QUT.B[0];
            
            API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_RGB_CTR.Color0[API_RGB_Color_R];
            API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_RGB_CTR.Color0[API_RGB_Color_G];
            API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_RGB_CTR.Color0[API_RGB_Color_B];
            
            
            API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = API_KB_ActDrama[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] - 1;
            
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
static void API_RGB_MarphingDrama(void)
{
    uint32_t API_RGB_MarphingDramaTmp;
    
    
    if(API_RGB_CTR.RGB_RefreshColumn == 0)
    {
        if( (API_RGB_CTR.RGB_DramaMain & 0x01) == 0)
        {
            API_RGB_MarphingDramaTmp = 255 * API_RGB_CTR.RGB_DramaSub;
        }
        else
        {
            API_RGB_MarphingDramaTmp = 255 * (API_RGB_CTR.RGB_DramaSubCmp -  API_RGB_CTR.RGB_DramaSub);
        }
        
        GPL->DIVD.W   = API_RGB_MarphingDramaTmp;
        GPL->DIVS.W   = API_RGB_CTR.RGB_DramaSubCmp;
        GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
        
        while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
        
        API_RGB_CTR.Color0[0] = GPL->QUT.B[0];
        
        
        switch(API_RGB_CTR.RGB_DramaMain)
        {
            case 0:
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = 255;
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = 0;
                    break;
            case 1: 
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = 255;
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = 0;                      
                    break;
            case 2: 
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = 0;
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = 255;
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    break;
            case 3: 
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = 0;
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = 255;
                    break;
            case 4: 
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = 0;
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = 255;
                    break;
            case 5:
            default:
                    API_KBRGB_RColorScenery[ 0 ][ 0 ] = 255;
                    API_KBRGB_GColorScenery[ 0 ][ 0 ] = 0;
                    API_KBRGB_BColorScenery[ 0 ][ 0 ] = API_RGB_CTR.Color0[0];
                    break;
        }


        for( API_RGB_MarphingDramaTmp = 1; API_RGB_MarphingDramaTmp < API_RGB_KBTotalColume ; API_RGB_MarphingDramaTmp++) 
        {
            API_KBRGB_RColorScenery[ 0 ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_RColorScenery[ 0 ][ 0 ] ;
            API_KBRGB_GColorScenery[ 0 ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_GColorScenery[ 0 ][ 0 ] ;
            API_KBRGB_BColorScenery[ 0 ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_BColorScenery[ 0 ][ 0 ] ;
            
        }
    }
    else
    {
        for( API_RGB_MarphingDramaTmp = 0; API_RGB_MarphingDramaTmp < API_RGB_KBTotalColume ; API_RGB_MarphingDramaTmp++)
        {
            API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_RColorScenery[ 0 ][ 0 ];
            API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_GColorScenery[ 0 ][ 0 ];
            API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_MarphingDramaTmp ] = API_KBRGB_BColorScenery[ 0 ][ 0 ];
        }
    }

    if(API_RGB_CTR.RGB_RefreshColumn == ( API_RGB_KBTotalLine - 1))
    {
        API_RGB_SetNextDrama();
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
static void API_RGB_RainDrama2(void)
{
    uint8_t API_RGB_RainDrama1Tmp;
    uint8_t API_RGB_RainDrama1Column = API_RGB_CTR.RGB_RefreshColumn;
    
    
    
    if( API_RGB_RainDrama1Column == ( API_RGB_KBTotalLine - 1))
    {
        for( API_RGB_CTR.RGB_RefreshRow = 0 ; API_RGB_CTR.RGB_RefreshRow < (API_RGB_KBTotalColume-1); API_RGB_CTR.RGB_RefreshRow++)
        {
            API_KBRGB_RColorScenery[ API_RGB_RainDrama1Column ][ 22 - API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorScenery[ API_RGB_RainDrama1Column ][ ( 21 - API_RGB_CTR.RGB_RefreshRow ) ];
            API_KBRGB_GColorScenery[ API_RGB_RainDrama1Column ][ 22 - API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorScenery[ API_RGB_RainDrama1Column ][ ( 21 - API_RGB_CTR.RGB_RefreshRow ) ];
            API_KBRGB_BColorScenery[ API_RGB_RainDrama1Column ][ 22 - API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorScenery[ API_RGB_RainDrama1Column ][ ( 21 - API_RGB_CTR.RGB_RefreshRow ) ];
        }
        
        switch( API_RGB_CTR.RGB_DramaMain)
        {
            case 0:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
                    
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    break;
            case 1:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
            
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 2:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
                    
                    
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;    
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 3:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 4:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];                
        
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 5:
            default:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
        }
        
    }
    else
    {
        for( API_RGB_CTR.RGB_RefreshRow = 0 ; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow++)
        {
            API_KBRGB_RColorScenery[ API_RGB_RainDrama1Column ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorScenery[ ( API_RGB_RainDrama1Column + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
            API_KBRGB_GColorScenery[ API_RGB_RainDrama1Column ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorScenery[ ( API_RGB_RainDrama1Column + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
            API_KBRGB_BColorScenery[ API_RGB_RainDrama1Column ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorScenery[ ( API_RGB_RainDrama1Column + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
        }
        
    }
    
    if(API_RGB_CTR.RGB_RefreshColumn == ( API_RGB_KBTotalLine - 1))
    {
        API_RGB_SetNextDrama();
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
static void API_RGB_RainDrama1(void)
{
    
    uint8_t API_RGB_RainDrama1Tmp;

    if( API_RGB_CTR.RGB_RefreshColumn != ( API_RGB_KBTotalLine - 1))
    {
        for( API_RGB_CTR.RGB_RefreshRow = 0 ; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow++)
        {
            API_KBRGB_RColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorScenery[ ( API_RGB_CTR.RGB_RefreshColumn + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
            API_KBRGB_GColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorScenery[ ( API_RGB_CTR.RGB_RefreshColumn + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
            API_KBRGB_BColorScenery[ API_RGB_CTR.RGB_RefreshColumn ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorScenery[ ( API_RGB_CTR.RGB_RefreshColumn + 1 ) ][ API_RGB_CTR.RGB_RefreshRow ];
        }
    }
    else
    {
        switch( API_RGB_CTR.RGB_DramaMain)
        {
            case 0:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
                    
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    break;
            case 1:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
            
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 2:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
                    
                    
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;    
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 3:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
                    API_KBRGB_GColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 4:
                    GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];                
        
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
            case 5:
            default:
                    GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                    GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                    API_RGB_RainDrama1Tmp = GPL->QUT.B[0];
            
                    API_KBRGB_BColorScenery[( API_RGB_KBTotalLine - 1)][0] = API_RGB_RainDrama1Tmp;
                    API_KBRGB_RColorScenery[( API_RGB_KBTotalLine - 1)][0] = 255;
                    break;
        
        }
        
        for( API_RGB_CTR.RGB_RefreshRow = 1 ; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow++)
        {
            API_KBRGB_RColorScenery[ ( API_RGB_KBTotalLine - 1) ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_RColorScenery[ ( API_RGB_KBTotalLine - 1) ][ 0 ];
            API_KBRGB_GColorScenery[ ( API_RGB_KBTotalLine - 1) ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_GColorScenery[ ( API_RGB_KBTotalLine - 1) ][ 0 ];
            API_KBRGB_BColorScenery[ ( API_RGB_KBTotalLine - 1) ][ API_RGB_CTR.RGB_RefreshRow ] = API_KBRGB_BColorScenery[ ( API_RGB_KBTotalLine - 1) ][ 0 ];
        }
        
    }
    
    if(API_RGB_CTR.RGB_RefreshColumn == ( API_RGB_KBTotalLine - 1))
    {
        API_RGB_SetNextDrama();
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
static void API_RGB_RainDrama0(void)
{
    uint8_t API_RGB_RainDrama0Tmp;

    for( API_RGB_CTR.RGB_RefreshRow = 1 ; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow++)
    {
        API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][ (API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) ] = API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][ ((API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) - 1 ) ];
        API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][ (API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) ] = API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][ ((API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) - 1 ) ];
        API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][ (API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) ] = API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][ ((API_RGB_KBTotalColume - API_RGB_CTR.RGB_RefreshRow) - 1 ) ];
    }
    

    
    switch( API_RGB_CTR.RGB_DramaMain)
    {
        case 0:
                GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];
                
                API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;
                break;
        case 1:
                GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];
        
        
                API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;
                API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                break;
        case 2:
                GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];
                
                
                API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;    
                API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                break;
        case 3:
                GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];
        
                API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;
                API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                break;
        case 4:
                GPL->DIVD.W = 255 * API_RGB_CTR.RGB_DramaSub;
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];                

                API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;
                API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                break;
        case 5:
        default:
                GPL->DIVD.W = 255 * ( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub);
                GPL->DIVS.W = API_RGB_CTR.RGB_DramaSubCmp;
                GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
                while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
                API_RGB_RainDrama0Tmp = GPL->QUT.B[0];
        
                API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = API_RGB_RainDrama0Tmp;
                API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][0] = 255;
                break;
    
    }
    
    if(API_RGB_CTR.RGB_RefreshColumn == ( API_RGB_KBTotalLine - 1))
    {
        API_RGB_SetNextDrama();
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
static void API_RGB_BreathDramaAct(void)
{
    //==========================================================================================
    GPL->DIVD.W   =  (( API_KBRGB_RColorSceneryTable[0][0] * API_RGB_Numerator) * API_RGB_Numerator);
    GPL->DIVS.W   =  ( API_RGB_Denominator * API_RGB_Denominator);
    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
    
    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 

    
    API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = GPL->QUT.B[0];
    
    //===========================================================================================
    GPL->DIVD.W   =  (( API_KBRGB_GColorSceneryTable[0][0] * API_RGB_Numerator) * API_RGB_Numerator);
    GPL->DIVS.W   =  ( API_RGB_Denominator * API_RGB_Denominator);
    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
    
    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
    
    API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = GPL->QUT.B[0];
    
    //=============================================================================================
    GPL->DIVD.W   =  (( API_KBRGB_BColorSceneryTable[0][0] * API_RGB_Numerator) * API_RGB_Numerator);
    GPL->DIVS.W   =  ( API_RGB_Denominator * API_RGB_Denominator);
    GPL->CR1.B[3] =  GPL_CR1_DIV_START_mask_b3;
    
    while( ( GPL->STA.W & GPL_STA_DIVCF_mask_w) == 0); 
    
    API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][API_RGB_CTR.RGB_RefreshRow] = GPL->QUT.B[0];
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
static void API_RGB_BreathDrama(void)
{
    if( API_RGB_CTR.RGB_DramaMain == 0)
    {
        API_RGB_Numerator   = (uint8_t)API_RGB_CTR.RGB_DramaSub ;
        API_RGB_Denominator = (uint8_t)API_RGB_CTR.RGB_DramaSubCmp;
        
        for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow ++)
        {
            API_RGB_BreathDramaAct();
        }
    }
    else
    {
        API_RGB_Numerator   = (uint8_t)( API_RGB_CTR.RGB_DramaSubCmp - API_RGB_CTR.RGB_DramaSub) ;
        API_RGB_Denominator = (uint8_t)API_RGB_CTR.RGB_DramaSubCmp;
        
        for( API_RGB_CTR.RGB_RefreshRow = 0; API_RGB_CTR.RGB_RefreshRow < API_RGB_KBTotalColume; API_RGB_CTR.RGB_RefreshRow ++)
        {
            API_RGB_BreathDramaAct();
        }
    }
    
    if(API_RGB_CTR.RGB_RefreshColumn == ( API_RGB_KBTotalLine - 1))
    {
        API_RGB_SetNextDrama();
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
static void API_RGB_StaticDrama(void)
{
    uint8_t    APIRGB_StaticTmp;
    
    for( APIRGB_StaticTmp = 0; APIRGB_StaticTmp < API_RGB_KBTotalColume; APIRGB_StaticTmp ++)
    {
        API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticTmp] = API_KBRGB_RColorSceneryTable[ 0 ][ 0 ];
        API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticTmp] = API_KBRGB_GColorSceneryTable[ 0 ][ 0 ];
        API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticTmp] = API_KBRGB_BColorSceneryTable[ 0 ][ 0 ];
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
static void API_RGB_StaticUserDrama(void)
{
    uint8_t    APIRGB_StaticUserTmp;
    
    
    for( APIRGB_StaticUserTmp = 0; APIRGB_StaticUserTmp < API_RGB_KBTotalColume; APIRGB_StaticUserTmp ++)
    {
        API_KBRGB_RColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticUserTmp] = API_KBRGB_RColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ APIRGB_StaticUserTmp ];
        API_KBRGB_GColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticUserTmp] = API_KBRGB_GColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ APIRGB_StaticUserTmp ];
        API_KBRGB_BColorScenery[API_RGB_CTR.RGB_RefreshColumn][APIRGB_StaticUserTmp] = API_KBRGB_BColorSceneryTable[ API_RGB_CTR.RGB_RefreshColumn ][ APIRGB_StaticUserTmp ];
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
static void API_RGB_SetNextDrama(void)
{
    if( API_RGB_CTR.RGB_DramaSub == API_RGB_CTR.RGB_DramaSubCmp)
    {
        API_RGB_CTR.RGB_DramaSub = 0;
        
        if( API_RGB_CTR.RGB_DramaMain == API_RGB_CTR.RGB_DramaMainCmp)
        {
            API_RGB_CTR.RGB_DramaMain = 0;
        }
        else
        {
            API_RGB_CTR.RGB_DramaMain = API_RGB_CTR.RGB_DramaMain + 1;
        }
    }
    else
    {
        API_RGB_CTR.RGB_DramaSub = API_RGB_CTR.RGB_DramaSub + 1;
    }
}

#endif






