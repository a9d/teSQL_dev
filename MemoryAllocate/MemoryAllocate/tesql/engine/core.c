#include "core.h"
#include "err_code.h"
#include "sector.h"
#include "system_var.h"
#include "sector_hal.h"
#include "sql.h"
#include <memory.h>
#include <string.h>

#define MODE_DROPE  0
#define MODE_CREATE 1
#define MODE_SET	2

UINT8_T mode_create;
UINT32_T last_db;
UINT32_T last_tbl;


extern void ApplicationSqlErr(UINT8_T err);


UINT8_T DeleteDB(void *db_addr); //�������� ��


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



//������� 
//���������
//���

//�������� �������
//db_LoadArray(�����, ���������)



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

UINT8_T DeleteDB(void *db_addr)
{
	UINT8_T err;
	DB_Record *rec=NULL;
	UINT32_T name_addr;

	//�������� ���� �������
	//�������� ���� ������

	//�������� ��
	rec=(DB_Record*)local_malloc(sizeof(DB_Record));
	if(rec!=NULL)
	{
		memset(rec,0x00,sizeof(DB_Record));

		rec->index=sector_GetStartIndex();
		rec->addrlen=sector_GetAddrLen(rec->index);	
		memcpy(&rec->addr_cur,db_addr,rec->addrlen);

		//������� ������� �������� ������
		if(rec->addr_cur==(UINT32_T)NULL || rec->addr_cur==sector_GetZeroSeg())
		{
			err=ERR_DB_ADDR;
		}
		else
		{
			err=db_record_cur(rec);

			if(err==ERR_OK)
			{
				//��������� ������� �����
				name_addr=0;
				memcpy(&name_addr,rec->data+rec->addrlen*2,rec->addrlen);

				if(name_addr!=0)
				{
					//������� ������� � ������
					err=sector_Free(rec->index,name_addr);
				}

				local_free(rec->data);
			
				if(err==ERR_OK)
				{
					//������� ��
					err=db_record_del(rec);

					//�������� ��������� �� ��
					memset(db_addr,0,rec->addrlen);
				}
			}
		}

		local_free(rec);
	}
	else
	{
		err=ERR_LOCAL_MALLOC;
	}

	return err;
}

//������ �������
//����� �������
//��������� �� ���������
UINT8_T db_LoadArray(UINT8_T index, UINT32_T addr, UINT8_T **arr)
{
	UINT8_T err;
	UINT32_T size;

	*arr=NULL;

	err=sector_GetSegmentSize(index,addr,&size);
	if(err==ERR_OK)
	{
		//�������� ����� ��� ������
		*arr=(UINT8_T*)local_malloc(size);
		if(*arr!=NULL)
		{
			err=sector_read(index,addr,*arr,size);
			if(err!=ERR_OK)
			{
				local_free(*arr);
			}
		}
		else
		{
			err=ERR_LOCAL_MALLOC;
		}
	}

	return err;
}

//�������� ������� err=db_LoadArray(rec->index, arr_addr, &arr); 
//UINT8_T db_FindByName(UINT32_T first_addr, void *db_link,UINT8_T *name)
//{
//	UINT8_T err=ERR_OK;
//	UINT8_T next;
//	UINT8_T *name_check=NULL;
//	UINT32_T start_addr;
//	UINT32_T name_addr;
//	UINT32_T size;
//	UINT16_T str_size;
//	DB_Record *rec=NULL;
//	//���� ����� �� � db_link �� NULL
//
//	rec=(DB_Record*)local_malloc(sizeof(DB_Record));
//
//	if(rec!=NULL)
//	{
//		memset(rec,0x00,sizeof(DB_Record));
//
//		rec->index=sector_GetStartIndex(); 
//		rec->addrlen=sector_GetAddrLen(rec->index);
//		rec->addr_cur=first_addr;//sector_GetZeroSeg();
//		start_addr=rec->addr_cur;
//
//		//�������� db_link
//		//memset(db_link, 0x00, rec->addrlen);
//
//		//�������� �� ���� ������� � �����
//		err=db_record_cur( rec );
//
//		if(err!=ERR_OK)
//		{
//			local_free(rec);
//			return err;
//		}
//
//		local_free(rec->data);
//
//		if( (rec->addr_next==(UINT32_T)NULL) && (rec->addr_prev==(UINT32_T)NULL) )
//		{
//			//�� ����������
//			next=FALSE;
//		}
//		else
//		{
//			next=TRUE;
//		}
//
//
//		//�������� �� ���� �������
//		while(next)
//		{
//			err=db_record_next(rec);
//
//			if(err==ERR_OK)
//			{
//				//��������� ��������� �� ���
//				name_addr=(UINT32_T)NULL;
//				memcpy(&name_addr,rec->data+rec->addrlen*2,rec->addrlen);
//
//				if(name_addr!=(UINT32_T)NULL)
//				{
//					//��������� ���
//
//					//������ ��������
//					size=0;
//					err=sector_GetSegmentSize(rec->index,name_addr,&size);
//
//					//err=db_LoadArray(rec->index, name_addr, &arr); 
//					if(err==ERR_OK)
//					{
//						//�������� ����� ��� ������
//						name_check=(UINT8_T*)local_malloc(size);
//						if(name_check!=NULL)
//						{
//							err=sector_read(rec->index,name_addr,name_check,size);
//							if(err==ERR_OK)
//							{
//								//��������� ����� ������
//								size=0;
//								memcpy(&size,name_check,sizeof(UINT16_T));
//
//								//����� ����������� ������
//								str_size=strlen((CHAR*)name);
//
//								//���� ����� ����� ���������
//								if(size==str_size)
//								{
//									//����������
//									if(memcmp(name, name_check+sizeof(UINT16_T), size)==0)
//									{
//										//���� ��� �������, �� �������� ����� ��
//										//����� ��������� � ��������� ��
//										memcpy(db_link,&rec->addr_cur,rec->addrlen);
//										next=FALSE;
//									}
//								}
//							}
//							else
//							{
//								next=FALSE;
//							}
//							local_free(name_check);
//						}
//						else
//						{
//							err=ERR_LOCAL_MALLOC;
//							next=FALSE;
//						}
//					}
//					else
//					{
//						next=FALSE;
//					}
//				}
//
//				//���������� ������ ���������� ��� �������
//				local_free(rec->data);
//
//				if(rec->addr_next==start_addr)
//					next=FALSE;
//			}
//			else
//			{
//				next=FALSE;
//			}
//		}
//
//		//�����������
//		local_free(rec);
//	}
//	else
//	{
//		err=ERR_LOCAL_MALLOC;
//	}
//
//	return err;
//}

UINT8_T db_FindByName(UINT32_T first_addr, void *db_link,UINT8_T *name)
{
	UINT8_T err=ERR_OK;
	UINT8_T next;
	UINT8_T *name_check=NULL;
	UINT32_T start_addr;
	UINT32_T name_addr;
	UINT32_T size;
	UINT16_T str_size;
	DB_Record *rec=NULL;
	//���� ����� �� � db_link �� NULL

	rec=(DB_Record*)local_malloc(sizeof(DB_Record));

	if(rec!=NULL)
	{
		memset(rec,0x00,sizeof(DB_Record));

		rec->index=sector_GetStartIndex(); 
		rec->addrlen=sector_GetAddrLen(rec->index);
		rec->addr_cur=first_addr;//sector_GetZeroSeg();
		start_addr=rec->addr_cur;

		//�������� db_link
		//memset(db_link, 0x00, rec->addrlen);

		//�������� �� ���� ������� � �����
		err=db_record_cur( rec );

		if(err!=ERR_OK)
		{
			local_free(rec);
			return err;
		}

		local_free(rec->data);

		if( (rec->addr_next==(UINT32_T)NULL) && (rec->addr_prev==(UINT32_T)NULL) )
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
					err=db_LoadArray(rec->index, name_addr, &name_check); 
					if(err==ERR_OK)
					{
						//��������� ����� ������
						size=0;
						memcpy(&size,name_check,sizeof(UINT16_T));
						
						//����� ����������� ������
						str_size=strlen((CHAR*)name);
						
						//���� ����� ����� ���������
						if(size==str_size)
						{
							//����������
							if(memcmp(name, name_check+sizeof(UINT16_T), size)==0)
							{
								//���� ��� �������, �� �������� ����� ��
								//����� ��������� � ��������� ��
								memcpy(db_link,&rec->addr_cur,rec->addrlen);
								next=FALSE;
							}
						}

						local_free(name_check);

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

UINT8_T db_AddNewDB(void *db_addr,UINT8_T *name)
{
	UINT8_T err=ERR_OK;
	UINT32_T dbNameAddr=0;
	DB_Record *rec=NULL;
	UINT16_T str_size;

	rec=(DB_Record*)local_malloc(sizeof(DB_Record));

	if(rec!=NULL)
	{
		memset(rec,0x00,sizeof(DB_Record));

		rec->index=sector_GetStartIndex(); 
		rec->addrlen=sector_GetAddrLen(rec->index);
		rec->addr_cur=sector_GetZeroSeg();

		if(name!=NULL)
		{
			//������ �����
			str_size=strlen((CHAR*)name);
			
			rec->size=sizeof(UINT16_T)+str_size; //����� ������ + ������
			
			rec->data=(UINT8_T*)sector_RamMalloc(rec->index,&rec->size);
			if(rec->data!=NULL)
			{
				//�������� ����� ������
				memcpy(rec->data,&str_size,sizeof(UINT16_T));
				//�������� ������
				memcpy(rec->data+sizeof(UINT16_T),name,str_size);

				//�������� �������
				err=sector_Malloc(rec->index,&dbNameAddr,rec->size);
				if(err==ERR_OK)
				{
					//���������� ��� ��
					err=sector_write(rec->index,dbNameAddr,rec->data,rec->size);

					if(err!=ERR_OK)
					{
						//���� ������ �� �������, �� ������� ���������� �������
						sector_Free(rec->index,dbNameAddr);
					}
				}

				sector_RamFree(rec->data);
			}
			else
			{
				err=ERR_LOCAL_MALLOC;
			}
		}

		//��������� err
		if(err==ERR_OK)
		{
			//err=db_record_cur( rec );
			//if(err==ERR_OK)
			//{
			//	local_free(rec->data);

			//	if( rec->addr_next!=(UINT32_T)NULL && rec->addr_prev!=(UINT32_T)NULL )
			//	{
			//		//��������� �� ��������� ������
			//		rec->addr_cur=rec->addr_prev;
			//	}
			//}


			//�������� ����� ��� 
			//next,prev,name,table
			rec->size=rec->addrlen*4;
			rec->data= (UINT8_T*)sector_RamMalloc(rec->index,&rec->size);

			if(rec->data!=NULL)
			{
				memset(rec->data,0x00, rec->size);

				if(dbNameAddr!=0)
				{
					//���������� ��������� �� ��� ��
					memcpy(rec->data+rec->addrlen*2, &dbNameAddr, rec->addrlen);
				}

				err=db_record_add( rec );

				//���������� ��������� �� ��
				memcpy(db_addr,&rec->addr_cur,rec->addrlen);

				//�������� ��������� �� ��������� ��
				//last_db=rec->addr_cur;

				sector_RamFree(rec->data);
			}
			else
			{
				//������� ������ � ������
				if(dbNameAddr!=0)
				{
					sector_Free(rec->index,dbNameAddr);
				}
				err=ERR_LOCAL_MALLOC;
			}
		}

		local_free(rec);
	}
	else
	{
		err=ERR_LOCAL_MALLOC;
	}

	return err;
}

UINT8_T db_GetDB(void *db_link,UINT8_T *name)
{
	UINT8_T err;
	//��������� �������
	LOCK;
	err=db_FindByName(sector_GetZeroSeg(),db_link,name);
	//���������� �������
	UNLOCK;
	return err;
}


UINT8_T db_GetAllDB(void *db_link, UINT8_T *name,UINT8_T max_len)
{
	UINT8_T err=ERR_OK;
	UINT32_T arr_addr;
	DB_Record *rec=NULL;
	UINT8_T *arr=NULL;

	//��������� �������
	LOCK;

	rec=(DB_Record*)local_malloc(sizeof(DB_Record));

	if(rec!=NULL)
	{
		memset(rec,0x00,sizeof(DB_Record));
		
		rec->index=sector_GetStartIndex();
		rec->addrlen=sector_GetAddrLen(rec->index);

		memcpy(&rec->addr_cur ,db_link,rec->addrlen);

		//���� 0 �� ��������� ������ ������
		if(rec->addr_cur==0)
		{
			//����� �������� ��������
			rec->addr_cur=sector_GetZeroSeg();
		}
		
		//��������� ������� ������
		err=db_record_cur(rec);
		if(err==ERR_OK)
		{
			local_free(rec->data);

			if( rec->addr_next==(UINT32_T)NULL && rec->addr_prev==(UINT32_T)NULL )
			{
				//� ������ ��� ��
				err=ERR_DB_END;
			}
		}


		if(err==ERR_OK)
		{
			//��������� ��������� �� ��
			err=db_record_next(rec);
			
			if(err==ERR_OK)
			{
				//���� ��������� ��� � ���
				if(max_len>0)
				{
					//��������� ��������� �� NULL
					arr_addr=0;
					memcpy(&arr_addr,rec->data+2*rec->addrlen,rec->addrlen);

					if(arr_addr!=(UINT32_T)NULL)
					{
						//��������� ���
						err=db_LoadArray(rec->index, arr_addr, &arr); 

						//������� ����� �������
						arr_addr=0;
						memcpy(&arr_addr,arr,sizeof(UINT16_T));

						if(arr_addr<max_len)
						{
							memcpy(name, arr+sizeof(UINT16_T), arr_addr);
							name[arr_addr]=0;
						}
						else
						{
							err=ERR_NAME_LEN;
						}

						if(err==ERR_OK || err==ERR_NAME_LEN)
						{
							local_free(arr);
						}
					}
					else
					{
						name[0]=0;
					}
				}
				local_free(rec->data);

				memcpy(db_link , &rec->addr_cur, rec->addrlen);

				//��������� ��������� ��
				if(rec->addr_next==sector_GetZeroSeg())
				{
					//����� ������
					err=ERR_DB_END;
				}
			}
		}
		
		local_free(rec);
	}
	else
	{
		err=ERR_LOCAL_MALLOC;
	}

	//���������� �������
	UNLOCK;
	return err;
}


void db_create_tbl(UINT8_T index, void *addr ,void *name,...)
{
	//void **p=&arg;
}

//void db_create_tbl_rows(void *arg,...)
//{
//}

void db_create_tbl_row(void *addr,void *name, UINT16_T param,...)
{
}

void db_save_sector(UINT8_T index)
{
}

void db_create(void *db_link, void *arg,...)
{
	void **p=&arg;

	void *db_addr;
	UINT8_T err=ERR_OK;
	UINT32_T addr=0;

	//������ �������� ��� ������ ���� ������
	if(db_link==NULL )
	{
		//������
		ApplicationSqlErr(ERR_SQL_DB_ADDR);
		return;
	}
	else
	{
		db_addr=db_link;
	}

	//������� � ���������� ���������
	//p++;

	if(mode_create==MODE_CREATE)
	{
		if((UINT32_T)*p!=(UINT32_T)NULL)// && (UINT32_T)*p!=MAGIC_WORD)
		{
			//�������� ���������� �� ��� �� � �������� ������
			err=db_GetDB(&addr,(UINT8_T*)*p);//db_FindByName(sector_GetZeroSeg(),&addr,(UINT8_T*)*p);
		}

		if(err==ERR_OK)
		{ 
			//���� addr!=0 �� �� � �������� ������ ��� ���������� 
			if(addr==0)
			{
				err=db_AddNewDB(db_addr,(UINT8_T*)*p);

				//if(err==ERR_OK)
				//{
				//	//�������� ������ ������
				//	addr=sector_GetStartIndex();
				//	addr=sector_GetAddrLen(addr);

				//}
			}
			else
			{
				err=ERR_DB_ALREDY_EXISTS;
			}
		}
	}
	else if(mode_create==MODE_DROPE)
	{
		//�������� ������ �� ������

		//������� ��
		//������� ��� ������� ��
		//������� ��� ������ ��

		err=DeleteDB(db_addr);
		
	}
	else if(mode_create==MODE_SET)
	{
		//last_db=0;
	}
	else
	{
		err=ERR_WRONG_MODE;
	}


	if(err!=ERR_OK)
	{
		ApplicationSqlErr(err);
	}
	else
	{
		//��������� ��������� �� ��������� ��
		
		//�������� ������ ������
		addr=sector_GetStartIndex();
		addr=sector_GetAddrLen(addr);

		last_db=0;
		memcpy(&last_db,db_addr,addr);
	}
}



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

//������ ��������� ������ � �����
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
					//next = prev

					//next
					//memcpy(rec->data, &buf->addr_next, buf->addrlen);
					memcpy(rec->data, &buf->addr_cur, buf->addrlen);
					//prev
					memcpy(rec->data+rec->addrlen, &buf->addr_prev, buf->addrlen);
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
						//memcpy(buf->data, &addr_new, buf->addrlen);
						//prev
						memcpy(buf->data+buf->addrlen, &addr_new, buf->addrlen);

						err=sector_write(buf->index, buf->addr_cur, buf->data, buf->size);

						if(err==ERR_OK)
						{
							//�������� ��������� ������
							local_free(buf->data);
							//err=db_record_next(buf);
							err=db_record_prev(buf);
						
							if(err==ERR_OK)
							{
								//� ��������� �������� ������ prev = addr_new
								//prev
								//memcpy(buf->data+buf->addrlen, &addr_new, buf->addrlen);
								//next
								memcpy(buf->data, &addr_new, buf->addrlen);

								err=sector_write(buf->index, buf->addr_cur, buf->data, buf->size);
							}
						
						}

					}
				}//if
				else
				{
					//������� ���������� ������ ���� ������ �� �������
					sector_Free(rec->index,addr_new);
				}
				
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
	UINT8_T err;
	UINT32_T next,prev;
	//������� ��������� ������
	//err=db_record_cur(rec);

	//if(err==ERR_OK)
	//{
		//local_free(rec->data);

		//������� �������
		err=sector_Free(rec->index,rec->addr_cur);

		if(err==ERR_OK)
		{
			if(rec->addr_next!=rec->addr_prev)
			{
				next=rec->addr_next;
				prev=rec->addr_prev;

				//������� next � �������� ���� prev
				rec->addr_cur=next;
				err=db_record_cur(rec);
				if(err==ERR_OK)
				{
					memcpy(rec->data+rec->addrlen, &prev, rec->addrlen);
					err=sector_write(rec->index,rec->addr_cur,rec->data,rec->size);
					local_free(rec->data);
				}

				if(err!=ERR_OK)
					return err;

				//������� prev � �������� ���� next
				rec->addr_cur=prev;
				err=db_record_cur(rec);
				if(err==ERR_OK)
				{
					memcpy(rec->data, &next, rec->addrlen);
					err=sector_write(rec->index,rec->addr_cur,rec->data,rec->size);
					local_free(rec->data);
				}

				//if(err!=ERR_OK)
				//	return err;
			}
			else if(rec->addr_next==rec->addr_prev)
			{
				//������������� ������ � ������
				err=db_record_next(rec);

				if(err==ERR_OK)
				{
					memset(rec->data,0x00,rec->addrlen*2);
					err=sector_write(rec->index,rec->addr_cur,rec->data,rec->size);
					local_free(rec->data);
				}
			}
			//else
			//{
			//	//�������� ������
			//}
		}
	//}

	return err;
}
