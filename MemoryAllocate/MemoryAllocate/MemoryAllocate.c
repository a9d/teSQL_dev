#include <stdio.h>
#include <tchar.h>

#include "crc.h"
#include "portable.h"
#include "err_code.h"
#include "table.h"

#include "8to7.h"

#define MEM_SIZE 1000
UINT8_T ucHeap[MEM_SIZE];


/*-----------------------------------------------------------*/
void MySectorInit()
{
	memset(ucHeap, 0, sizeof(__int8) * MEM_SIZE);
}

UINT8_T local_write(UINT32_T addr, void *data, UINT32_T size)
{
	UINT32_T i;

	for(i=0;i<size;i++ )
		*(ucHeap+addr+i)=*((UINT8_T*)data+i);

	return ERR_OK;
}

UINT8_T local_read(UINT32_T addr, void *data, UINT32_T size)
{
	UINT32_T i;

	for(i=0;i<size;i++ )
		*((UINT8_T*)data+i)=*(ucHeap+addr+i);

	return ERR_OK;
}
/*-----------------------------------------------------------*/

int _tmain(int argc, _TCHAR* argv[])
{
	TableInfo myTable;
	UINT32_T addr, addr1, addr2, addr3, addr4, addr5, size;
	UINT8_T err = ERR_OK;

	////00010000 00000000 00000000 00000000 00000000 00000000 00000000 00000000 10001010 00001100 00000000 00000000
	////10001000 10000000 10000000 10000000 10000000 10000000 10000000 10000000 10000000 10100010 11000001 11000000 10000000 10000000
	////0x88 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0x80 0xA2 0xC1 0xC0   0x80 0x80
	//UINT8_T test[12] = { 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x8A, 0x0C ,0x00,0x00};
	//UINT8_T out[12] = { 0 };
	//UINT8_T out1[12] = { 0 };
	//
	//EightToSeven(test, out, 12);
	//SevenToEight(out, out1, 12);
	//
	//return 0;

	MySectorInit();	//инициализация сектора
	
	table_Init(&myTable, 4, 4, 4, 0, MEM_SIZE, local_read, local_write, Crc16);

	table_Malloc(&myTable, &addr, 10);
	table_Malloc(&myTable, &addr1, 20);
	table_Malloc(&myTable, &addr2, 30);
	table_Malloc(&myTable, &addr3, 40);
	table_Malloc(&myTable, &addr4, 50);

	table_Malloc(&myTable, &addr5, myTable.FreeBytesRemaining - myTable.bl_size);

	table_Free(&myTable, addr);
	table_Free(&myTable, addr2);
	table_Free(&myTable, addr3);

	table_Malloc(&myTable, &addr, 39);
	table_Malloc(&myTable, &addr3, 5);

	table_Free(&myTable, addr);
	table_Free(&myTable, addr1);
	table_Free(&myTable, addr3);
	table_Free(&myTable, addr4);
	table_Free(&myTable, addr5);

	return 0;
}




//#include <stdio.h>
//#include <tchar.h>
//
//#include "sector.h"
//#include "err_code.h"
//#include "system_var.h"
//#include <memory.h>
//#include "crc.h"
//
//#include "sql.h"
//
//#include <stdio.h>
//#include <stdarg.h>
//#include <math.h>
//#include <string.h>
//
//extern UINT8_T ucHeap[100];
////extern UINT8_T ucHeap1[2048];
//
//void ApplicationSectorPrepareHook(void)
//{
//	//подготовка памяти к размещению секторов
//}
//
//void ApplicationSectorOpenHook(UINT8_T index, UINT32_T start_addr,UINT32_T end_addr)
//{
//	//подготовка сектора
//}
//
//
//
//void ApplicationSectorDeleteHook(UINT8_T index, UINT32_T start_addr, UINT32_T end_addr)
//{
//	//удаление заданного сектора
//}
//
//void ApplicationSectorCloseHook(UINT8_T index, UINT32_T start_addr, UINT32_T end_addr)
//{
//	//закрытие сектора
//}
//
//void ApplicationSectorСlosingHook( void )
//{
//	//завершение работы
//}
//
//void ApplicationSqlLockHook()
//{
//}
//
//void ApplicationSqlUnlockHook()
//{
//}
//
//void ApplicationSqlErr(UINT8_T err)
//{
//}
//
////#define AVG(X) X,10
//
////запись бд
////next
////prev
////name link
////table link
//
////запись таблицы
////next
////prev
////name link
////row link
////data link
////flag
////saved sector
//
////запись row
////next
////prev
////name link
////tbl link
////row config
////data link offset
//
////запись data
////next
////prev
////size
////data
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	SectorConfig config;
//	//выделение памяти под структуры секторов
//	sector_ConfigInit(2,0,0);
//
//	//инициализация структур
//	config.index= SECTOR_RAM_0;
//	config.type = SECTOR_OPEN | SECTOR_CREATE | SECTOR_CRC | SECTOR_FLASH;
//	config.ByteAligment=4;
//	config.StartAddr=0;
//	config.StartAddrLen= BYTES_2;
//	config.EndAddr=100;
//	config.SectorSizeLen= BYTES_2;
//	sector_ConfigCheck(&config);
//	sector_ConfigSet(&config);
//
//	config.index = SECTOR_RAM_1;
//	config.type = SECTOR_OPEN | SECTOR_CRC | SECTOR_FLASH;
//	config.ByteAligment = 8;
//	config.StartAddr = 0;
//	config.StartAddrLen = BYTES_2;
//	config.EndAddr = 100;
//	config.SectorSizeLen = BYTES_2;
//	sector_ConfigCheck(&config);
//	sector_ConfigSet(&config);
//	
//	//открываем сектора
//	sector_Open();
//
//
//
//	//флаг с тем что делать, структура конфигов,
//	//sector_Open
//
//	//сделать более понятным. Слишком сложно
//
//	//проблема выравнивания!!!
//	//структуры с выравниванием 2 и 4 весят по разному и будет проблема если открыть в другом микроконтроллере
//	//sector_Open(0);
//
//	return 0;
//	//int i;
//	//int size;
//	//SectorConfig config;
//	//UINT32_T test;
//	//UINT32_T addr1,addr2,addr3,addr4,addr5;
//	//UINT8_T buf[]={1,2,3,4,5,6};
//	//UINT32_T addr11;
//	//UINT8_T y;
//	//UINT8_T buf1[20];
//
//	//UINT16_T db_name=0;
//	//UINT16_T tb_name=0;
//	//UINT16_T *tb_name1=0;
//	//UINT16_T tb_row1=0;
//
//	////попробовать реализовать перегрузку используя функцию с неизвестным колличеством параметров
//	//sector_Create(1,2);
//
// //   config.index=0;
//	//config.type=(SECTOR_START|SECTOR_CRC|SECTOR_FLASH);
//	//config.ByteAligment=2;
//	//config.StartAddr=0;
//	//config.StartAddrLen=BYTES_2;
//	//config.SectorSize=2000;
//	//config.SectorSizeLen=BYTES_2;
//	//sector_ConfigCheck(&config);
//	//sector_Insert(&config);
//
//
//	////CREATE DATABASE &db_name,(UINT8_T*)"test" END;
//
//	////переделать под первый обязательный параметр
//	//CREATE DATABASE &db_name END;
//
//	//SET DATABASE &db_name END;
//	//DROP DATABASE &db_name END;
//
//	//CREATE DATABASE &db_name,NULL END;
//	//CREATE DATABASE &db_name,"test" END;
//	//CREATE DATABASE &db_name,"test" END;
//	//CREATE DATABASE &db_name,"test1" END;
//
//	////тип
//	////ввести однозначное определение конца строки
//	//SET DATABASE &db_name END;
//	//tb_name=0;
//
//	//CREATE TABLE 0,&tb_name ,"test" END;
//	//
//	//CREATE SAVEDIN(1) TABLE  0,&tb_name ,"test" ROW &tb_row1,"id", UNSIGNED INT8 PRIMARY_KEY
//	//											ROW &tb_row1,"id", UNSIGNED INT8 PRIMARY_KEY END;
//		//(&tb_row1,"id",UNSIGNED INT8 PRIMARY_KEY),
//		//											 (&tb_row1,"id1", ARRAY(0,100) NOT_NULL) END;
//
//
//	//db_GetDB(&db_name,(UINT8_T*)"test");
//
//	//db_name=0;
//	//while(db_GetAllDB(&db_name, buf1,5)==ERR_OK){};
//
//
//
//	////DROPE DATABASE AVG(&db_name) END;
//
//	//db_GetDB(&db_name,(UINT8_T*)"test");
//
//	//CREATE DATABASE END;
//	//DROP DATABASE &db_name END;
//
//	//db_name=0;
//	//db_GetDB(&db_name,(UINT8_T*)"test");
//	
//	//проверить ситуацию когда удаляется только заголовок
//
//	//DROP TABLE
//	//ALTER TABLE
//	//CREATE TABLE
//
//	//UPDATE
//	//DELETE
//	//INSERT INTO 
//	//SELECT FROM WHERE
//	
//
//
//
//
//
//
//
//
////	CREATE  TABLE  tbl_name [(create_definition,...)]
////[table_options] [select_statement]
////
////create_definition:
////  col_name type [NOT NULL | NULL] [DEFAULT default_value] [AUTO_INCREMENT]
////            [PRIMARY KEY] [reference_definition]
////  или   PRIMARY KEY (index_col_name,...)
////  или   UNIQUE  [index_name] (index_col_name,...)
////  или   FULLTEXT  [index_name] (index_col_name,...)
////
////type:
////        TINYINT[(length)] [UNSIGNED] [ZEROFILL]
////  или   SMALLINT[(length)] [UNSIGNED] [ZEROFILL]
////  или   MEDIUMINT[(length)] [UNSIGNED] [ZEROFILL]
////  или   INT[(length)] [UNSIGNED] [ZEROFILL]
////  или   INTEGER[(length)] [UNSIGNED] [ZEROFILL]
////  или   BIGINT[(length)] [UNSIGNED] [ZEROFILL]
////  или   REAL[(length,decimals)] [UNSIGNED] [ZEROFILL]
////  или   DOUBLE[(length,decimals)] [UNSIGNED] [ZEROFILL]
////  или   FLOAT[(length,decimals)] [UNSIGNED] [ZEROFILL]
////  или   DECIMAL(length,decimals) [UNSIGNED] [ZEROFILL]
////  или   NUMERIC(length,decimals) [UNSIGNED] [ZEROFILL]
////  или   CHAR(length) [BINARY]
//
//	//PRIMARY KEY - столбец уникален
//	//NULL по умолчанию
//	//CREATE TABLE name,"str name" ( row,"str row",type,NOT_NULL,DEFAULT, AUTO_INCREMENT,PRIMARY KEY UNIQUE)
// 
//	//NOT_NULL-всегда инициализировать
//	//DEFAULT-значение по умолчанию
//	//AUTO_INCREMENT-только для целых, числовых
//	//PRIMARY_KEY - уникальное значение, если два столбца, то уникальная строка
//	//UNIQUE	- уникальное значние
//	
//	//UNSIGNED
//
//	//INT8 8
//	//INT16 16
//	//INT32	32
//	//INT64	64
//	//FLOAT  4 byte 
//	//DOUBLE 8 byte
//	//ARRAY(size)
//
//
//	//SELECT FROM WHERE
//	//LIMIT 
//
//	//как удаять дубли??
//	
//
//
//	return 0;
//
//	//sector_GetSectorConfig(0,&config);
//
//	//sector_Malloc(0,&addr1,6);
//	//sector_write(0,addr1,(void*)buf,6);
//
//	//sector_Malloc(0,&addr2,6);
//	//sector_write(0,addr2,(void*)buf,6);
//
//	//sector_Malloc(0,&addr3,6);
//	//sector_write(0,addr3,(void*)buf,6);
//
//	//sector_Malloc(0,&addr4,6);
//	//sector_write(0,addr4,(void*)buf,6);
//
//	//sector_Malloc(0,&addr5,6);
//	//sector_write(0,addr5,(void*)buf,6);
//
//	//sector_Free(0,addr1);
//	//sector_Free(0,addr3);
//	//sector_Free(0,addr2);
//	//sector_Free(0,addr4);
//	//sector_Free(0,addr5);
//
//	//sector_Close();
//
//	//sector_Open(0,2);
//
//	//sector_Malloc(0,&addr1,6);
//	//sector_write(0,addr1,(void*)buf,6);
//
//	//sector_Close();
//
//	//return 0;
//
//	//sector_Create(2,2);
//
//	//config.index=0;
//	//config.type=(SECTOR_MAIN|SECTOR_START|SECTOR_FLASH);
//	//config.ByteAligment=2;
//	//config.StartAddr=0;
//	//config.StartAddrLen=BYTES_2;
//	//config.SectorSize=2000;
//	//config.SectorSizeLen=BYTES_2;
//
//	//sector_ConfigCheck(&config);	
//	//sector_Insert(&config);
//	////sector_GetSectorConfig(0,&config);
//
//	////
//	//config.index=1;
//	//config.type=(SECTOR_EEPROM);
//	//config.ByteAligment=1;
//	//config.StartAddr=0;
//	//config.StartAddrLen=BYTES_4;
//	//config.SectorSize=2000;
//	//config.SectorSizeLen=BYTES_4;
//
//	//sector_ConfigCheck(&config);
//	//sector_Insert(&config);
//	////sector_GetSectorConfig(1,&config);
//
//	//sector_Malloc(0,&addr1,6);
//	//sector_write(0,addr1,(void*)buf,6);
//
//	//sector_Malloc(1,&addr11,6);
//	//sector_write(1,addr11,(void*)buf,6);
//
//	//sector_Malloc(0,&addr2,6);
//	//sector_write(0,addr2,(void*)buf,6);
//
//	//sector_Malloc(0,&addr3,6);
//	//sector_write(0,addr3,(void*)buf,6);
//
//	//sector_Malloc(0,&addr4,6);
//	//sector_write(0,addr4,(void*)buf,6);
//
//	//sector_Malloc(0,&addr5,6);
//	//sector_write(0,addr5,(void*)buf,6);
//
//	//sector_Free(0,addr2);
//	//sector_Free(0,addr4);
//	//sector_Free(0,addr5);
//	//sector_Free(0,addr3); 
//
//	//sector_Malloc(0,&addr2,14);
//
//	//sector_GetFreeSize(0);
//	////sector_GetSegmentCounter(0);
//
//	//sector_GetFreeSize(1);
//
//	//config.index=2;
//	//config.type=(SECTOR_FLASH);
//	//config.ByteAligment=2;
//	//config.StartAddr=0;
//	//config.StartAddrLen=BYTES_2;
//	//config.SectorSize=2000;
//	//config.SectorSizeLen=BYTES_2;
//	//sector_ConfigCheck(&config);
//
//	//sector_Delete(1);
//	//sector_AddNewSector(&config);
//
//	//sector_Close();
//	//sector_Open(0, 2 ,0);
//	//sector_GetSegmentCounter(1);
//
//	//sector_Malloc(0,&addr2,6);
//	//sector_write(0,addr2,(void*)buf,6);
//
//	//sector_Free(0,addr1);
//
//
//	//sector_Close();
//
//
//	//если база данных закрыта, то как узнать адрес ссылки на список баз данных
//	//в секторе START первый сегмент содержит указатель на список таблиц
//	//этот сегмент создается при создании сектора START
//
//	return 0;
//}
//
