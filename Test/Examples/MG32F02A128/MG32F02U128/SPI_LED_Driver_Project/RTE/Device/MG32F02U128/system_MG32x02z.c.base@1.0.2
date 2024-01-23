/**
 ******************************************************************************
 * @file     system_MG32x02z.c
 * @brief    CMSIS Cortex-M# Device Peripheral Access Layer Source File for
 *           Device MG32x02z
 * @version  V3.30
 * @date     2023/06/25
 *
 * @note
 *
 ******************************************************************************
 * Copyright (c) 2012 ARM LIMITED

  All rights reserved.
  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:
  - Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  - Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  - Neither the name of ARM nor the names of its contributors may be used
    to endorse or promote products derived from this software without
    specific prior written permission.
  *
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
  -----------------------------------------------------------------------------
  */


#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "RTE_Components.h"
#include "MG32x02z.h"
#include "MG32x02z_CSC.h"
#include "MG32x02z_GPL.h"
#include "system_MG32x02z.h"

#if defined(MG32x02z_ConfigerWizard_CSC)
  #include "MG32x02z_CSC_Init.h"
#endif

/*-----------------------------------------------------------------------------
  DEFINES
 *---------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------
  Clock Variable definitions
 *---------------------------------------------------------------------------*/
/* ToDo: initialize SystemCoreClock with the system core clock frequency value
         achieved after system intitialization.
         This means system core clock frequency after call to SystemInit()   */
#if defined (__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050) /* ARM Compiler V6 */
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wmissing-variable-declarations"
        uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/
    #pragma clang diagnostic pop
#else
    uint32_t SystemCoreClock = __SYSTEM_CLOCK;  /*!< System Clock Frequency (Core Clock)*/
#endif

/*-----------------------------------------------------------------------------
  Clock functions
 *---------------------------------------------------------------------------*/
void SystemCoreClockUpdate(void)            /* Get Core Clock Frequency      */
{
/* ToDo: add code to calculate the system frequency based upon the current
         register settings.
         This function can be used to retrieve the system core clock frequeny
         after user changed register sittings.                               */

  #if defined(MG32x02z_ConfigerWizard_CSC)
    SystemCoreClock = CONF_CK_AHB_FREQ;
  #else
    // CK_MAIN
    switch(CSC->CR0.W & CSC_CR0_MAIN_SEL_mask_w){
        case CSC_CR0_MAIN_SEL_ck_hs_w :
            switch(CSC->CR0.W & CSC_CR0_HS_SEL_mask_w){
                case CSC_CR0_HS_SEL_ihrco_w:
                    if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                    {
                        if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                            SystemCoreClock = 12000000UL;
                        else
                            SystemCoreClock = 11059200UL;
                    }
                    else
                        SystemCoreClock = 0UL;
                    break;
                case CSC_CR0_HS_SEL_xosc_w:
                    SystemCoreClock = __XTAL_FREQ;
                    break;
                case CSC_CR0_HS_SEL_ilrco_w:
                    SystemCoreClock = 32000UL;
                    break;
                case CSC_CR0_HS_SEL_ck_ext_w:
                    SystemCoreClock = __EXTCK_FREQ;
                    break;
            }
            break;

        case CSC_CR0_MAIN_SEL_ck_plli_w :
          #if defined(MG32_1ST) || defined(MG32_2ND)
            switch(CSC->CR0.W & CSC_CR0_HS_SEL_mask_w){
                case CSC_CR0_HS_SEL_ihrco_w:
                    if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                    {
                        if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                            SystemCoreClock = 12000000UL;
                        else
                            SystemCoreClock = 11059200UL;
                    }
                    else
                        SystemCoreClock = 0UL;
                    break;
                case CSC_CR0_HS_SEL_xosc_w:
                    SystemCoreClock = __XTAL_FREQ;
                    break;
                case CSC_CR0_HS_SEL_ilrco_w:
                    SystemCoreClock = 32000UL;
                    break;
                case CSC_CR0_HS_SEL_ck_ext_w:
                    SystemCoreClock = __EXTCK_FREQ;
                    break;
            }
          #else
            if((CSC->PLL.W & CSC_PLL_PLLI_SEL_mask_w) == 0)
            {
                switch(CSC->CR0.W & CSC_CR0_HS_SEL_mask_w){
                    case CSC_CR0_HS_SEL_ihrco_w:
                        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                        {
                            if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                                SystemCoreClock = 12000000UL;
                            else
                                SystemCoreClock = 11059200UL;
                        }
                        else
                            SystemCoreClock = 0UL;
                        break;
                    case CSC_CR0_HS_SEL_xosc_w:
                        SystemCoreClock = __XTAL_FREQ;
                        break;
                    case CSC_CR0_HS_SEL_ilrco_w:
                        SystemCoreClock = 32000UL;
                        break;
                    case CSC_CR0_HS_SEL_ck_ext_w:
                        SystemCoreClock = __EXTCK_FREQ;
                        break;
                }
            }
            else
            {
                switch(CSC->CR0.W & CSC_CR0_HS2_SEL_mask_w){
                    case CSC_CR0_HS2_SEL_ihrco_w:
                        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                        {
                            if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                                SystemCoreClock = 12000000UL;
                            else
                                SystemCoreClock = 11059200UL;
                        }
                        else
                            SystemCoreClock = 0UL;
                        break;
                    case CSC_CR0_HS2_SEL_xosc_w:
                        SystemCoreClock = __XTAL_FREQ;
                        break;
                    case CSC_CR0_HS2_SEL_ck_ext_w:
                        SystemCoreClock = __EXTCK_FREQ;
                        break;
                }
            }
          #endif

            // PLLI Input
            switch(CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w){
                case CSC_DIV_PLLI_DIV_div2_w :
                    SystemCoreClock = SystemCoreClock / 2;
                    break;
                case CSC_DIV_PLLI_DIV_div4_w :
                    SystemCoreClock = SystemCoreClock / 4;
                    break;
                case CSC_DIV_PLLI_DIV_div6_w :
                    SystemCoreClock = SystemCoreClock / 6;
                    break;
                default :
                case CSC_DIV_PLLI_DIV_div1_w :
                    break;
            }
            break;

        case CSC_CR0_MAIN_SEL_ck_pllo_w :
          #if defined(MG32_1ST) || defined(MG32_2ND)
            switch(CSC->CR0.W & CSC_CR0_HS_SEL_mask_w){
                case CSC_CR0_HS_SEL_ihrco_w:
                    if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                    {
                        if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                            SystemCoreClock = 12000000UL;
                        else
                            SystemCoreClock = 11059200UL;
                    }
                    else
                        SystemCoreClock = 0UL;
                    break;
                case CSC_CR0_HS_SEL_xosc_w:
                    SystemCoreClock = __XTAL_FREQ;
                    break;
                case CSC_CR0_HS_SEL_ilrco_w:
                    SystemCoreClock = 32000UL;
                    break;
                case CSC_CR0_HS_SEL_ck_ext_w:
                    SystemCoreClock = __EXTCK_FREQ;
                    break;
            }
          #else
            if((CSC->PLL.W & CSC_PLL_PLLI_SEL_mask_w) == CSC_PLL_PLLI_SEL_ck_hs_w)
            {
                switch(CSC->CR0.W & CSC_CR0_HS_SEL_mask_w){
                    case CSC_CR0_HS_SEL_ihrco_w:
                        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                        {
                            if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                                SystemCoreClock = 12000000UL;
                            else
                                SystemCoreClock = 11059200UL;
                        }
                        else
                            SystemCoreClock = 0UL;
                        break;
                    case CSC_CR0_HS_SEL_xosc_w:
                        SystemCoreClock = __XTAL_FREQ;
                        break;
                    case CSC_CR0_HS_SEL_ilrco_w:
                        SystemCoreClock = 32000UL;
                        break;
                    case CSC_CR0_HS_SEL_ck_ext_w:
                        SystemCoreClock = __EXTCK_FREQ;
                        break;
                }
            }
            else
            {
                switch(CSC->CR0.W & CSC_CR0_HS2_SEL_mask_w){
                    case CSC_CR0_HS2_SEL_ihrco_w:
                        if((CSC->CR0.W & CSC_CR0_IHRCO_EN_mask_w) != 0)
                        {
                            if((CSC->CR0.W & CSC_CR0_IHRCO_SEL_mask_w) == CSC_CR0_IHRCO_SEL_12_w)
                                SystemCoreClock = 12000000UL;
                            else
                                SystemCoreClock = 11059200UL;
                        }
                        else
                            SystemCoreClock = 0UL;
                        break;
                    case CSC_CR0_HS2_SEL_xosc_w:
                        SystemCoreClock = __XTAL_FREQ;
                        break;
                    case CSC_CR0_HS2_SEL_ck_ext_w:
                        SystemCoreClock = __EXTCK_FREQ;
                        break;
                }
            }
          #endif

            // PLLI Input
            switch(CSC->DIV.W & CSC_DIV_PLLI_DIV_mask_w){
                case CSC_DIV_PLLI_DIV_div2_w :
                    SystemCoreClock = SystemCoreClock / 2;
                    break;
                case CSC_DIV_PLLI_DIV_div4_w :
                    SystemCoreClock = SystemCoreClock / 4;
                    break;
                case CSC_DIV_PLLI_DIV_div6_w :
                    SystemCoreClock = SystemCoreClock / 6;
                    break;
                default :
                case CSC_DIV_PLLI_DIV_div1_w :
                    break;
            }

            // PLL MUX
            if((CSC->CR0.W & CSC_CR0_PLL_EN_mask_w) == 0)
                SystemCoreClock = 0;
            else
            {
              #if defined(MG32_1ST) || defined(MG32_2ND)
                if((CSC->PLL.W & CSC_PLL_PLL_MUL_mask_w) ==  CSC_PLL_PLL_MUL_16_w)
                    SystemCoreClock = SystemCoreClock * 16;
                else
                    SystemCoreClock = SystemCoreClock * 24;
              #else 
                if((CSC->PLL.W & CSC_PLL_PLL_MDS_mask_w) != 0)
                    SystemCoreClock = SystemCoreClock * (((CSC->PLL.W & CSC_PLL_PLL_MULX_mask_w) >> 9) + 1);
                else
                {
                    if((CSC->PLL.W & CSC_PLL_PLL_MUL_mask_w) ==  CSC_PLL_PLL_MUL_16_w)
                        SystemCoreClock = SystemCoreClock * 16;
                    else
                        SystemCoreClock = SystemCoreClock * 24;
                }
              #endif
                SystemCoreClock = SystemCoreClock / (4 - ((CSC->DIV.W & CSC_DIV_PLLO_DIV_mask_w) >> 4));
            }
            SystemCoreClock = SystemCoreClock >> ((CSC->DIV.W & CSC_DIV_APB_DIV_mask_w) >> 16);
            SystemCoreClock = SystemCoreClock >> ((CSC->DIV.W & CSC_DIV_AHB_DIV_mask_w) >> 8);
            break;

        default:
            break;
    }
  #endif
}

/**
 * Initialize the system
 *
 * @param  none
 * @return none
 *
 * @brief  Setup the microcontroller system.
 *         Initialize the System.
 */
void SystemInit (void)
{
/* ToDo: add code to initialize the system
         do not use global variables because this function is called before
         reaching pre-main. RW section maybe overwritten afterwards.         */
  SystemCoreClock = __SYSTEM_CLOCK;
}

/**
 *******************************************************************************
 * @brief       
 * @details     
 * @return      
 * @exception   No
 * @note
 * @par         Example
 * @code
 * @endcode
 *******************************************************************************
 */
// Hard Fault handler in C, with stack frame location and LR value
// extracted from the assembly wrapper as input parameters
__weak void HardFault_Handler_C(unsigned int * hardfault_args, unsigned lr_value)
{
    static volatile unsigned int stacked_r0;
    static volatile unsigned int stacked_r1;
    static volatile unsigned int stacked_r2;
    static volatile unsigned int stacked_r3;
    static volatile unsigned int stacked_r12;
    static volatile unsigned int stacked_lr;
    static volatile unsigned int stacked_pc;
    static volatile unsigned int stacked_psr;
    stacked_r0 = ((unsigned long) hardfault_args[0]);
    stacked_r1 = ((unsigned long) hardfault_args[1]);
    stacked_r2 = ((unsigned long) hardfault_args[2]);
    stacked_r3 = ((unsigned long) hardfault_args[3]);
    stacked_r12 = ((unsigned long) hardfault_args[4]);
    stacked_lr = ((unsigned long) hardfault_args[5]);
    stacked_pc = ((unsigned long) hardfault_args[6]);
    stacked_psr = ((unsigned long) hardfault_args[7]);

    printf ("  Hard Fault Handler\n\r"); 
    printf ("  R0 = 0x%X\n\r", stacked_r0);
    printf ("  R1 = 0x%X\n\r", stacked_r1);
    printf ("  R2 = 0x%X\n\r", stacked_r2);
    printf ("  R3 = 0x%X\n\r", stacked_r3);
    printf ("  R12 = 0x%X\n\r", stacked_r12);
    printf ("  Stacked LR = 0x%X\n\r", stacked_lr);
    printf ("  Stacked PC = 0x%X\n\r", stacked_pc);
    printf ("  Stacked PSR = 0x%X\n\r", stacked_psr);
    printf ("  Current LR = 0x%X\n\r", lr_value);

    while(1); // endless loop
}

#if defined (__ARMCC_VERSION) || defined(__ARMCC_VERSION)
    #define GPL_DIVIDEND    *(int *)0x4B000030
    #define GPL_DIVISOR     *(int *)0x4B000034
    #define GPL_QUITUENT    *(int *)0x4B000038
    #define GPL_REMAINDER   *(int *)0x4B00003C

    #define lGPL_DIVIDEND   *(long int*)0x4B000030
    #define lGPL_DIVISOR    *(long int*)0x4B000034
    #define lGPL_QUITUENT   *(long int*)0x4B000038
    #define lGPL_REMAINDER  *(long int*)0x4B00003C
  #if defined(MG32_3RD)
    /**
    ******************************************************************************
    * @brief       computes the quotient and remainder of the division of the numerator
    *              numer by the denominator denom. If the division is inexact, the resulting
    *              quotient is the integer of lesser magnitude that is the nearest to the
    *              algebraic quotient. If the result cannot be represented, the behaviour is
    *              undefined; otherwise, quot * denom + rem shall equal numer.
    * @param[in]   Dividend
    * @param[in]   Divisor
    * @return      a structure of type div_t, comprising both the quotient and the
    *              remainder. the structure shall contain the following members,
    *              in either order.
    *              int quot; int rem;
    ******************************************************************************
    */
    _ARMABI_PURE div_t div(int Dividend, int Divisor)
    {
        div_t lDIV_T;
        GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
        // GPL->DIVD.W = (uint32_t)Dividend;
        // GPL->DIVS.W = (uint32_t)Divisor;
        GPL_DIVIDEND = Dividend;
        GPL_DIVISOR = Divisor;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        // lDIV_T.quot = (int32_t) GPL->QUT.W;
        // lDIV_T.rem = (int32_t) GPL->REM.W;
        lDIV_T.quot = GPL_QUITUENT;
        lDIV_T.rem = GPL_REMAINDER;
        return lDIV_T;
    }

    /*
    ******************************************************************************
    * computes the quotient and remainder of the division of the numerator
    * numer by the denominator denom. If the division is inexact, the sign of
    * the resulting quotient is that of the algebraic quotient, and the
    * magnitude of the resulting quotient is the largest integer less than the
    * magnitude of the algebraic quotient. If the result cannot be represented,
    * the behaviour is undefined; otherwise, quot * denom + rem shall equal
    * numer.
    * Returns: a structure of type ldiv_t, comprising both the quotient and the
    *          remainder. the structure shall contain the following members,
    *          in either order.
    *          long int quot; long int rem;
    ******************************************************************************
    */
    _ARMABI_PURE ldiv_t ldiv(long int Dividend, long int Divisor)
    {
        ldiv_t lDIV_T;
        GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
        // GPL->DIVD.W = (uint32_t)Dividend;
        // GPL->DIVS.W = (uint32_t)Divisor;
        lGPL_DIVIDEND = Dividend;
        lGPL_DIVISOR = Divisor;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        // lDIV_T.quot = (int32_t) GPL->QUT.W;
        // lDIV_T.rem = (int32_t) GPL->REM.W;
        lDIV_T.quot = lGPL_QUITUENT;
        lDIV_T.rem = lGPL_REMAINDER;
        return lDIV_T;
    }

    /**
     ******************************************************************************
     * Signed divide: (16-bit quot), (16-bit rem) = (32-bit) / (16-bit)
     ******************************************************************************
     */
    __value_in_regs _ARMABI_PURE __sdiv32by16 __rt_sdiv32by16(
         int Dividend,
         short int Divisor)
    {
        __sdiv32by16 lDIV_T;
        GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
        // GPL->DIVD.W = (uint32_t)Dividend;
        // GPL->DIVS.W = (uint32_t)Divisor;
        GPL_DIVIDEND = Dividend;
        GPL_DIVISOR = Divisor;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        // lDIV_T.quot = (long) GPL->QUT.W;
        // lDIV_T.rem = (long) GPL->REM.W;
        lDIV_T.quot = GPL_QUITUENT;
        lDIV_T.rem = GPL_REMAINDER;
        return lDIV_T;
    }

    /**
     ******************************************************************************
     * Unsigned divide: (16-bit quot), (16-bit rem) = (32-bit) / (16-bit)
     ******************************************************************************
     */
    __value_in_regs _ARMABI_PURE __udiv32by16 __rt_udiv32by16(
         unsigned int Dividend,
         unsigned short Divisor)
    {
        __udiv32by16 lDIV_T;
        GPL->CR1.B[2] &= ~GPL_CR1_DIV_TYPE_mask_b2;
        GPL->DIVD.W = (uint32_t)Dividend;
        GPL->DIVS.W = (uint32_t)Divisor;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        lDIV_T.quot = (unsigned long)GPL->QUT.W;
        lDIV_T.rem = (unsigned long)GPL->REM.W;
        return lDIV_T;
    }
  #endif

/*
 * GNU Compiler
 */
#elif defined ( __GNUC__ )
    #define GPL_DIVIDEND    *(int *)0x4B000030
    #define GPL_DIVISOR     *(int *)0x4B000034
    #define GPL_QUITUENT    *(int *)0x4B000038
    #define GPL_REMAINDER   *(int *)0x4B00003C

    #define lGPL_DIVIDEND   *(long *)0x4B000030
    #define lGPL_DIVISOR    *(long *)0x4B000034
    #define lGPL_QUITUENT   *(long *)0x4B000038
    #define lGPL_REMAINDER  *(long *)0x4B00003C

  #if defined(MG32_3RD)
    div_t div(int __numer, int __denom)
    {
        div_t lDIV_T;
        GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
        // GPL->DIVD.W = (uint32_t)Dividend;
        // GPL->DIVS.W = (uint32_t)Divisor;
        GPL_DIVIDEND = __numer;
        GPL_DIVISOR = __denom;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        // lDIV_T.quot = (int32_t) GPL->QUT.W;
        // lDIV_T.rem = (int32_t) GPL->REM.W;
        lDIV_T.quot = GPL_QUITUENT;
        lDIV_T.rem = GPL_REMAINDER;
        return lDIV_T;
    }

    ldiv_t ldiv(long __numer, long __denom)
    {
        ldiv_t lDIV_T;
        GPL->CR1.B[2] |= GPL_CR1_DIV_TYPE_mask_b2;
        // GPL->DIVD.W = (uint32_t)Dividend;
        // GPL->DIVS.W = (uint32_t)Divisor;
        lGPL_DIVIDEND = __numer;
        lGPL_DIVISOR = __denom;
        GPL->CR1.W |= GPL_CR1_DIV_START_mask_w;

        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();
        __NOP();

        // lDIV_T.quot = (long) GPL->QUT.W;
        // lDIV_T.rem = (long) GPL->REM.W;
        lDIV_T.quot = lGPL_QUITUENT;
        lDIV_T.rem = lGPL_REMAINDER;
        return lDIV_T;
    }
  #endif

/*
 * IAR Compiler
 */
#elif defined ( __ICCARM__ )

#else
  #error Unknown compiler.
#endif

