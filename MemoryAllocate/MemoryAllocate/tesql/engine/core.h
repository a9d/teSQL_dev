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

void db_create(void *arg,...);

//чтение записи
//


//функции работы со списком должны быть едины для всех!

//решить проблему с буффером
UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size);
//db_record_next
//db_record_prev
//db_record_add
//db_record_del

//добавить запись

#ifdef  __cplusplus
}
#endif

#endif