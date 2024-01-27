#ifndef SQL_ERR_CODE
#define SQL_ERR_CODE

#include "portable.h"

#ifdef  __cplusplus
extern "C" {
#endif

#define ERR_OK					((UINT8_T)0)
#define ERR_LOCAL_MALLOC		((UINT8_T)1)
#define ERR_WRONG_ALIGMENT		((UINT8_T)2)
#define ERR_WRONG_INDEX			((UINT8_T)3)
#define ERR_WRONG_SIZE			((UINT8_T)4)
//#define ERR_WRITE_FLASH			((UINT8_T)5)//1
//#define ERR_WRITE_EEPROM		((UINT8_T)6)//1
//#define ERR_WRITE_RAM			((UINT8_T)7)//1
//#define ERR_READ_FLASH			((UINT8_T)8)//1
//#define ERR_READ_EEPROM			((UINT8_T)9)//1
//#define ERR_READ_RAM			((UINT8_T)10)//1
#define ERR_NO_FREE_SPACE		((UINT8_T)11)
#define ERR_CRC					((UINT8_T)12)
//#define ERR_MAIN_READONLY		((UINT8_T)13)//1
//#define ERR_MAIN_SECTOR_FREE	((UINT8_T)14)//1
//#define ERR_START_SECTOR_FREE	((UINT8_T)15)//1
#define ERR_ADDR_LEN			((UINT8_T)16)
#define ERR_SIZE_LEN			((UINT8_T)17)
//#define ERR_SECTOR_FREE			((UINT8_T)18)//1
//#define ERR_SL_NULL				((UINT8_T)19)//1
//#define ERR_NO_MAIN				((UINT8_T)20)//1
//#define ERR_SQL_DB_ADDR			((UINT8_T)21)//1
//#define ERR_DB_ALREDY_EXISTS	((UINT8_T)22)//1
//#define ERR_DB_END				((UINT8_T)23)//1
//#define ERR_NAME_LEN			((UINT8_T)24)//1
//#define ERR_DB_ADDR				((UINT8_T)25)//1
//#define ERR_WRONG_MODE			((UINT8_T)26)//1
//#define ERR_MAIN_INDEX			((UINT8_T)27)//1
//#define ERR_START_INDEX			((UINT8_T)28)//1
#define ERR_TABLE_NULL			((UINT8_T)29)
#define ERR_NO_READ_FUNCTION	((UINT8_T)30)
#define ERR_NO_WRITE_FUNCTION	((UINT8_T)31)
#define ERR_READ				((UINT8_T)32)
#define ERR_WRITE				((UINT8_T)33)

#ifdef  __cplusplus
}
#endif

#endif