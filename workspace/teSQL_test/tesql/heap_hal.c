#include <stdlib.h>
#include "portable.h"
#include "sql_db_config.h"

#include "heap_4.h"
//UINT8_T ucHeap[2000];
//UINT8_T ucHeap1[2000];

extern void fat_write(UINT32_T addr, void *data, UINT16_T size);
extern void fat_read(UINT32_T addr, void *data, UINT16_T size);

/*-----------------------------------------------------------*/
UINT8_T sector_write(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size)
{
	UINT16_T i;

	if(sector==0)
	{
		fat_write(addr,data, size);
//		for(i=0;i<size;i++ )
//		{
//			*(ucHeap+addr+i)=*((UINT8_T*)data+i);
//		}
	}
//	else if(sector==1)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*(ucHeap1+addr+i)=*((UINT8_T*)data+i);
//		}
//	}

	return ERR_OK;
}

/*-----------------------------------------------------------*/
UINT8_T sector_read(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size)
{
	UINT16_T i;

	if(sector==0)
	{
		fat_read(addr,data, size);
//		for(i=0;i<size;i++ )
//		{
//			*((UINT8_T*)data+i)=*(ucHeap+addr+i);
//		}
	}
//	else if(sector==1)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*((UINT8_T*)data+i)=*(ucHeap1+addr+i);
//		}
//	}

	return ERR_OK;
}


/*-----------------------------------------------------------*/
void *local_malloc(size_t size)
{
	return pvPortMalloc(size);
}

/*-----------------------------------------------------------*/
void local_free(void *block)
{
	vPortFree(block);
}
