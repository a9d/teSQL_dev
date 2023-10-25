#ifndef SYSTEM_VAR_H
#define SYSTEM_VAR_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "portable.h"

#define SECTOR_FREE		0x00
#define SECTOR_FLASH	0x01
#define SECTOR_EEPROM	0x02
#define SECTOR_RAM		0x03

#define SECTOR_READONLY	0x10 //сектор можно только читать, не работает если сектор main
#define SECTOR_CRC		0x20 //каждая запись имеет CRC16
#define SECTOR_START	0x40 //информация о БД
#define SECTOR_MAIN     0x80 //информация о секторах, если сектор еще и START то он используется в работе и не может быть расширен

#define BYTES_1 0x01
#define BYTES_2 0x02
#define BYTES_3 0x03
#define BYTES_4 0x04

//1=		  127
//2=	   32 767
//3=	8 388 607
//4=2 147 483 647


//описание сектора
typedef struct SECTOR_CONFIG
{
	UINT8_T	index;				//номер сектора
	UINT8_T type;				//тип сектора
	UINT8_T StartAddrLen;		//длина, в байтах, поля адрес
	UINT8_T SectorSizeLen;		//длина, в байтах, поля размер
	UINT16_T ByteAligment;		//выравнивание сектора, в байтах
	UINT32_T StartAddr;			//адрес начала сектора с учетом выравнивания
	UINT32_T SectorSize;		//размер сектора с учетом выравнивания
}SectorConfig;

#ifdef  __cplusplus
}
#endif

#endif