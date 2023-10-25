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

#define SECTOR_READONLY	0x10 //������ ����� ������ ������, �� �������� ���� ������ main
#define SECTOR_CRC		0x20 //������ ������ ����� CRC16
#define SECTOR_START	0x40 //���������� � ��
#define SECTOR_MAIN     0x80 //���������� � ��������, ���� ������ ��� � START �� �� ������������ � ������ � �� ����� ���� ��������

#define BYTES_1 0x01
#define BYTES_2 0x02
#define BYTES_3 0x03
#define BYTES_4 0x04

//1=		  127
//2=	   32 767
//3=	8�388�607
//4=2�147�483�647


//�������� �������
typedef struct SECTOR_CONFIG
{
	UINT8_T	index;				//����� �������
	UINT8_T type;				//��� �������
	UINT8_T StartAddrLen;		//�����, � ������, ���� �����
	UINT8_T SectorSizeLen;		//�����, � ������, ���� ������
	UINT16_T ByteAligment;		//������������ �������, � ������
	UINT32_T StartAddr;			//����� ������ ������� � ������ ������������
	UINT32_T SectorSize;		//������ ������� � ������ ������������
}SectorConfig;

#ifdef  __cplusplus
}
#endif

#endif