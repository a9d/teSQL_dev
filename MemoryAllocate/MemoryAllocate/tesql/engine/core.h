#ifndef _CORE_H
#define _CORE_H

#include "portable.h"

//db_create		создание бд
//db_get		вернуть адрресс бд на входе номер или имя
//db_count		колличество бд
//db_delete		удалить бд

//ошибка возвращается через хук

void db_create(UINT8_T index, UINT8_T* name);

#endif