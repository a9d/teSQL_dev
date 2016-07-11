#ifndef SQL_DB_CONFIG
#define SQL_DB_CONFIG

#include <stdio.h>
#include "portable.h"

#ifdef  __cplusplus
extern "C" {
#endif


//���� ���������� 

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

typedef struct A_SECTOR_INFO
{
		UINT8_T  StartAddrLen;			//����� ���� ������
		UINT8_T	 SectorSizeLen;			//����� ���� ������
		UINT8_T  Type;					//��� �������
		UINT8_T  bl_size;				//����� ��������� ���� ���� � ������ ������������
		UINT8_T  ByteAligment;			//������������ ,������ ������ ����
		UINT32_T StartAddr;				//�������� �� ������
		UINT32_T FreeBytesRemaining;	//����������� ��������� ����

		#if (configUSE_SegmentCounter==TRUE)
		UINT32_T xSegmentCounter;		//����������� ���������
		#endif

		UINT32_T xStart_Addr;			//��������� �� ������
		UINT32_T pxEnd_Addr;			//��������� �� �����
}SectorInfo;

//������ ��������
typedef struct SECTOR_LIST
{
	UINT16_T	crc16;				//�������� ����� �����������
	UINT8_T		sector_counter;		//����������� ��������
	UINT8_T		crc;				//��������������� ���� sector_counter
	
	struct A_SECTOR_INFO *sector;	//������ ��������
}SectorList;

//������� ����
//������ ��
//�����������
//���������
//crc




//�������� �������
typedef struct SECTOR_CONFIG
{
	UINT8_T	index;				//����� �������
	UINT8_T type;				//��� �������
	UINT8_T StartAddrLen;		//�����, � ������, ���� �����
	UINT8_T SectorSizeLen;		//�����, � ������, ���� ������
	UINT32_T StartAddr;			//����� ������ ������� � ������ ������������
	UINT32_T SectorSize;		//������ ������� � ������ ������������
	UINT8_T ByteAligment;		//�������� � �������
}SectorConfig;

#ifdef  __cplusplus
}
#endif


#endif