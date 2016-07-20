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

		//номер БД(это адрес БД)
		//-указатель на имя БД - допустимо NULL
		//-указатель на список таблиц - NULL если список еще не создан
		//-указатель на следующую БД
		//-CRC если требуется

//список секторов
typedef struct DB_HEADER
{
	UINT32_T	name;       //указатель на имя БД
	UINT32_T	tbl_list;	//указатель на список таблиц
	UINT32_T	next;		//указатель на следующую БД
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

	//первый параметр это индекс базы данных
	if(*p==NULL)
	{
		//ошибка
		ApplicationSqlErr(ERR_SQL_DB_ADDR);
		return;
	}
	else
	{
		db_addr=p;
	}

	//переход к следующему параметру
	p++;

	if(mode_create==MODE_CREATE)
	{
		//cnf=(SectorConfig*)local_malloc(sizeof(SectorConfig));

		//if(cnf!=NULL)
		//{
			//получить конфиг сектора старт
			//sector_GetSectorConfig(sector_GetStartIndex(),cnf);
			//memcpy((void*)&db_addr, *p, cnf->StartAddrLen);

		addr=sector_GetZeroSeg();
		err=sector_GetSegmentSize(sector_GetStartIndex(), addr, &size);

		//написаит функцию прохода по всем сегментам бд

		if(*p!=NULL)
		{
			//если есть имя то провести поиск БД с подобным именем
		}

		//	local_free(cnf);
		//}
		//else
		//{
		//	ApplicationSqlErr(ERR_LOCAL_MALLOC);
		//	return;
		//}

		//номер [имя]

		//проверить сущетвование БД с подобным номером или именем

		//создать если нет иначе вернуть ошибку

		//номер БД(это адрес БД)
		//-указатель на имя БД - допустимо NULL
		//-указатель на список таблиц - NULL если список еще не создан
		//-указатель на следующую БД
		//-CRC если требуется
	}
	else
	{
		//удаление только по номеру
	}



	//если есть второй, то это имя БД
	//if(*p!=NULL)
	//{
	//}

	//	const UINT8_T **p=&name;
	//UINT8_T len;
	//UINT8_T	index;

	////первый параметр UINT8
	////второй, если есть, это строка
	//if(*p!=NULL)
	//	index=**p;

	//p++;

	//if(*p!=NULL)
	//	len=strlen((char*)*p);

}