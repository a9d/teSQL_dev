#ifndef _SQL_H
#define _SQL_H

#include "portable.h"
#include "core.h"

//CREATE DATABASE [IF NOT EXISTS] db_name

//#define DB_NEW	0

extern void ApplicationSqlLockHook();
extern void ApplicationSqlUnlockHook();

//если бд уже существует то вернуть соответсвующуую ошибку
//#define CREATE		ApplicationSqlLockHook();
//#define DATABASE(__INDEX,__NAME)	db_create(__INDEX, __NAME);
//#define END			ApplicationSqlUnlockHook();

#define LOCK	ApplicationSqlLockHook()
#define UNLOCK	ApplicationSqlUnlockHook()

#define CREATE		LOCK;db_set_mode(1);
#define DROP		LOCK;db_set_mode(0);

#define DATABASE	db_create(
#define END			,NULL); UNLOCK;


#endif