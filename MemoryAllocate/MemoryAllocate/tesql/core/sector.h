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

UINT8_T		sector_Init(UINT8_T index);												//���������������� ����� ������
void		sector_ResourceFree();													//���������� ���������� ������ � ����

UINT8_T		sector_Malloc(UINT8_T index, UINT32_T *addr, UINT32_T xWantedSize );	//�������� �������
UINT8_T		sector_Free(UINT8_T index, UINT32_T pv );								//���������� �������
UINT8_T		sector_ConfigCheck(SectorConfig* config);								//�������� ��������
UINT8_T		sector_Create(UINT8_T count);											//�������� ��������
UINT8_T		sector_Insert(SectorConfig* config);									//�������� ����� ������ � ������������ ������
UINT32_T	sector_GetFreeSize(UINT8_T index);										//������� ��������� ����� � �������
UINT8_T		sector_GetSectorConfig(UINT8_T index, SectorConfig* config);			//������� ������������ �������

#if (configUSE_SegmentCounter==TRUE)
UINT32_T	sector_GetSegmentCounter(UINT8_T index);								//������� ����������� ��������� � �������
#endif

UINT8_T		sector_Close();															//��������� ��������� ��������. ���������� �������
UINT8_T		sector_MainSave();														//��������� sl � ������� main
UINT8_T		sector_Delete(UINT8_T index);											//���������� �������� ������

UINT8_T		sector_AddNewSector(SectorConfig* config);								//���������� ������ �������
UINT8_T		sector_Open(UINT32_T addr);												//������� ������ main . ����������� ��� ������� � ������

UINT32_T	sector_GetZeroSeg();													//������� ����� ������� �������� ������� 

UINT8_T		sector_GetStartIndex();													//������� ������ ������� Start


UINT32_T	sector_aligment(UINT32_T aligment,UINT32_T size);						//��������� ������

UINT8_T		sector_GetSegmentSize(UINT8_T index, UINT32_T addr, UINT32_T *size);	//������� ������ ��������

void*		sector_RamMalloc(UINT8_T index,SIZE_T *size);							//�������� ������ � ������ ������������ � CRC
void		sector_RamFree(void *block);											//���������� ������
UINT8_T		sector_write(UINT8_T index, UINT32_T addr, void *data, UINT16_T size);	//������ � ���������� CRC
UINT8_T		sector_read(UINT8_T index, UINT32_T addr, void *data, UINT16_T size);	//������ � ��������� CRC

UINT8_T		sector_GetAddrLen(UINT8_T index);
UINT8_T		sector_GetSizeLen(UINT8_T index);
UINT8_T		sector_GetCrcSize(UINT8_T index);

#ifdef  __cplusplus
}
#endif

#endif