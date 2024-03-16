#ifndef SQL_8TO7
#define SQL_8TO7

#include "portable.h"

#ifdef  __cplusplus
extern "C" {
#endif

UINT32_T SevenToEight(UINT8_T* in, UINT8_T* out, UINT32_T len);
UINT32_T EightToSeven(UINT8_T* in, UINT8_T* out, UINT32_T len, UINT8_T msb_bit);

#ifdef  __cplusplus
}
#endif

#endif