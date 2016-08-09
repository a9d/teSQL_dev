#ifndef _CRC_
#define _CRC_

#include "portable.h"

UINT16_T	Crc16(UINT8_T *pcBlock, UINT16_T len); //сгенерировать crc16
void		Crc16_Clear();	//сбросить скс16
UINT16_T	Crc16_Get();	//вернуть текущий crc16

#endif