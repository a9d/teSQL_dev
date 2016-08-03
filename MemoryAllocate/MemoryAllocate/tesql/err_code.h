#ifndef ERR_CODE
#define ERR_CODE

#ifdef  __cplusplus
extern "C" {
#endif

#include "portable.h"

#define ERR_OK					((UINT8_T)0)
#define ERR_LOCAL_MALLOC		((UINT8_T)1)
#define ERR_WRONG_ALIGMENT		((UINT8_T)2)
#define ERR_WRONG_INDEX			((UINT8_T)3)
#define ERR_WRONG_SIZE			((UINT8_T)4)
#define ERR_WRITE_FLASH			((UINT8_T)5)
#define ERR_WRITE_EEPROM		((UINT8_T)6)
#define ERR_WRITE_RAM			((UINT8_T)7)
#define ERR_READ_FLASH			((UINT8_T)8)
#define ERR_READ_EEPROM			((UINT8_T)9)
#define ERR_READ_RAM			((UINT8_T)10)
#define ERR_NO_FREE_SPACE		((UINT8_T)11)
#define ERR_CRC					((UINT8_T)12)
#define ERR_MAIN_READONLY		((UINT8_T)13)
#define ERR_MAIN_SECTOR_FREE	((UINT8_T)14)
#define ERR_START_SECTOR_FREE	((UINT8_T)15)
#define ERR_ADDR_LEN			((UINT8_T)16)
#define ERR_SIZE_LEN			((UINT8_T)17)
#define ERR_SECTOR_FREE			((UINT8_T)18)
#define ERR_SL_NULL				((UINT8_T)19) //sector list is null
#define ERR_NO_MAIN				((UINT8_T)20)
#define ERR_SQL_DB_ADDR			((UINT8_T)21)
#define ERR_DB_ALREDY_EXISTS	((UINT8_T)22)
#define ERR_DB_END				((UINT8_T)23) //
#define ERR_NAME_LEN			((UINT8_T)24)
#define ERR_DB_ADDR				((UINT8_T)25)

#ifdef  __cplusplus
}
#endif

#endif