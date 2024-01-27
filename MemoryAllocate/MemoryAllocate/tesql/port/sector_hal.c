#include <stdlib.h>
#include "portable.h"
//#include "err_code.h"
//#include "system_var.h"

//UINT8_T ucHeap[100];
//UINT8_T ucHeap1[2000];
//
///*-----------------------------------------------------------*/
//UINT8_T local_write(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size)
//{
//	UINT16_T i;
//
//	if(sector == SECTOR_RAM_0)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*(ucHeap+addr+i)=*((UINT8_T*)data+i);
//		}
//	}
//	else if(sector == SECTOR_RAM_1)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*(ucHeap1+addr+i)=*((UINT8_T*)data+i);
//		}
//	}
//
//	return ERR_OK;
//}
//
///*-----------------------------------------------------------*/
//UINT8_T local_read(UINT8_T sector, UINT32_T addr, void *data, UINT16_T size)
//{
//	UINT16_T i;
//
//	if(sector == SECTOR_RAM_0)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*((UINT8_T*)data+i)=*(ucHeap+addr+i);
//		}
//	}
//	else if(sector == SECTOR_RAM_1)
//	{
//		for(i=0;i<size;i++ )
//		{
//			*((UINT8_T*)data+i)=*(ucHeap1+addr+i);
//		}
//	}
//
//	return ERR_OK;
//}


/*-----------------------------------------------------------*/
void *local_malloc(SIZE_T size)
{
	return malloc(size);
}

/*-----------------------------------------------------------*/
void local_free(void *block)
{
	free(block);
}