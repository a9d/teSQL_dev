#ifndef _HEAP
#define _HEAP

#include <stdio.h>
#include "portable.h"
#include "sector_hal.h"
#include "crc.h"
#include "err_code.h"
#include "system_var.h"

#ifdef  __cplusplus
extern "C" {
#endif

UINT8_T		sector_Init(UINT8_T index);												//инициализировать новый сектор
void		sector_ResourceFree();													//освободить занимаемую память в куче

UINT8_T		sector_Malloc(UINT8_T index, UINT32_T *addr, UINT32_T xWantedSize );	//выделить сегмент
UINT8_T		sector_Free(UINT8_T index, UINT32_T pv );								//освободить сегмент
UINT8_T		sector_ConfigCheck(SectorConfig* config);								//проверка настроек
UINT8_T		sector_Create(UINT8_T count);											//создание секторов
UINT8_T		sector_Insert(SectorConfig* config);									//вставить новый сектор в существующую аблицу
UINT32_T	sector_GetFreeSize(UINT8_T index);										//вернуть свободное место в секторе
UINT8_T		sector_GetSectorConfig(UINT8_T index, SectorConfig* config);			//вернуть конфигурацию сектора

#if (configUSE_SegmentCounter==TRUE)
UINT32_T	sector_GetSegmentCounter(UINT8_T index);								//вернуть колличество сегментов в секторе
#endif

UINT8_T		sector_Close();															//сохранить структуру секторов. Освободить ресурсы
UINT8_T		sector_MainSave();														//сохранить sl в секторе main
UINT8_T		sector_Delete(UINT8_T index);											//освободить заданный сектор

UINT8_T		sector_AddNewSector(SectorConfig* config);								//добавление нового сектора
UINT8_T		sector_Open(UINT32_T addr);												//открыть сектор main . Подготовить все сектора к работе

UINT32_T	sector_GetZeroSeg();													//вернуть адрес первого сегмента сектора 

UINT8_T		sector_GetStartIndex();													//вернуть индекс сектора Start


UINT32_T	sector_aligment(UINT32_T aligment,UINT32_T size);						//выровнять размер

UINT8_T		sector_GetSegmentSize(UINT8_T index, UINT32_T addr, UINT32_T *size);	//вернуть размер сегмента

void*		sector_RamMalloc(UINT8_T index,SIZE_T *size);							//выделить память с учетом выравнивания и CRC
void		sector_RamFree(void *block);											//освободить память
UINT8_T		sector_write(UINT8_T index, UINT32_T addr, void *data, UINT16_T size);	//запись с генерацией CRC
UINT8_T		sector_read(UINT8_T index, UINT32_T addr, void *data, UINT16_T size);	//чтение с проверкой CRC

UINT8_T		sector_GetAddrLen(UINT8_T index);
UINT8_T		sector_GetSizeLen(UINT8_T index);
UINT8_T		sector_GetCrcSize(UINT8_T index);

#ifdef  __cplusplus
}
#endif

#endif