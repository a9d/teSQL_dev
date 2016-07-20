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

#ifdef  __cplusplus
}
#endif

#endif