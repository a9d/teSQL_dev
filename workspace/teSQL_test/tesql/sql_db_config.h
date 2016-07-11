#ifndef SQL_DB_CONFIG
#define SQL_DB_CONFIG

#include <stdio.h>
#include "portable.h"

#ifdef  __cplusplus
extern "C" {
#endif


//файл переделать 

#define ERR_OK					0
#define ERR_LOCAL_MALLOC		1
#define ERR_WRONG_ALIGMENT		2
#define ERR_WRONG_INDEX			3
#define ERR_WRONG_SIZE			4
#define ERR_WRITE_FLASH			5
#define ERR_WRITE_EEPROM		6
#define ERR_WRITE_RAM			7
#define ERR_READ_FLASH			8
#define ERR_READ_EEPROM			9
#define ERR_READ_RAM			10
#define ERR_NO_FREE_SPACE		11
#define ERR_CRC					12
#define ERR_MAIN_READONLY		13
#define ERR_MAIN_SECTOR_FREE	14
#define ERR_START_SECTOR_FREE	15
#define ERR_ADDR_LEN			16
#define ERR_SIZE_LEN			17
#define ERR_SECTOR_FREE			18
#define ERR_SL_NULL				19
#define ERR_NO_MAIN				20


#define configUSE_SegmentCounter FALSE


#define SECTOR_FREE		0x00
#define SECTOR_FLASH	0x01
#define SECTOR_EEPROM	0x02
#define SECTOR_RAM		0x03

#define SECTOR_READONLY	0x10 //сектор можно только читать, не работает если сектор main
#define SECTOR_CRC		0x20 //кажда€ запись имеет CRC16
#define SECTOR_START	0x40 //информаци€ о Ѕƒ
#define SECTOR_MAIN     0x80 //информаци€ о секторах, если сектор еще и START то он используетс€ в работе и не может быть расширен
	

#define BYTES_1 0x01
#define BYTES_2 0x02
#define BYTES_3 0x03
#define BYTES_4 0x04

//1=		  127
//2=	   32 767
//3=	8†388†607
//4=2†147†483†647

typedef struct A_SECTOR_INFO
{
		UINT8_T  StartAddrLen;			//длина пол€ адреса
		UINT8_T	 SectorSizeLen;			//длина пол€ размер
		UINT8_T  Type;					//тип сектора
		UINT8_T  bl_size;				//длина структуры блок линк с учетом выравнивани€
		UINT8_T  ByteAligment;			//выравнивание ,всегда больше нул€
		UINT32_T StartAddr;				//смещение на сектор
		UINT32_T FreeBytesRemaining;	//колличество свободных байт

		#if (configUSE_SegmentCounter==TRUE)
		UINT32_T xSegmentCounter;		//колличество сегментов
		#endif

		UINT32_T xStart_Addr;			//указатель на голову
		UINT32_T pxEnd_Addr;			//указатель на хвост
}SectorInfo;

//список секторов
typedef struct SECTOR_LIST
{
	UINT16_T	crc16;				//генерить перед сохранением
	UINT8_T		sector_counter;		//колличество секторов
	UINT8_T		crc;				//инвертированное поле sector_counter
	
	struct A_SECTOR_INFO *sector;	//список секторов
}SectorList;

//текущий аддр
//список Ѕƒ
//колличество
//указатель
//crc




//описание сектора
typedef struct SECTOR_CONFIG
{
	UINT8_T	index;				//номер сектора
	UINT8_T type;				//тип сектора
	UINT8_T StartAddrLen;		//длина, в байтаз, пол€ адрес
	UINT8_T SectorSizeLen;		//длина, в байтах, пол€ размер
	UINT32_T StartAddr;			//адрес начала сектора с учетом выравнивани€
	UINT32_T SectorSize;		//размер сектора с учетом выравнивани€
	UINT8_T ByteAligment;		//смещение в секторе
}SectorConfig;

#ifdef  __cplusplus
}
#endif


#endif