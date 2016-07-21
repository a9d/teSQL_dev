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

//������ ������
//


//������� ������ �� ������� ������ ���� ����� ��� ����!

//������ �������� � ��������
UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size);
//db_record_next
//db_record_prev
//db_record_add
//db_record_del

//�������� ������

#ifdef  __cplusplus
}
#endif

#endif