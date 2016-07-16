#ifndef _SQL_H
#define _SQL_H

#include "portable.h"
#include "core.h"

//CREATE DATABASE [IF NOT EXISTS] db_name

extern void ApplicationSqlLockHook();
extern void ApplicationSqlUnlockHook();

//если бд уже существует то вернуть соответсвующуую ошибку
//#define CREATE		ApplicationSqlLockHook();
//#define DATABASE(__INDEX,__NAME)	db_create(__INDEX, __NAME);
//#define END			ApplicationSqlUnlockHook();

#define ST (
#define DG )

#define CREATE		ApplicationSqlLockHook();
//void db_create(UINT8_T index, UINT8_T* name);
#define DATABASE	db_create(
#define END			); ApplicationSqlUnlockHook();


#endif