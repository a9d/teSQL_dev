#ifndef _CRC_
#define _CRC_

#include "portable.h"

UINT16_T	Crc16(UINT8_T *pcBlock, UINT16_T len); //������������� crc16
void		Crc16_Clear();	//�������� ���16
UINT16_T	Crc16_Get();	//������� ������� crc16

#endif