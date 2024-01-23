


 /**
 ******************************************************************************
 *
 * @file        KEYBOARD.h
 * @brief       The KEYBOARD Code's h file.
 *
 * @par         Project
 *              MG32x02z
 * @version     V1.03
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
 * 1.History:
 *  #001_Lucas_20210427_V1.02
 *    >> Add RGB option in the project.
 *  #002_Lucas_20230426_1130_V1.03
 *    >> RGB funciotn add LED driver model option in Wizard.
 *******************************************************************************
 */
 
#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include "MG32x02z_GPIO_DRV.h"
#include "MG32x02z_EXIC_DRV.h"
#include "MG32x02z_USB_DRV.h"
//#include "MG32x02z_USBD_Descriptor_API.h"

// <<< Use Configuration Wizard in Context Menu >>>


//<o0> RGB Function <0=> Disable 
//                  <1=> Use TLC5948 
//                  <2=> Use MBIA045
#define MG32x02z_USBD_KEYBOARD_RGB_EN       2

//<o0> Ghost Key detect <0=> Disable <1=> Enable
#define MG32x02z_USBD_KEYBOARD_GHOSTKEY_EN  1

// <<< end of Configuration section >>> 


/**
 * @name	============== Data type ==============
 *   		
 */ 
///@{
#define    LED_OFF         1                     /*!< Define LED ON  : Control pin status.*/ 
#define    LED_ON          0                     /*!< Define LED OFF : Control pin status.*/ 

#define    KB_DISABLE      0
#define    KB_ENABLE       1


///@}

/**
 * @name	============== GPIO Relationship ==============
 *   		
 */ 
///@{
#define KB_LED_Caps                           PA6                                                                /*!< Define Caps LED control pin.*/
#define KB_LED_NumLock                        PA2                                                                /*!< Define NumLock LED control pin.*/
#define KB_LED_ScrollLock                     PA5                                                                /*!< Define ScallLock LED control pin.*/
                                                                                                                 
                                                                                                                 
#define KB_LED_Caps_Status(__HANDLE__)        KB_LED_Caps       = ~(__HANDLE__)                                  /*!< Control Caps      LED status according to __HANDLE__.*/
#define KB_LED_NumLock_Status(__HANDLE__)     KB_LED_NumLock    = ~(__HANDLE__)                                  /*!< Control NumLock   LED status according to __HANDLE__.*/
#define KB_LED_ScrollLock_Status(__HANDLE__)  KB_LED_ScrollLock = ~(__HANDLE__)                                  /*!< Control ScallLock LED status according to __HANDLE__.*/
                                                                                                                 
                                                                                                                 
#define KB_SCAN_ROW0                                GPIOC                                                              /*!< Define Key row0 port.*/
    #define KB_SCAN_ROW0_IRQ                      EXINT2_IRQn                                                    /*!< Define Key row0 interrupt vector.*/
    #define KB_SCAN_ROW0_MSK                      0x0F8F                                                         /*!< Defien pin mask of the row0 port .*/     
#define KB_SCAN_ROW1                          GPIOB                                                              /*!< Define Key row1 port.*/    
    #define KB_SCAN_ROW1_IRQ                      EXINT1_IRQn                                                    /*!< Define Key row1 interrupt vector.*/
    #define KB_SCAN_ROW1_MSK                      0xC000                                                         /*!< Define pin mask of the row1 port.*/
    #define KB_SCAN_ROW1_SHIFT                    10                                                              /*!< Define pin data shift of the row1 port.*/
#define KB_SCAN_ROW_MSK                       (KB_SCAN_ROW0_MSK | (KB_SCAN_ROW1_MSK >> KB_SCAN_ROW1_SHIFT))      /*!< Define Key row data mask*/                      
                                                                                               
                                                                                               
#define KB_SCAN_COLUMN0                       GPIOA                                                              /*!< Define key column0 port.*/
    #define KB_SCAN_COLUMN0_MSK                   0xFE80                                                         /*!< Define pin mask of the column0 port.*/    
#define KB_SCAN_COLUMN1                       GPIOD                                                              /*!< Define key column1 port.*/
    #define KB_SCAN_COLUMN1_MSK                   0x0001                                                         /*!< Define pin mask of the column1 port.*/
#define KB_SCAN_COLUMN2                       GPIOC                                                              /*!< Define key column2 port.*/           
    #define KB_SCAN_COLUMN2_MSK                   0xF000                                                         /*!< Define pin mask of the column2 port.*/


///@}


/**
 * @name	============== Time Relationship ==============
 *   		
 */ 
///@{
#define KB_DELAY_5US       1
#define KB_DELAY_1ms       48000

void KB_Delay(uint16_t KB_DELAY_TIME);

///@}



/**
 * @name	============== Keyboard Relationship ==============
 *   		
 */ 
///@{
                           
#define KB_SCAN_COLUMN             12                                  /*!< Total key colume.*/            
#define KB_SCAN_ROW                12                                  /*!< Total key row.*/
#define KB_TOTAOL_KEY              (KB_SCAN_COLUMN * KB_SCAN_ROW)      /*!< Total key that can define .*/


#define KB_SCAN_USB_PORT           3                                   /*!< Total Column use port count.*/

#define KB_MAKE_DELAY_TIME         0                                   /*!< Control buttion make debounce time.*/
#define KB_BREAK_DELAY_TIME        6                                   /*!< Control buttion break debounce time.*/


#define KB_GHOST_CNT_MASK          0x0F
#define KB_GHOST_NONE              0x00
#define KB_GHOST_CONFIRM           0x40
#define KB_GHOST_SEND              0x80

#define KB_SCAN_MAKE_STATUS_MASK   0x30
    #define KB_SCAN_MAKE_NOW           0x10
    #define KB_SCAN_MAKE_CONFIRM       0x20
#define KD_SCAN_Code_Update        0x40
#define KB_SCAN_BREAK_CONFIRM      0x80
#define KB_SCAN_MAKE_COUNT_MASK    0x07


extern uint16_t const KeyScan1_Table[(KB_SCAN_COLUMN + 1)][KB_SCAN_USB_PORT];    /*!< Table control scan pin status 1.*/
extern uint16_t const KeyScan0_Table[(KB_SCAN_COLUMN + 1)][KB_SCAN_USB_PORT];    /*!< Table control scan pin status 0.*/


extern const uint8_t Default_KeyCode_Table[KB_TOTAOL_KEY];                       /*!< Table of key code.*/


#define Key_Record_MAX          27


//====================================================================
//USB Relationship 
#define KB_STDKEY_EP                  USB_EP1                                    /*!< Use the usb endpoint to send standard key.*/
#define KB_MULTIMEDIA_KEY_EP          USB_EP2                                    /*!< Use the usb endpoint to send multimedia key.*/
                                      
#define KB_STDKEY_DATA_SIZE           8                                          /*!< Standard key total data size .*/
    #define KB_STD_MODIFY                 0                                      /*!< Modify key byte of the standard key data package.*/
        #define KB_STD_MODIFY_L_CTRL          0x01                               /*!< L_CTRL  bit of Modify byte.*/
        #define KB_STD_MODIFY_L_SHFIT         0x02                               /*!< L_SHFIT bit of Modify byte.*/
        #define KB_STD_MODIFY_L_ALT           0x04                               /*!< L_ALT   bit of Modify byte.*/
        #define KB_STD_MODIFY_L_GUI           0x08                               /*!< L_GUI   bit of Modify byte.*/
        #define KB_STD_MODIFY_R_CTRL          0x10                               /*!< R_CTRL  bit of Modify byte.*/
        #define KB_STD_MODIFY_R_SHFIT         0x20                               /*!< R_SHIFT bit of Modify byte.*/
        #define KB_STD_MODIFY_R_ALT           0x40                               /*!< R_ALT   bit of Modify byte.*/
        #define KB_STD_MODIFY_R_GUI           0x80                               /*!< R_GUI   bit of Modify byte.*/
    #define KB_STD_RESERVED               1                                      /*!< Reserved byte of the standard key data package.*/                                  
    #define KB_STD_NORAML                 2                                      /*!< MODIFY key byte of the standard key data package.*/

#define KB_MKEY_DATA_SIZE             4                                          /*!< Multimedia key total data size.*/

//====================================================================
//Keyboard / Keypad Page Table 

#define    KB_MULTI_MEDIA_START          0xA0
#define    KB_MULTI_MEDIA_END            0xB3
                                          
                                          
#define    KB_PREVIOUS_TRACK             160      //0xA0
#define    KB_NEXT_TRACK                 161      //0xA1
#define    KB_STOP                       162      //0xA2
#define    KB_PLAY                       163      //0xA3
#define    KB_VOL_UP                     164      //0xA4
#define    KB_VOL_DN                     165      //0xA5
#define    KB_FST_FW                     166      //0xA6
#define    KB_REWIND                     167      //0xA7
#define    KB_MUTE                       168      //0xA8
#define    KB_CALL_MYCOMPUTER            169      //0xA9
#define    KB_CALL_CACULATOR             170      //0xAA
#define    KB_CALL_MEDUA_PLAY            171      //0xAB
#define    KB_CALL_WWWW                  172      //0xAC
#define    KB_CALL_EMAIL                 173      //0xAD
#define    KB_CALL_MYFAVORITE            174      //0xAE
#define    KB_CALL_SEARCH                175      //0xAF
#define    KB_CALL_PREVIOUS_PAGE         176      //0xB0
#define    KB_CALL_NEXT_PAGE             177      //0xB1
#define    KB_CALL_WEBSTOP               178      //0xB2
#define    KB_CALL_WEBREFRESH            179      //0xB3


//====================================================================


typedef union
{
    __IO uint8_t B;
    struct
    {
        __IO uint8_t  NumLock     : 1;
        __IO uint8_t  Caps        : 1;
        __IO uint8_t  ScrollLock  : 1;
        __IO uint8_t              : 5;
    }MBIT;
}KB_LEDBit_TypeDef;

/** 
 * @struct	KEYBOARD
 * @brief	Control Keyboard.
 */
typedef struct
{
    //====================================
    //For Scan Key Relationship Control
    uint8_t              Scan_Column;
    uint8_t              Scan_Flag_Start;
    uint8_t              Scan_Flag_Matrix_CheckFull;
    uint8_t              Scan_Flag_Matrix_Checked;
    uint8_t              Scan_Count_CheckMatrix;
    uint8_t              Scan_Count_BuffOut;
    uint16_t             Scan_Buffer_Matrix[KB_SCAN_COLUMN];
    uint8_t              Scan_Buffer_Matrix_Flag[Key_Record_MAX];
    uint8_t              Scan_Buffer_Matrix_Address[Key_Record_MAX];
    //=====================================
    //For Standard Key Relationship Control
    uint8_t              STDKey_Busy;
    uint8_t              STDKey_IdleRate;
    uint8_t              STDKey_Protocol;
    uint8_t              STDKey_SendFlag;
    uint8_t              STDKey_ToHostBuffer[KB_STDKEY_DATA_SIZE];
    //=====================================
    //For MultiMedia Key Relationship Control
//    uint8_t              MKey_Busy;
//    uint8_t              MKey_SendFlag;
//    uint8_t              MKey_ToHostBuffer[(FKB_TOTALFUNCTION + 1)];
    //======================================
    //Ghost relationship
    uint8_t              GhostStatus;
    uint8_t              GhostDebounce[KB_SCAN_COLUMN];
    //======================================
    //handle Tmp;
    uint8_t              Tmp_Flag;
    uint8_t              Tmp_Addr;
    uint8_t              Tmp_Code;
    uint8_t              Tmp_Index;
    //======================================
    //LED
    KB_LEDBit_TypeDef    LED_Status;
    //=======================================
    //Reserved
    uint8_t              __Padding[3];
}KEYBOARD_TypeDef;



//====================================================================
extern KEYBOARD_TypeDef KB;


//====================================================================
void API_KB_Init(void);
void API_KB_Main(void);
void API_KB_Parameter_DeInit(void);
void API_KB_Update_LEDStatus(void);
void API_KB_ClearKeyRecord(void);
void API_KB_RecordKeySend(void);

void API_KB_ExternalWakeup_Cmd( FunctionalState EXTI_WAKEUP);
//====================================================================







#endif








