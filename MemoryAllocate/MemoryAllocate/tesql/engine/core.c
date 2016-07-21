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
	UINT32_T	next;   //адрес следующей записи
	UINT32_T	prev;	//адрес предыдущей записи
}DB_Header;

//список базданных
typedef struct
{
	struct DB_HEADER header;
	UINT32_T	name;       //указатель на имя БД
	UINT32_T	tbl_list;	//указатель на список таблиц
}DB_List;


UINT8_T recor2db_header(UINT8_T index, DB_Header *header, UINT8_T *data);
void recor2db_header_list(UINT8_T index, DB_List *list, UINT8_T i, UINT8_T *data);

//0-drop
//1-create
void db_set_mode(UINT8_T mode)
{
	mode_create=mode;
}

//конвертировать массив в заголовок
UINT8_T recor2db_header(UINT8_T index, DB_Header *header, UINT8_T *data)
{
	UINT8_T i;	 //текущая позиция в массиве
	UINT8_T len; //длина поля

	len=sector_GetAddrLen(index);

	i=0;
	memcpy(&header->next,data,len);
	i+=len;
	memcpy(&header->prev,data+i,len);
	i+=len;

	return i;
}

//конвертировать массив в тело
void recor2db_header_list(UINT8_T index, DB_List *list, UINT8_T i, UINT8_T *data)
{
	UINT8_T len; //длина поля

	len=sector_GetAddrLen(index);

	memcpy(&list->name,data+i,len);
	i+=len;
	memcpy(&list->tbl_list,data+i,len);
	i+=len;
}



void db_create(void *arg,...)
{
	void **p=&arg;

	void *db_addr;

	UINT32_T	size;
	UINT32_T	addr;
	UINT8_T		err;
	UINT8_T		start_index;
	UINT8_T		*buf=NULL;
	DB_List		list;
	UINT8_T		len;
	UINT8_T		i;

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
		//получить данные по сектору старт
		start_index=sector_GetStartIndex();
		addr=sector_GetZeroSeg();
		
		err=db_record_load(start_index,addr,&buf, &size);

		

		local_free(buf);


		if(*p!=NULL)
		{
			//если есть имя то провести поиск БД с подобным именем
		}


	}
	else
	{
		//удаление только по номеру
	}


}


UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size)
{
	UINT8_T err;

	err=sector_GetSegmentSize(index, addr, size);

	if(err==ERR_OK)
	{
		*buf=(UINT8_T*)local_malloc(*size);
		if(buf!=NULL)
		{
			err=sector_read(index,addr,*buf,*size);
		}
		else
		{
			err=ERR_LOCAL_MALLOC;
		}
	}

	return err;
}