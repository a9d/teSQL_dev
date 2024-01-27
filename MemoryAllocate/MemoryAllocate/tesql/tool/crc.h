#ifndef SQL_CRC16
#define SQL_CRC16

#include "portable.h"

#ifdef  __cplusplus
extern "C" {
#endif

UINT16_T Crc16(UINT16_T crc, UINT8_T* pcBlock, UINT16_T len); //сгенерировать crc16

#ifdef  __cplusplus
}
#endif

#endif