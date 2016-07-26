#include "core.h"
#include "err_code.h"
#include "sector.h"
#include "system_var.h"
#include "sector_hal.h"
#include "sql.h"
#include <memory.h>

#define MODE_DROPE  0
#define MODE_CREATE 1

UINT8_T mode_create;



extern void ApplicationSqlErr(UINT8_T err);



		//����� ��(��� ����� ��)
		//-��������� �� ��� �� - ��������� NULL
		//-��������� �� ������ ������ - NULL ���� ������ ��� �� ������
		//-��������� �� ��������� ��
		//-CRC ���� ���������

//������ ��������
//typedef struct DB_HEADER
//{
//	UINT32_T	next;   //����� ��������� ������
//	UINT32_T	prev;	//����� ���������� ������
//}DB_Header;
//
////������ ���������
//typedef struct
//{
//	struct DB_HEADER header;
//	UINT32_T	name;       //��������� �� ��� ��
//	UINT32_T	tbl_list;	//��������� �� ������ ������
//}DB_List;




//UINT8_T recor2db_header(UINT8_T index, DB_Header *header, UINT8_T *data);
//void recor2db_header_list(UINT8_T index, DB_List *list, UINT8_T i, UINT8_T *data);

//0-drop
//1-create
void db_set_mode(UINT8_T mode)
{
	mode_create=mode;
}

//�������������� ������ � ���������
//UINT8_T recor2db_header(UINT8_T index, DB_Header *header, UINT8_T *data)
//{
//	UINT8_T i;	 //������� ������� � �������
//	UINT8_T len; //����� ����
//
//	len=sector_GetAddrLen(index);
//
//	i=0;
//	memcpy(&header->next,data,len);
//	i+=len;
//	memcpy(&header->prev,data+i,len);
//	i+=len;
//
//	return i;
//}

////�������������� ������ � ����
//void recor2db_header_list(UINT8_T index, DB_List *list, UINT8_T i, UINT8_T *data)
//{
//	UINT8_T len; //����� ����
//
//	len=sector_GetAddrLen(index);
//
//	memcpy(&list->name,data+i,len);
//	i+=len;
//	memcpy(&list->tbl_list,data+i,len);
//	i+=len;
//}

//������ ������ � crc
//������ ��� ����� ����� �������

UINT8_T db_FindByName(void *db_link,UINT8_T *name)
{
	UINT8_T err=ERR_OK;
	UINT8_T next;
	UINT8_T *name_check=NULL;
	UINT32_T start_addr;
	UINT32_T name_addr;
	UINT32_T size;
	DB_Record *rec=NULL;
	//���� ����� �� � db_link �� NULL

	rec=(DB_Record*)local_malloc(sizeof(DB_Record));

	if(rec!=NULL)
	{
		memset(rec,0x00,sizeof(DB_Record));

		rec->index=sector_GetStartIndex(); 
		rec->addrlen=sector_GetAddrLen(rec->index);
		rec->addr_cur=sector_GetZeroSeg();
		start_addr=rec->addr_cur;

		//�������� db_link
		memset(db_link, 0x00, rec->addrlen);

		//�������� �� ���� ������� � �����
		err=db_record_cur( rec );

		if(err!=ERR_OK)
		{
			local_free(rec);
			return err;
		}

		local_free(rec->data);

		if( (rec->addr_next==(UINT32_T)NULL) && (rec->addr_prev=(UINT32_T)NULL) )
		{
			//�� ����������
			next=FALSE;
		}
		else
		{
			next=TRUE;
		}


		//�������� �� ���� �������
		while(next)
		{
			err=db_record_next(rec);

			if(err==ERR_OK)
			{
				//��������� ��������� �� ���
				name_addr=(UINT32_T)NULL;
				memcpy(&name_addr,rec->data+rec->addrlen*2,rec->addrlen);

				if(name_addr!=(UINT32_T)NULL)
				{
					//��������� ���

					//������ ��������
					size=0;
					err=sector_GetSegmentSize(rec->index,name_addr,&size);
					if(err==ERR_OK)
					{
						//�������� ����� ��� ������
						name_check=(UINT8_T*)local_malloc(size);
						if(name_check!=NULL)
						{
							err=sector_read(rec->index,name_addr,name_check,size);
							if(err==ERR_OK)
							{
								//��������� ����� ������
								size=0;
								memcpy(&size,name_check,sizeof(UINT16_T));

								//����������
								if(memcmp(name, name_check+sizeof(UINT16_T), size)==0)
								{
									//���� ��� �������, �� �������� ����� ��
									//����� ��������� � ��������� ��
									memcpy(db_link,&rec->addr_cur,rec->addrlen);
									next=FALSE;
								}
							}
							else
							{
								next=FALSE;
							}
							local_free(name_check);
						}
						else
						{
							err=ERR_LOCAL_MALLOC;
							next=FALSE;
						}
					}
					else
					{
						next=FALSE;
					}
				}

				//���������� ������ ���������� ��� �������
				local_free(rec->data);

				if(rec->addr_next==start_addr)
					next=FALSE;
			}
			else
			{
				next=FALSE;
			}
		}

		//�����������
		local_free(rec);
	}
	else
	{
		err=ERR_LOCAL_MALLOC;
	}

	return err;
}

void db_create(void *arg,...)
{
	void **p=&arg;

	void *db_addr;
	
	DB_Record *rec=NULL;

	//������ �������� ��� ������ ���� ������
	if(*p==NULL)
	{
		//������
		ApplicationSqlErr(ERR_SQL_DB_ADDR);
		return;
	}
	else
	{
		db_addr=*p;
	}

	//������� � ���������� ���������
	p++;

	if(mode_create==MODE_CREATE)
	{
		if(*p!=NULL)
		{
			//���� ���� ��� �� �������� ����� �� � �������� ������

			db_FindByName(db_addr,(UINT8_T*)*p);


			//���������� ����� �� ������ ���� ���������� �������  !!!!!!!!!!

		}
		else
		{
			//������� �� ��� �����

			rec=(DB_Record*)local_malloc(sizeof(DB_Record));
			
			if(rec!=NULL)
			{
				memset(rec,0x00,sizeof(DB_Record));

				rec->index=sector_GetStartIndex(); 
				rec->addrlen=sector_GetAddrLen(rec->index);
				rec->addr_cur=sector_GetZeroSeg();

				//�������� ����� ��� 
				//next,prev,name,table
				rec->size=rec->addrlen*4;
				rec->data= (UINT8_T*)sector_RamMalloc(rec->index,&rec->size);

				if(rec->data!=NULL)
				{
					memset(rec->data,0x00, rec->size);

					db_record_add( rec );

					memcpy(db_addr,&rec->addr_cur,rec->addrlen);
					sector_RamFree(rec->data);
				}
				else
				{
					ApplicationSqlErr(ERR_LOCAL_MALLOC);
				}

				local_free(rec);
			}
			else
			{
				ApplicationSqlErr(ERR_LOCAL_MALLOC);
				return;
			}
		}
	}
	else
	{
		//�������� ������ �� ������
	}
}


//UINT8_T db_record_load(UINT8_T index,UINT32_T addr, UINT8_T **buf,UINT32_T *size)
//{
//	UINT8_T err;
//
//	err=sector_GetSegmentSize(index, addr, size);
//
//	if(err==ERR_OK)
//	{
//		*buf=(UINT8_T*)local_malloc(*size);
//		if(buf!=NULL)
//		{
//			err=sector_read(index,addr,*buf,*size);
//		}
//		else
//		{
//			err=ERR_LOCAL_MALLOC;
//		}
//	}
//
//	return err;
//}

UINT8_T db_record_cur( DB_Record *rec )
{
	UINT8_T err=ERR_OK;

	err=sector_GetSegmentSize(rec->index, rec->addr_cur, &rec->size);

	if(err==ERR_OK)
	{
		rec->data=(UINT8_T*)local_malloc(rec->size);
		if(rec->data!=NULL)
		{
			err=sector_read(rec->index,rec->addr_cur,rec->data,rec->size);

			//���� ��� ������ �� ��������� ���� next � prev
			if(err==ERR_OK)
			{
				rec->addr_next=0;
				memcpy(&rec->addr_next,rec->data,rec->addrlen);
				rec->addr_prev=0;
				memcpy(&rec->addr_prev,rec->data+rec->addrlen,rec->addrlen);
			}
			else
			{
				local_free(rec->data);
			}
		}
		else
		{
			err=ERR_LOCAL_MALLOC;
		}
	}

	return err;
}


UINT8_T db_record_prev( DB_Record *rec )
{
	rec->addr_cur=rec->addr_prev;
	return db_record_cur(rec);
}

UINT8_T db_record_next( DB_Record *rec )
{
	rec->addr_cur=rec->addr_next;
	return db_record_cur(rec);
}

	//UINT8_T	index;		//������ �������
	//UINT8_T	addrlen;	//����� ������
	//UINT32_T	addr_cur;	//������� ������, ��� �������
	//UINT32_T	addr_next;	//�� ������������
	//UINT32_T	addr_prev;	//�� ������������ 
	//UINT32_T	size;		������ ������������� ����
	//UINT8_T	*data;		������ ��� ������
UINT8_T db_record_add( DB_Record *rec )
{
	UINT8_T err=ERR_OK;
	UINT32_T addr_new;
	DB_Record *buf=NULL;
	//��������� ��

	//!!!!!!!!!!
	//������ ������� ����� ��������
	//������� ���������� ���������� �� ������ ��������� ������

	if( rec->size < (UINT32_T)(rec->addrlen*2))
	{
		return ERR_WRONG_SIZE;
	}

	buf=(DB_Record*)local_malloc(sizeof(DB_Record));

	if(buf!=NULL)
	{
		memset(buf,0x00,sizeof(DB_Record));
		buf->index=rec->index;
		buf->addr_cur=rec->addr_cur;
		buf->addrlen=rec->addrlen;
		err=db_record_cur(buf); //��������� ������� ������

		if(err==ERR_OK)
		{
			err=sector_Malloc(rec->index,&addr_new,rec->size); //�������� ����� ��� ����� ������

			if(err==ERR_OK)
			{
				if( buf->addr_next== (UINT32_T)NULL && buf->addr_prev==(UINT32_T)NULL )
				{
					//������ ������
					//next
					memcpy(rec->data, &rec->addr_cur, rec->addrlen);
					//prev
					memcpy(rec->data+rec->addrlen, &rec->addr_cur, rec->addrlen);
				}
				else
				{
					//�������� ������
					//������� ����� ���������
					//� ����� prev = cur
					//		  next = old_next

					//next
					memcpy(rec->data, &buf->addr_next, buf->addrlen);
					//prev
					memcpy(rec->data+rec->addrlen, &buf->addr_cur, buf->addrlen);
				}


				//���������� ������
				err=sector_write(rec->index,addr_new,rec->data,rec->size);

				if(err==ERR_OK)
				{
					//���� ��� ������, �� �������� ���������

					//���� ������ ������ �� �������� ������ ������ �������
					if( buf->addr_next== (UINT32_T)NULL && buf->addr_prev==(UINT32_T)NULL )
					{
						//next
						memcpy(buf->data, &addr_new, buf->addrlen);
						//prev
						memcpy(buf->data+buf->addrlen, &addr_new, buf->addrlen);

						err=sector_write(buf->index, buf->addr_cur, buf->data, buf->size);
					}
					else
					{
						//����� ������ � ���������

						//� ���������� �������� ������ next = addr_new
						//next
						memcpy(buf->data, &addr_new, buf->addrlen);

						err=sector_write(buf->index, buf->addr_cur, buf->data, buf->size);

						if(err==ERR_OK)
						{
							//�������� ��������� ������
							local_free(buf->data);
							err=db_record_next(buf);

						
							if(err==ERR_OK)
							{
								//� ��������� �������� ������ prev = addr_new
								//prev
								memcpy(buf->data+buf->addrlen, &addr_new, buf->addrlen);

								err=sector_write(buf->index, buf->addr_cur, buf->data, buf->size);
							}
						
						}

					}
				}//if
				
				rec->addr_cur=addr_new;
				local_free(buf->data);
			}
		}//if

		local_free(buf);
	}
	else
	{
		err=ERR_LOCAL_MALLOC;
	}

	return err;
}

UINT8_T db_record_del( DB_Record *rec )
{
	return 0;
}
