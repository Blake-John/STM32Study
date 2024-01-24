#pragma once
#include "stm32f10x.h"
#include <math.h>
#include <stdio.h>
#include <stdarg.h>

extern uint8_t Tx_data[];
extern uint8_t Rx_data[];

void SerialInit (void);
void SerialSendByte (uint8_t byte);
void SerialSendArray (uint8_t* array, uint16_t length);
void SerialSendString (char* string);
void SerialSendNum (uint32_t num, uint8_t length);
void SerialPrintf (char* format, ...);
uint8_t GetFlag (void);
uint8_t* GetData (void);
void SerialSendPackage (uint8_t length);
