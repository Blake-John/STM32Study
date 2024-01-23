#pragma once
#include "stm32f10x.h"


void SerialInit (void);
void SerialSendByte (uint8_t byte);
void SerialSendArray (uint8_t* array, uint16_t length);
void SerialSendString (char* string);