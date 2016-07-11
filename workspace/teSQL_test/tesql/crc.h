#ifndef _CRC_
#define _CRC_

#include "portable.h"

UINT16_T	Crc16(UINT8_T *pcBlock, UINT16_T len);
void		Crc16_Clear();
UINT16_T	Crc16_Get();

#endif