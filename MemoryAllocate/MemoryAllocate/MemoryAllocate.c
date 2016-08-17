// MemoryAllocate.cpp: ���������� ����� ����� ��� ����������� ����������.
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
	//���������� ������ � ���������� ��������
}

void ApplicationSectorOpenHook(UINT8_T index, UINT32_T start_addr,UINT32_T size)
{
	//���������� �������
}

void ApplicationSectorDeleteHook(UINT8_T index, UINT32_T start_addr, UINT32_T size)
{
	//�������� ��������� �������
}

void ApplicationSectorCloseHook(UINT8_T index, UINT32_T start_addr, UINT32_T size)
{
	//�������� �������
}

void ApplicationSector�losingHook( void )
{
}




//����������� ������� ����������� ����� � ������ � �������
void ApplicationSqlLockHook()
{
}

void ApplicationSqlUnlockHook()
{
}


void ApplicationSqlErr(UINT8_T err)
{
}




#define AVG(X) X,10



//������ ��
//next
//prev
//name link
//table link

//������ �������
//next
//prev
//name link
//row link
//data link
//flag
//saved sector

//������ row
//next
//prev
//name link
//tbl link
//row config
//data link offset

//������ data
//next
//prev
//size
//data


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
	UINT16_T tb_name=0;
	UINT16_T *tb_name1=0;
	UINT16_T tb_row1=0;

	//����������� ����������� ���������� ��������� ������� � ����������� ������������ ����������
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


	//CREATE DATABASE &db_name,(UINT8_T*)"test" END;

	//���������� ��� ������ ������������ ��������
	CREATE DATABASE &db_name END;

	SET DATABASE &db_name END;
	DROP DATABASE &db_name END;

	CREATE DATABASE &db_name,NULL END;
	CREATE DATABASE &db_name,"test" END;
	CREATE DATABASE &db_name,"test" END;
	CREATE DATABASE &db_name,"test1" END;

	//���
	//������ ����������� ����������� ����� ������
	SET DATABASE &db_name END;
	tb_name=0;

	CREATE TABLE 0,&tb_name ,"test" END;
	
	CREATE SAVEDIN(1) TABLE  0,&tb_name ,"test" ROW &tb_row1,"id", UNSIGNED INT8 PRIMARY_KEY
												ROW &tb_row1,"id", UNSIGNED INT8 PRIMARY_KEY END;
		//(&tb_row1,"id",UNSIGNED INT8 PRIMARY_KEY),
		//											 (&tb_row1,"id1", ARRAY(0,100) NOT_NULL) END;


	//db_GetDB(&db_name,(UINT8_T*)"test");

	//db_name=0;
	//while(db_GetAllDB(&db_name, buf1,5)==ERR_OK){};



	////DROPE DATABASE AVG(&db_name) END;

	//db_GetDB(&db_name,(UINT8_T*)"test");

	//CREATE DATABASE END;
	//DROP DATABASE &db_name END;

	//db_name=0;
	//db_GetDB(&db_name,(UINT8_T*)"test");
	
	//��������� �������� ����� ��������� ������ ���������

	//DROP TABLE
	//ALTER TABLE
	//CREATE TABLE

	//UPDATE
	//DELETE
	//INSERT INTO 
	//SELECT FROM WHERE
	








//	CREATE  TABLE  tbl_name [(create_definition,...)]
//[table_options] [select_statement]
//
//create_definition:
//  col_name type [NOT NULL | NULL] [DEFAULT default_value] [AUTO_INCREMENT]
//            [PRIMARY KEY] [reference_definition]
//  ���   PRIMARY KEY (index_col_name,...)
//  ���   UNIQUE  [index_name] (index_col_name,...)
//  ���   FULLTEXT  [index_name] (index_col_name,...)
//
//type:
//        TINYINT[(length)] [UNSIGNED] [ZEROFILL]
//  ���   SMALLINT[(length)] [UNSIGNED] [ZEROFILL]
//  ���   MEDIUMINT[(length)] [UNSIGNED] [ZEROFILL]
//  ���   INT[(length)] [UNSIGNED] [ZEROFILL]
//  ���   INTEGER[(length)] [UNSIGNED] [ZEROFILL]
//  ���   BIGINT[(length)] [UNSIGNED] [ZEROFILL]
//  ���   REAL[(length,decimals)] [UNSIGNED] [ZEROFILL]
//  ���   DOUBLE[(length,decimals)] [UNSIGNED] [ZEROFILL]
//  ���   FLOAT[(length,decimals)] [UNSIGNED] [ZEROFILL]
//  ���   DECIMAL(length,decimals) [UNSIGNED] [ZEROFILL]
//  ���   NUMERIC(length,decimals) [UNSIGNED] [ZEROFILL]
//  ���   CHAR(length) [BINARY]

	//PRIMARY KEY - ������� ��������
	//NULL �� ���������
	//CREATE TABLE name,"str name" ( row,"str row",type,NOT_NULL,DEFAULT, AUTO_INCREMENT,PRIMARY KEY UNIQUE)
 
	//NOT_NULL-������ ����������������
	//DEFAULT-�������� �� ���������
	//AUTO_INCREMENT-������ ��� �����, ��������
	//PRIMARY_KEY - ���������� ��������, ���� ��� �������, �� ���������� ������
	//UNIQUE	- ���������� �������
	
	//UNSIGNED

	//INT8 8
	//INT16 16
	//INT32	32
	//INT64	64
	//FLOAT  4 byte 
	//DOUBLE 8 byte
	//ARRAY(size)


	//SELECT FROM WHERE
	//LIMIT 

	//��� ������ �����??
	


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


	//���� ���� ������ �������, �� ��� ������ ����� ������ �� ������ ��� ������
	//� ������� START ������ ������� �������� ��������� �� ������ ������
	//���� ������� ��������� ��� �������� ������� START

	return 0;
}

