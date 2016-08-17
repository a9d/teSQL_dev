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

void db_create(void *db_link, void *arg,...);

void db_create_tbl(UINT8_T index, void *addr ,void *arg,...);
//void db_create_tbl_rows(void *arg,...);
void db_create_tbl_row(void *addr,void *name, UINT16_T param,...);

//������� ������ ��� ���������� �� �� ���
void db_save_sector(UINT8_T index);

//������ ������
//

typedef struct
{
	UINT8_T		index;		//������ �������
	UINT8_T		addrlen;	//����� ������
	UINT32_T	addr_cur;	//������� ������
	UINT32_T	addr_next;	//����� ��������� ������
	UINT32_T	addr_prev;	//����� ���������� ������
	UINT32_T	size;		//������ ��������
	UINT8_T		*data;		//��������� �� ������ � �������
}DB_Record;


//������� ������ �� ������� ������ ���� ����� ��� ����!

UINT8_T db_record_cur( DB_Record *rec );  //��������� �������
UINT8_T db_record_prev( DB_Record *rec ); //����������
UINT8_T db_record_next( DB_Record *rec ); //���������
UINT8_T db_record_add( DB_Record *rec );  //�������� ����� ������, ������ ���������� ����� ���������� �������� ������� �������� ��������� �� �����
UINT8_T db_record_del( DB_Record *rec );  //������� ��������� ������ 


//������� ������ ���� ��

//������� � ��������� ������
UINT8_T db_FindByName(UINT32_T first_addr, void *db_link,UINT8_T *name);

//UINT8_T db_BaseByName(void *db_link,UINT8_T *name);
UINT8_T db_TableByName(void *db_link,UINT8_T *name);

UINT8_T db_AddNewDB(void *db_addr,UINT8_T *name);

UINT8_T db_GetDB(void *db_link,UINT8_T *name);

//���� db_link = NULL �� ������ ����� ��� ����� ������� ��
//���� ��������� �� ��� �������, �� �����������
UINT8_T db_GetAllDB(void *db_link, UINT8_T *name,UINT8_T max_len);

UINT8_T db_LoadArray(UINT8_T index, UINT32_T addr, UINT8_T **arr);
//db_GetTBL
//db_GetAllTBL

//������ �������� � ��������
//UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size);
//db_record_next
//db_record_prev
//db_record_add
//db_record_del

//�������� ������

#ifdef  __cplusplus
}
#endif

#endif