// MemoryAllocate.cpp: определяет точку входа для консольного приложения.
//
#include <stdio.h>
#include <tchar.h>

#include "sector.h"
#include "err_code.h"
#include "system_var.h"
#include <memory.h>
#include "crc.h"

#include "sql.h"


#include <stdio.h>
#include <stdarg.h>
#include <math.h>
#include <string.h>

extern UINT8_T ucHeap[2048];
extern UINT8_T ucHeap1[2048];

void ApplicationSectorPrepareHook(void)
{
	//подготовка памяти к размещению секторов
}

void ApplicationSectorOpenHook(UINT8_T index, UINT32_T start_addr,UINT32_T size)
{
	//подготовка сектора
}

void ApplicationSectorDeleteHook(UINT8_T index, UINT32_T start_addr, UINT32_T size)
{
	//удаление заданного сектора
}

void ApplicationSectorCloseHook(UINT8_T index, UINT32_T start_addr, UINT32_T size)
{
	//закрытие сектора
}

void ApplicationSectorСlosingHook( void )
{
}




//разработать функции конвертации чисел в массив и обратно
void ApplicationSqlLockHook()
{
}

void ApplicationSqlUnlockHook()
{
}


void ApplicationSqlErr(UINT8_T err)
{
}


//добавить функцию маллок с учетом выравнивания и функции read write с учетом выравнивания
//функцию корректироваки размера


//добавить функцию получения нулевого адреса
//добавить фунцию высокоуровнего чтения/записи

#define AVG(X) X,10

int _tmain(int argc, _TCHAR* argv[])
{
	int i;
	int size;
	SectorConfig config;
	UINT32_T test;
	UINT32_T addr1,addr2,addr3,addr4,addr5;
	UINT8_T buf[]={1,2,3,4,5,6};
	UINT32_T addr11;
	UINT8_T y;
	UINT8_T buf1[20];

	UINT16_T db_name=0;

	UINT8_T len=strlen("test");

	//попробовать реализовать перегрузку используя функцию с неизвестным колличеством параметров
	sector_Create(1,2);

    config.index=0;
	config.type=(SECTOR_START|SECTOR_CRC|SECTOR_FLASH);
	config.ByteAligment=2;
	config.StartAddr=0;
	config.StartAddrLen=BYTES_2;
	config.SectorSize=2000;
	config.SectorSizeLen=BYTES_2;
	sector_ConfigCheck(&config);
	sector_Insert(&config);


	CREATE DATABASE &db_name,(UINT8_T*)"test" END;
	CREATE DATABASE &db_name END;
	CREATE DATABASE &db_name,NULL END;
	CREATE DATABASE &db_name,"test" END;
	CREATE DATABASE &db_name,"test" END;
	CREATE DATABASE &db_name,"test1" END;
	//
	CREATE DATABASE &db_name,"test1" END;


	db_GetDB(&db_name,(UINT8_T*)"test");

	db_name=0;
	while(db_GetAllDB(&db_name, buf1,5)==ERR_OK){};



	//DROPE DATABASE AVG(&db_name) END;

	db_GetDB(&db_name,(UINT8_T*)"test");

	//CREATE DATABASE END;
	DROP DATABASE &db_name END;
	
	//проверить ситуацию когда удаляется только заголовок

	//DROP TABLE
	//ALTER TABLE
	//CREATE TABLE

	//UPDATE
	//DELETE
	//INSERT INTO 
	//SELECT FROM WHERE
	


	return 0;

	//sector_GetSectorConfig(0,&config);

	//sector_Malloc(0,&addr1,6);
	//sector_write(0,addr1,(void*)buf,6);

	//sector_Malloc(0,&addr2,6);
	//sector_write(0,addr2,(void*)buf,6);

	//sector_Malloc(0,&addr3,6);
	//sector_write(0,addr3,(void*)buf,6);

	//sector_Malloc(0,&addr4,6);
	//sector_write(0,addr4,(void*)buf,6);

	//sector_Malloc(0,&addr5,6);
	//sector_write(0,addr5,(void*)buf,6);

	//sector_Free(0,addr1);
	//sector_Free(0,addr3);
	//sector_Free(0,addr2);
	//sector_Free(0,addr4);
	//sector_Free(0,addr5);

	//sector_Close();

	//sector_Open(0,2);

	//sector_Malloc(0,&addr1,6);
	//sector_write(0,addr1,(void*)buf,6);

	//sector_Close();

	//return 0;

	//sector_Create(2,2);

	//config.index=0;
	//config.type=(SECTOR_MAIN|SECTOR_START|SECTOR_FLASH);
	//config.ByteAligment=2;
	//config.StartAddr=0;
	//config.StartAddrLen=BYTES_2;
	//config.SectorSize=2000;
	//config.SectorSizeLen=BYTES_2;

	//sector_ConfigCheck(&config);	
	//sector_Insert(&config);
	////sector_GetSectorConfig(0,&config);

	////
	//config.index=1;
	//config.type=(SECTOR_EEPROM);
	//config.ByteAligment=1;
	//config.StartAddr=0;
	//config.StartAddrLen=BYTES_4;
	//config.SectorSize=2000;
	//config.SectorSizeLen=BYTES_4;

	//sector_ConfigCheck(&config);
	//sector_Insert(&config);
	////sector_GetSectorConfig(1,&config);

	//sector_Malloc(0,&addr1,6);
	//sector_write(0,addr1,(void*)buf,6);

	//sector_Malloc(1,&addr11,6);
	//sector_write(1,addr11,(void*)buf,6);

	//sector_Malloc(0,&addr2,6);
	//sector_write(0,addr2,(void*)buf,6);

	//sector_Malloc(0,&addr3,6);
	//sector_write(0,addr3,(void*)buf,6);

	//sector_Malloc(0,&addr4,6);
	//sector_write(0,addr4,(void*)buf,6);

	//sector_Malloc(0,&addr5,6);
	//sector_write(0,addr5,(void*)buf,6);

	//sector_Free(0,addr2);
	//sector_Free(0,addr4);
	//sector_Free(0,addr5);
	//sector_Free(0,addr3); 

	//sector_Malloc(0,&addr2,14);

	//sector_GetFreeSize(0);
	////sector_GetSegmentCounter(0);

	//sector_GetFreeSize(1);

	//config.index=2;
	//config.type=(SECTOR_FLASH);
	//config.ByteAligment=2;
	//config.StartAddr=0;
	//config.StartAddrLen=BYTES_2;
	//config.SectorSize=2000;
	//config.SectorSizeLen=BYTES_2;
	//sector_ConfigCheck(&config);

	//sector_Delete(1);
	//sector_AddNewSector(&config);

	//sector_Close();
	//sector_Open(0, 2 ,0);
	//sector_GetSegmentCounter(1);

	//sector_Malloc(0,&addr2,6);
	//sector_write(0,addr2,(void*)buf,6);

	//sector_Free(0,addr1);


	//sector_Close();


	//если база данных закрыта, то как узнать адрес ссылки на список баз данных
	//в секторе START первый сегмент содержит указатель на список таблиц
	//этот сегмент создается при создании сектора START

	return 0;
}

