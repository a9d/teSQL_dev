#ifndef _SQL_H
#define _SQL_H

#include "portable.h"
#include "core.h"

#define MAGIC_WORD 0x87654321

extern void ApplicationSqlLockHook();
extern void ApplicationSqlUnlockHook();

#define LOCK	ApplicationSqlLockHook()
#define UNLOCK	ApplicationSqlUnlockHook()

#define CREATE		LOCK;db_set_mode(1);
#define DROP		LOCK;db_set_mode(0);
#define SET

#define DATABASE	db_create(
#define END			,MAGIC_WORD); UNLOCK;

#define TABLE		db_create_tbl(
#define ROWS		);db_create_tbl_rows(

#define SAVEDIN(N)	db_save_sector(N);


#define UNSIGNED		0x0080 |
#define	INT8			0x0001
#define	INT16			0x0002
#define	INT32			0x0004
#define	INT64			0x0008
#define FLOAT			0x0010
#define DOUBLE			0x0020
#define ARRAY(N,SIZE)	0x0040,N,SIZE,0x0040

#define NOT_NULL		| 0x0100
#define AUTO_INCREMENT	| 0x0200
#define PRIMARY_KEY		| 0x0400
#define UNIQUE			| 0x0800


#endif