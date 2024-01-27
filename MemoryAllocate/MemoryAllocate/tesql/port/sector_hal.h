#ifndef SQL_HEAP_HAL
#define SQL_HEAP_HAL

#include <stdio.h>
#include "portable.h"
//#include "err_code.h"
//#include "system_var.h"

#ifdef  __cplusplus
extern "C" {
#endif

//UINT8_T local_write(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size);
//UINT8_T local_read(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size);

void *local_malloc(SIZE_T size);
void local_free(void *block);

#ifdef  __cplusplus
}
#endif

#endif