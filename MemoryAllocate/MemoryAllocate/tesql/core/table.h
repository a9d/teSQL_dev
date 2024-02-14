#ifndef SQL_TABLE
#define SQL_TABLE

#include <stdio.h>
#include "portable.h"
#include "config.h"

#ifdef  __cplusplus
extern "C" {
#endif

typedef UINT8_T(*read_t)(UINT32_T addr, void* data, UINT32_T size);
typedef UINT8_T(*write_t)(UINT32_T addr, void* data, UINT32_T size);
typedef UINT16_T(*crc_t)(UINT16_T crc, UINT8_T* pcBlock, UINT16_T len);

typedef struct TABLE_INFO
{
	UINT8_T  StartAddrLen;			//длина поля адреса
	UINT8_T	 TableSizeLen;			//длина поля размер

	UINT16_T bl_size;				//размер структуры блок линк с учетом выравнивания
	UINT16_T ByteAligment;			//выравнивание сектора

	UINT32_T StartAddr;				//стартовый адрес таблицы
	UINT32_T EndAddr;				//адрес конца таблицы
	UINT32_T FreeBytesRemaining;	//колличество свободных байт
#if (configUSE_SegmentCounter==TRUE)
	UINT32_T xSegmentCounter;		//колличество сегментов,используется для отладки
#endif
	//UINT32_T HeadAddr;

	read_t read;
	write_t write;
	crc_t crc;
}TableInfo;

UINT8_T table_Init(TableInfo *tab_ptr, UINT8_T addrLen, UINT8_T sizeLen, UINT16_T aligment, UINT32_T startAddr, UINT32_T endAddr, read_t Read, write_t Write, crc_t Crc);
UINT8_T	table_Malloc(TableInfo *tab_ptr, UINT32_T *addr, UINT32_T xWantedSize);
UINT8_T	table_Free(TableInfo *tab_ptr, UINT32_T pv);

#if (configUSE_SegmentCounter==TRUE)
UINT32_T table_GetSegmentCounter(TableInfo *tab_ptr);
#endif

UINT32_T table_GetFreeSize(TableInfo *tab_ptr);

UINT8_T table_GetAddrLen(TableInfo *tab_ptr);
UINT8_T	table_GetSizeLen(TableInfo *tab_ptr);

UINT8_T	table_GetSegmentSize(TableInfo *tab_ptr, UINT32_T addr, UINT32_T *size);

UINT32_T table_GetStartAdd(TableInfo* tab_ptr);
UINT32_T table_GetEndAdd(TableInfo* tab_ptr);

//UINT8_T table_GetAddr(TableInfo* tab_ptr, UINT32_T* addr);
//UINT8_T table_Flash(TableInfo* tab_ptr);

//UINT8_T	table_Write(TableInfo *tab_ptr, UINT32_T addr, void *data, UINT16_T size);
//UINT8_T	table_Read(TableInfo *tab_ptr, UINT32_T addr, void *data, UINT16_T size);

#ifdef  __cplusplus
}
#endif

#endif