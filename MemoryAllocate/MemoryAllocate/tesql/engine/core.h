#ifndef _CORE_H
#define _CORE_H

#ifdef  __cplusplus
extern "C" {
#endif

#include "portable.h"

//db_create		�������� ��
//db_get		������� ������� �� �� ����� ����� ��� ���
//db_count		����������� ��
//db_delete		������� ��

//������ ������������ ����� ���

void db_set_mode(UINT8_T mode);

void db_create(void *arg,...);

#ifdef  __cplusplus
}
#endif

#endif