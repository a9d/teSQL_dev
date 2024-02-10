#include <stdlib.h>
#include <memory.h>
#include "table.h"
#include "err_code.h"
#include "sector_hal.h"

/* Define the linked list structure.  This is used to link free blocks in order
of their memory address. */
typedef struct A_BLOCK_LINK
{
	UINT32_T pxNextFreeBlock;	/*<< The next free block in the list. */
	UINT32_T xBlockSize;		/*<< The size of the free block. */
}BlockLink_t;

typedef struct BLOCK_LINK
{
	UINT32_T pxCurrentAddr;
	struct A_BLOCK_LINK body;
}BlockLink;

/*
 * Inserts a block of memory that is being freed into the correct position in
 * the list of free memory blocks.  The block being freed will be merged with
 * the block in front it and/or the block behind it if the memory blocks are
 * adjacent to each other.
 */
UINT8_T prvInsertBlockIntoFreeList(TableInfo* tab_ptr, BlockLink *pxBlockToInsert );

/*-----------------------------------------------------------*/
UINT32_T memory_aligment(UINT32_T aligment, UINT32_T size);
UINT8_T	memory_init(TableInfo* tab_ptr);

UINT8_T WriteBlockLink(TableInfo* tab_ptr, BlockLink* bl);
UINT8_T ReadBlockLink(TableInfo* tab_ptr, BlockLink *bl);

/*-----------------------------------------------------------*/
//Инициализация таблицы
//
//tab_ptr - параметры таблицы
//addrLen - длина поля адресс в байтах
//sizeLen - длина поля размер в байтах
//aligment - выравнивание памяти в байтах
//startAddr - адрес начала таблицы
//endAddr - адрес конца таблицы
//Read - указатель на функцию чтения
//Write - указатель на функцию записи
//Crc - указатель на функцию CRC, если используется
UINT8_T table_Init(TableInfo* tab_ptr,
	UINT8_T addrLen,
	UINT8_T sizeLen,
	UINT16_T aligment,
	UINT32_T startAddr,
	UINT32_T endAddr,
	read_t Read,
	write_t Write,
	crc_t Crc)
{
	if (tab_ptr == NULL)
		return ERR_TABLE_NULL;

	if (addrLen == 0 || addrLen > 4)
		return ERR_ADDR_LEN;
	else
		tab_ptr->StartAddrLen = addrLen;

	if (sizeLen == 0 || sizeLen > 4)
		return ERR_SIZE_LEN;
	else
		tab_ptr->TableSizeLen = sizeLen;

	if (aligment == 0)
		return ERR_WRONG_ALIGMENT;
	else
		tab_ptr->ByteAligment = aligment;

	tab_ptr->StartAddr = memory_aligment(tab_ptr->ByteAligment, startAddr);

	tab_ptr->EndAddr = memory_aligment(tab_ptr->ByteAligment, endAddr);
	if (tab_ptr->EndAddr > endAddr)
		tab_ptr->EndAddr = tab_ptr->EndAddr - tab_ptr->ByteAligment;

	if(tab_ptr->EndAddr == 0 || tab_ptr->EndAddr <= tab_ptr->StartAddr)
		return ERR_NO_FREE_SPACE;

	if (Read == NULL)
		return ERR_NO_READ_FUNCTION;
	else
		tab_ptr->read = Read;

	if (Write == NULL)
		return ERR_NO_WRITE_FUNCTION;
	else
		tab_ptr->write = Write;

	tab_ptr->crc = Crc;

	//расчитваем размер блок линка
	tab_ptr->bl_size = tab_ptr->StartAddrLen + tab_ptr->TableSizeLen;
	if(tab_ptr->crc != NULL)
		tab_ptr->bl_size += sizeof(UINT16_T);
	//учитываем выравнивание сектора
	tab_ptr->bl_size = memory_aligment(tab_ptr->ByteAligment, tab_ptr->bl_size);

	tab_ptr->FreeBytesRemaining = tab_ptr->EndAddr - tab_ptr->StartAddr;

#if (configUSE_SegmentCounter==TRUE)
	tab_ptr->xSegmentCounter = 0;
#endif

	return memory_init(tab_ptr);
}

UINT32_T memory_aligment(UINT32_T aligment,UINT32_T size)
{
	return ((size+(aligment-1))&~(aligment-1));
}

UINT8_T	memory_init(TableInfo* tab_ptr)
{
	BlockLink	pxFirstFreeBlock;
	BlockLink	pxEnd;
	BlockLink	xStart;
	//UINT32_T	xTotalHeapSize;
	UINT8_T		err = ERR_OK;

	xStart.pxCurrentAddr = 0;
	xStart.body.pxNextFreeBlock = 0;
	xStart.body.xBlockSize = 0;

	pxEnd.pxCurrentAddr = 0;
	pxEnd.body.pxNextFreeBlock = 0;
	pxEnd.body.xBlockSize = 0;

	pxFirstFreeBlock.pxCurrentAddr = 0;
	pxFirstFreeBlock.body.pxNextFreeBlock = 0;
	pxFirstFreeBlock.body.xBlockSize = 0;

	/* xStart is used to hold a pointer to the first item in the list of free
	blocks.  The void cast is used to prevent compiler warnings. */
	xStart.pxCurrentAddr = tab_ptr->StartAddr;
	xStart.body.pxNextFreeBlock = tab_ptr->StartAddr + tab_ptr->bl_size;
	xStart.body.xBlockSize = 0;
	err = WriteBlockLink(tab_ptr, &xStart);
	
	if(err == ERR_OK)
	{
		tab_ptr->FreeBytesRemaining -= tab_ptr->bl_size;
		//tab_ptr->HeadAddr = xStart.body.pxNextFreeBlock;
		//xTotalHeapSize = tab_ptr->FreeBytesRemaining - tab_ptr->bl_size;

		/* pxEnd is used to mark the end of the list of free blocks and is inserted
		at the end of the heap space. */
		tab_ptr->EndAddr = tab_ptr->EndAddr - tab_ptr->bl_size;

		pxEnd.pxCurrentAddr = tab_ptr->EndAddr;
		pxEnd.body.pxNextFreeBlock = 0;
		pxEnd.body.xBlockSize = 0;
		err = WriteBlockLink(tab_ptr, &pxEnd);

		if(err == ERR_OK)
		{
			/* To start with there is a single free block that is sized to take up the
			entire heap space, minus the space taken by pxEnd. */
			pxFirstFreeBlock.pxCurrentAddr = xStart.body.pxNextFreeBlock;
			pxFirstFreeBlock.body.xBlockSize = tab_ptr->FreeBytesRemaining - tab_ptr->bl_size;
			pxFirstFreeBlock.body.pxNextFreeBlock = tab_ptr->EndAddr;
			err = WriteBlockLink(tab_ptr, &pxFirstFreeBlock);

			if(err == ERR_OK)
			{
				/* Only one block exists - and it covers the entire usable heap space. */
				tab_ptr->FreeBytesRemaining = pxFirstFreeBlock.body.xBlockSize;

				#if (configUSE_SegmentCounter == TRUE)
				tab_ptr->xSegmentCounter = 3;
				#endif
			}
		}
	}

	return err;
}

/*-----------------------------------------------------------*/
#if (configUSE_SegmentCounter==TRUE)
UINT32_T table_GetSegmentCounter(TableInfo* tab_ptr)
{
	return tab_ptr->xSegmentCounter;
}
#endif

/*-----------------------------------------------------------*/
//index - номер сектора
UINT32_T table_GetFreeSize(TableInfo* tab_ptr)
{
	return tab_ptr->FreeBytesRemaining;
}

/*-----------------------------------------------------------*/
UINT8_T WriteBlockLink(TableInfo* tab_ptr, BlockLink *bl)
{
	UINT16_T crc;
	UINT8_T	*buf;
	UINT8_T	err = ERR_OK;

	buf = (UINT8_T*)local_malloc(tab_ptr->bl_size);

	if(buf == NULL)
		return ERR_LOCAL_MALLOC;

	memset((void*)buf, 0x00, tab_ptr->bl_size);

	//сформировать пакет для записи и сгенерить crc16 если требуется
	memcpy((void*)buf,(void*)&bl->body.pxNextFreeBlock, tab_ptr->StartAddrLen);
	memcpy((void*)(buf + tab_ptr->StartAddrLen),(void*)&bl->body.xBlockSize, tab_ptr->TableSizeLen);

	if(tab_ptr->crc != NULL)
	{
		crc = 0xFFFF;
		crc = tab_ptr->crc(crc, buf, tab_ptr->StartAddrLen + tab_ptr->TableSizeLen);

		memcpy((void*)(buf + tab_ptr->StartAddrLen + tab_ptr->TableSizeLen),(void*)&crc,sizeof(UINT16_T));
	}

	err = tab_ptr->write(bl->pxCurrentAddr, (void*)buf, tab_ptr->bl_size);

	local_free(buf);

	return err;
}

/*-----------------------------------------------------------*/
UINT8_T ReadBlockLink(TableInfo* tab_ptr, BlockLink* bl)
{
	UINT16_T crc;
	UINT8_T *buf;
	UINT8_T err=ERR_OK;

	buf=(UINT8_T*)local_malloc(tab_ptr->bl_size);

	if(buf==NULL)
		return ERR_LOCAL_MALLOC;

	err = tab_ptr->read(bl->pxCurrentAddr, (void*)buf, tab_ptr->bl_size );

	if (err != ERR_OK)
	{
		local_free(buf);
		return err;
	}

	//проверка CRC если требуется
	if(tab_ptr->crc != NULL)
	{
		crc = 0xFFFF;
		crc = tab_ptr->crc(crc, buf, tab_ptr->StartAddrLen + tab_ptr->TableSizeLen);
		
		err = memcmp((void*)(buf + tab_ptr->StartAddrLen + tab_ptr->TableSizeLen),(void*)&crc,sizeof(UINT16_T));
		if(err != 0x00)
		{
			local_free(buf);
			return ERR_CRC;
		}
	}

	//загружаем в структуру
	bl->body.pxNextFreeBlock = 0;
	memcpy((void*)&bl->body.pxNextFreeBlock, (void*)buf, tab_ptr->StartAddrLen);
	bl->body.xBlockSize = 0;
	memcpy((void*)&bl->body.xBlockSize, (void*)(buf + tab_ptr->StartAddrLen), tab_ptr->TableSizeLen);

	return ERR_OK;
}

/*-----------------------------------------------------------*/
UINT8_T	table_Malloc(TableInfo *tab_ptr, UINT32_T *addr, UINT32_T xWantedSize)
{
	BlockLink pxBlock, pxNewBlockLink, pxPreviousBlock, xStart;
	UINT8_T err=ERR_OK;

	xStart.pxCurrentAddr = 0;
	xStart.body.pxNextFreeBlock = 0;
	xStart.body.xBlockSize = 0;

	pxBlock.pxCurrentAddr = 0;
	pxBlock.body.pxNextFreeBlock = 0;
	pxBlock.body.xBlockSize = 0;

	pxNewBlockLink.pxCurrentAddr = 0;
	pxNewBlockLink.body.pxNextFreeBlock = 0;
	pxNewBlockLink.body.xBlockSize = 0;

	pxPreviousBlock.pxCurrentAddr = 0;
	pxPreviousBlock.body.pxNextFreeBlock = 0;
	pxPreviousBlock.body.xBlockSize = 0;

	//добавить проверку инициализированна куча или нет

	/* The wanted size is increased so it can contain a BlockLink_t
	structure in addition to the requested amount of bytes. */
	if(xWantedSize == 0)
	{
		err = ERR_WRONG_SIZE;
		return err;
	}

	xWantedSize += tab_ptr->bl_size;

	/* Ensure that blocks are always aligned to the required number of bytes. */
	if((xWantedSize & (tab_ptr->ByteAligment-1)) != 0x00)
	{
		/* Byte alignment required. */
		xWantedSize = memory_aligment(tab_ptr->ByteAligment,xWantedSize);
	}

	if(xWantedSize > tab_ptr->FreeBytesRemaining)
	{
		err = ERR_NO_FREE_SPACE;
		return err;
	}

	/* Traverse the list from the start	(lowest address) block until
	one	of adequate size is found. */
	xStart.pxCurrentAddr = tab_ptr->StartAddr;
	err = ReadBlockLink(tab_ptr, &xStart);

	if (err != ERR_OK)
		return err;

	pxPreviousBlock = xStart;
	//pxPreviousBlock.body.pxNextFreeBlock = tab_ptr->HeadAddr;
	pxBlock.pxCurrentAddr = xStart.body.pxNextFreeBlock;
	err = ReadBlockLink(tab_ptr, &pxBlock);

	if(err != ERR_OK)
		return err;

	while((pxBlock.body.xBlockSize < xWantedSize) && (pxBlock.body.pxNextFreeBlock != 0))
	{
		pxPreviousBlock = pxBlock;

		pxBlock.pxCurrentAddr = pxBlock.body.pxNextFreeBlock;
		err = ReadBlockLink(tab_ptr, &pxBlock);

		if(err != ERR_OK)
			return err;
	}

	/* If the end marker was reached then a block of adequate size
	was	not found. */
	if(pxBlock.pxCurrentAddr != tab_ptr->EndAddr)
	{
		/* Return the memory space pointed to - jumping over the
		BlockLink_t structure at its start. */
		*addr=pxPreviousBlock.body.pxNextFreeBlock + tab_ptr->bl_size;

		/* This block is being returned for use so must be taken out
		of the list of free blocks. */
		if(pxPreviousBlock.pxCurrentAddr != pxBlock.pxCurrentAddr)
		{
			pxPreviousBlock.body.pxNextFreeBlock = pxBlock.body.pxNextFreeBlock;
			
			err = WriteBlockLink(tab_ptr, &pxPreviousBlock);
			if(err != ERR_OK)
				return err;

			//tab_ptr->HeadAddr = pxBlock.body.pxNextFreeBlock; //pxPreviousBlock.body.pxNextFreeBlock;
		}

		/* If the block is larger than required it can be split into
		two. */
		if( (pxBlock.body.xBlockSize - xWantedSize) > (UINT32_T)(tab_ptr->bl_size<<1) )
		{
			/* This block is to be split into two.  Create a new
			block following the number of bytes requested. The void
			cast is used to prevent byte alignment warnings from the
			compiler. */
			pxNewBlockLink.pxCurrentAddr = pxBlock.pxCurrentAddr + xWantedSize;

			/* Calculate the sizes of two blocks split from the
			single block. */
			pxNewBlockLink.body.xBlockSize = pxBlock.body.xBlockSize - xWantedSize;
			pxNewBlockLink.body.pxNextFreeBlock = 0;

			pxBlock.body.xBlockSize = xWantedSize;

			/* Insert the new block into the list of free blocks. */
			err = prvInsertBlockIntoFreeList(tab_ptr, &pxNewBlockLink);

			if (err != ERR_OK)
				return err;

			#if (configUSE_SegmentCounter==TRUE)
			tab_ptr->xSegmentCounter++;
			#endif
		}

		tab_ptr->FreeBytesRemaining -= pxBlock.body.xBlockSize;

		/* The block is being returned - it is allocated and owned
		by the application and has no "next" block. */
		pxBlock.body.xBlockSize |= (UINT32_T)(0x01 << ((8 * tab_ptr->TableSizeLen) - 1));
		pxBlock.body.pxNextFreeBlock = 0;
		err = WriteBlockLink(tab_ptr, &pxBlock);
		if (err != ERR_OK)
			return err;
	}

	return err;
}

//UINT8_T table_GetAddr(TableInfo* tab_ptr, UINT32_T* addr)
//{
//	BlockLink pxIterator;
//	UINT8_T err = ERR_OK;
//
//	pxIterator.pxCurrentAddr = 0;
//	pxIterator.body.pxNextFreeBlock = 0;
//	pxIterator.body.xBlockSize = 0;
//
//	pxIterator.pxCurrentAddr = *addr;
//	err = ReadBlockLink(tab_ptr, &pxIterator);
//	if (err != ERR_OK)
//		return err;
//	
//	*addr = pxIterator.body.pxNextFreeBlock;
//
//	return err;
//}


/*-----------------------------------------------------------*/
UINT8_T prvInsertBlockIntoFreeList(TableInfo *tab_ptr, BlockLink *pxBlockToInsert)
{
	BlockLink pxIterator, pxBlockToInsertBuf;
	UINT8_T err=ERR_OK;

	pxIterator.pxCurrentAddr = 0;
	pxIterator.body.pxNextFreeBlock = 0;
	pxIterator.body.xBlockSize = 0;

	pxBlockToInsertBuf.pxCurrentAddr = 0;
	pxBlockToInsertBuf.body.pxNextFreeBlock = 0;
	pxBlockToInsertBuf.body.xBlockSize = 0;

	//чтение сектора xStart
	pxIterator.pxCurrentAddr = tab_ptr->StartAddr;
	err = ReadBlockLink(tab_ptr, &pxIterator);
	if(err != ERR_OK)
		return err;
	//pxIterator.body.pxNextFreeBlock = tab_ptr->HeadAddr;

	/* Iterate through the list until a block is found that has a higher address
	than the block being inserted. */
	while(pxIterator.body.pxNextFreeBlock < pxBlockToInsert->pxCurrentAddr)
	{
		pxIterator.pxCurrentAddr = pxIterator.body.pxNextFreeBlock;
		err = ReadBlockLink(tab_ptr,&pxIterator);
		if(err != ERR_OK)
			return err;
	}

	/* Do the block being inserted, and the block it is being inserted after
	make a contiguous block of memory? */
	if( (pxIterator.pxCurrentAddr + pxIterator.body.xBlockSize ) == pxBlockToInsert->pxCurrentAddr )
	{
		pxIterator.body.xBlockSize += pxBlockToInsert->body.xBlockSize;
		*pxBlockToInsert = pxIterator;

		#if (configUSE_SegmentCounter==TRUE)
		tab_ptr->xSegmentCounter--;
		#endif
	}

	/* Do the block being inserted, and the block it is being inserted before
	make a contiguous block of memory? */
	if((pxBlockToInsert->pxCurrentAddr + pxBlockToInsert->body.xBlockSize) == pxIterator.body.pxNextFreeBlock)
	{
		if(pxIterator.body.pxNextFreeBlock != tab_ptr->EndAddr)
		{
			/* Form one big block from the two blocks. */
			pxBlockToInsertBuf.pxCurrentAddr = pxIterator.body.pxNextFreeBlock;
			err = ReadBlockLink(tab_ptr,&pxBlockToInsertBuf);
			if(err != ERR_OK)
				return err;

			pxBlockToInsert->body.xBlockSize = pxBlockToInsertBuf.body.xBlockSize;
			pxBlockToInsert->body.pxNextFreeBlock = pxBlockToInsertBuf.body.pxNextFreeBlock;

			#if (configUSE_SegmentCounter==TRUE)
			tab_ptr->xSegmentCounter--;
			#endif
		}
		else
		{
			pxBlockToInsert->body.pxNextFreeBlock = tab_ptr->EndAddr;
		}
	}
	else
	{
		pxBlockToInsert->body.pxNextFreeBlock = pxIterator.body.pxNextFreeBlock;
	}

	/* If the block being inserted plugged a gab, so was merged with the block
	before and the block after, then it's pxNextFreeBlock pointer will have
	already been set, and should not be set here as that would make it point
	to itself. */
	if( pxIterator.pxCurrentAddr != pxBlockToInsert->pxCurrentAddr )
	{
		pxIterator.body.pxNextFreeBlock = pxBlockToInsert->pxCurrentAddr;
		err = WriteBlockLink(tab_ptr, &pxIterator);
		if (err != ERR_OK)
			return err;

		//tab_ptr->HeadAddr = pxBlockToInsert->pxCurrentAddr; //pxIterator.body.pxNextFreeBlock;
	}

	err = WriteBlockLink(tab_ptr,pxBlockToInsert);
	return err;
}


/*-----------------------------------------------------------*/
UINT8_T	table_Free(TableInfo* tab_ptr, UINT32_T pv )
{
	UINT32_T puc = pv;
	BlockLink pxLink;
	UINT8_T err = ERR_OK;

	pxLink.pxCurrentAddr = 0;
	pxLink.body.pxNextFreeBlock = 0;
	pxLink.body.xBlockSize = 0;

	if( pv != 0 )
	{
		/* The memory being freed will have an BlockLink_t structure immediately
		before it. */
		puc -= tab_ptr->bl_size;

		/* This casting is to keep the compiler from issuing warnings. */
		pxLink.pxCurrentAddr = puc;
		err = ReadBlockLink(tab_ptr, &pxLink);
		if(err != ERR_OK)
			return err;

		if( ( pxLink.body.xBlockSize & (UINT32_T)(0x01 << ((8 * tab_ptr->TableSizeLen)-1)) ) != 0 )								//!!!!!!!!!!!!!!
		{
			if( pxLink.body.pxNextFreeBlock == 0 )
			{
				/* The block is being returned to the heap - it is no longer allocated. */
				pxLink.body.xBlockSize &= ~(UINT32_T)(0x01 << ((8 * tab_ptr->TableSizeLen)-1));

				/* Add this block to the list of free blocks. */
				tab_ptr->FreeBytesRemaining += pxLink.body.xBlockSize;
				err = prvInsertBlockIntoFreeList(tab_ptr, &pxLink);
			}
		}
	}

	return err;
}

UINT8_T table_GetAddrLen(TableInfo* tab_ptr)
{
	return tab_ptr->StartAddrLen;
}

UINT8_T	table_GetSizeLen(TableInfo* tab_ptr)
{
	return tab_ptr->TableSizeLen;
}

UINT8_T	table_GetSegmentSize(TableInfo *tab_ptr, UINT32_T addr, UINT32_T *size)
{
	BlockLink pxBlock;
	UINT8_T err=ERR_OK;

	pxBlock.pxCurrentAddr = 0;
	pxBlock.body.pxNextFreeBlock = 0;
	pxBlock.body.xBlockSize = 0;

	pxBlock.pxCurrentAddr = addr - tab_ptr->bl_size;
	err = ReadBlockLink(tab_ptr, &pxBlock);

	if(err==ERR_OK)
		*size = (pxBlock.body.xBlockSize & ~(UINT32_T)(0x01 << ((8 * tab_ptr->TableSizeLen) - 1))) - tab_ptr->bl_size;
	
	return err;
}

UINT32_T table_GetStartAdd(TableInfo* tab_ptr)
{
	return tab_ptr->StartAddr;
}

UINT32_T table_GetEndAdd(TableInfo* tab_ptr)
{
	return tab_ptr->EndAddr + tab_ptr->bl_size;
}

UINT8_T table_Flash(TableInfo* tab_ptr)
{
	BlockLink xStart;
	UINT8_T err = ERR_OK;

	xStart.pxCurrentAddr = tab_ptr->StartAddr;
	//xStart.body.pxNextFreeBlock = tab_ptr->HeadAddr;
	xStart.body.xBlockSize = 0;

	err = WriteBlockLink(tab_ptr, &xStart);

	return err;
}

//UINT8_T sector_read(UINT8_T index, UINT32_T addr, void *data, UINT16_T size)
//{
//	UINT16_T crc;
//	UINT8_T err=ERR_OK;
//
//	err=local_read(index,addr,data,size);
//
//	//чтение с проверкой CRC
//	if(err==ERR_OK)
//	{
//		if((sl->sector[index].Type & SECTOR_CRC)>0)
//		{
//			Crc16_Clear();
//			crc=Crc16((UINT8_T*)data,size-sizeof(UINT16_T));
//
//			err=memcmp((void*)((UINT8_T*)data+size-sizeof(UINT16_T)),(void*)&crc,sizeof(UINT16_T));
//			if(err!=0x00)
//			{
//				err=ERR_CRC;
//			}
//		}
//	}
//
//	return err;
//}
//
//UINT8_T sector_write(UINT8_T index, UINT32_T addr, void *data, UINT16_T size)
//{
//	UINT16_T crc;
//
//	if((sl->sector[index].Type & SECTOR_CRC)>0)
//	{
//		Crc16_Clear();
//		crc=Crc16((UINT8_T*)data, size-sizeof(UINT16_T));
//		memcpy((void*)((UINT8_T*)data+size-sizeof(UINT16_T)),(void*)&crc,sizeof(UINT16_T));
//	}
//
//	//запись с генерированием CRC
//	return local_write(index,addr,data,size);
//}