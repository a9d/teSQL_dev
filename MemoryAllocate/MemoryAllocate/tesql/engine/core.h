#ifndef _CORE_H
#define _CORE_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "portable.h"

//db_create		создание бд
//db_get		вернуть адрресс бд на входе номер или имя
//db_count		колличество бд
//db_delete		удалить бд

//ошибка возвращается через хук

void db_set_mode(UINT8_T mode);

void db_create(void *db_link, void *arg,...);

void db_create_tbl(UINT8_T index, void *addr ,void *arg,...);
//void db_create_tbl_rows(void *arg,...);
void db_create_tbl_row(void *addr,void *name, UINT16_T param,...);

//указать сектор для сохранения ТБ из РАМ
void db_save_sector(UINT8_T index);

//чтение записи
//

typedef struct
{
	UINT8_T		index;		//индекс сектора
	UINT8_T		addrlen;	//длина адреса
	UINT32_T	addr_cur;	//текущий аддрес
	UINT32_T	addr_next;	//адрес следующей записи
	UINT32_T	addr_prev;	//адрес предыдущей записи
	UINT32_T	size;		//размер сегмента
	UINT8_T		*data;		//указатель на массив с записью
}DB_Record;


//функции работы со списком должны быть едины для всех!

UINT8_T db_record_cur( DB_Record *rec );  //загрузить текущую
UINT8_T db_record_prev( DB_Record *rec ); //предыдущую
UINT8_T db_record_next( DB_Record *rec ); //следующую
UINT8_T db_record_add( DB_Record *rec );  //добавить новую запись, всегда передается адрес стартового сегмента который содержит указатель на хвост
UINT8_T db_record_del( DB_Record *rec );  //удалить указанную запись 


//вернуть список всех БД

//вернуть с указанным именем
UINT8_T db_FindByName(UINT32_T first_addr, void *db_link,UINT8_T *name);

//UINT8_T db_BaseByName(void *db_link,UINT8_T *name);
UINT8_T db_TableByName(void *db_link,UINT8_T *name);

UINT8_T db_AddNewDB(void *db_addr,UINT8_T *name);

UINT8_T db_GetDB(void *db_link,UINT8_T *name);

//если db_link = NULL то первый иначе это адрес текущей БД
//если следующая бд это перввая, то остановится
UINT8_T db_GetAllDB(void *db_link, UINT8_T *name,UINT8_T max_len);

UINT8_T db_LoadArray(UINT8_T index, UINT32_T addr, UINT8_T **arr);
//db_GetTBL
//db_GetAllTBL

//решить проблему с буффером
//UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size);
//db_record_next
//db_record_prev
//db_record_add
//db_record_del

//добавить запись

#ifdef  __cplusplus
}
#endif

#endif