#include "core.h"
#include "err_code.h"
#include "sector.h"
#include "system_var.h"
#include "sector_hal.h"
#include "sql.h"
#include <memory.h>

#define MODE_DROPE  0
#define MODE_CREATE 1

UINT8_T mode_create;



extern void ApplicationSqlErr(UINT8_T err);

		//����� ��(��� ����� ��)
		//-��������� �� ��� �� - ��������� NULL
		//-��������� �� ������ ������ - NULL ���� ������ ��� �� ������
		//-��������� �� ��������� ��
		//-CRC ���� ���������

//������ ��������
typedef struct DB_HEADER
{
	UINT32_T	name;       //��������� �� ��� ��
	UINT32_T	tbl_list;	//��������� �� ������ ������
	UINT32_T	next;		//��������� �� ��������� ��
}DbHeader;


//0-drop
//1-create
void db_set_mode(UINT8_T mode)
{
	mode_create=mode;
}

void db_create(void *arg,...)
{
	void **p=&arg;

	SectorConfig *cnf;
	void *db_addr;
	UINT32_T size;
	UINT32_T addr;
	UINT8_T err;

	//������ �������� ��� ������ ���� ������
	if(*p==NULL)
	{
		//������
		ApplicationSqlErr(ERR_SQL_DB_ADDR);
		return;
	}
	else
	{
		db_addr=p;
	}

	//������� � ���������� ���������
	p++;

	if(mode_create==MODE_CREATE)
	{
		//cnf=(SectorConfig*)local_malloc(sizeof(SectorConfig));

		//if(cnf!=NULL)
		//{
			//�������� ������ ������� �����
			//sector_GetSectorConfig(sector_GetStartIndex(),cnf);
			//memcpy((void*)&db_addr, *p, cnf->StartAddrLen);

		addr=sector_GetZeroSeg();
		err=sector_GetSegmentSize(sector_GetStartIndex(), addr, &size);

		//�������� ������� ������� �� ���� ��������� ��

		if(*p!=NULL)
		{
			//���� ���� ��� �� �������� ����� �� � �������� ������
		}

		//	local_free(cnf);
		//}
		//else
		//{
		//	ApplicationSqlErr(ERR_LOCAL_MALLOC);
		//	return;
		//}

		//����� [���]

		//��������� ������������ �� � �������� ������� ��� ������

		//������� ���� ��� ����� ������� ������

		//����� ��(��� ����� ��)
		//-��������� �� ��� �� - ��������� NULL
		//-��������� �� ������ ������ - NULL ���� ������ ��� �� ������
		//-��������� �� ��������� ��
		//-CRC ���� ���������
	}
	else
	{
		//�������� ������ �� ������
	}



	//���� ���� ������, �� ��� ��� ��
	//if(*p!=NULL)
	//{
	//}

	//	const UINT8_T **p=&name;
	//UINT8_T len;
	//UINT8_T	index;

	////������ �������� UINT8
	////������, ���� ����, ��� ������
	//if(*p!=NULL)
	//	index=**p;

	//p++;

	//if(*p!=NULL)
	//	len=strlen((char*)*p);

}