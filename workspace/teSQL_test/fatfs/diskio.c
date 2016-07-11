/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"		/* FatFs lower layer API */
//#include "usbdisk.h"	/* Example: Header file of existing USB MSD control module */
//#include "atadrive.h"	/* Example: Header file of existing ATA harddisk control module */
//#include "sdcard.h"		/* Example: Header file of existing MMC/SDC contorl module */
#include <stm32f4xx.h>
#include "stm32f4_sdio_sd.h"

/* Definitions of physical drive number for each drive */
#define ATA		0	/* Example: Map ATA harddisk to physical drive 0 */
#define MMC		1	/* Example: Map MMC/SD card to physical drive 1 */
#define USB		2	/* Example: Map USB MSD to physical drive 2 */


/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	if(pdrv)
		return STA_NOINIT;		/* Supports only single drive */
	return SD_OK;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{

	NVIC_InitTypeDef NVIC_InitStructure;
	SD_Error res = SD_OK;

	/* Configure the NVIC Preemption Priority Bits */
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);

	// SDIO Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = SDIO_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	// DMA2 STREAMx Interrupt ENABLE
	NVIC_InitStructure.NVIC_IRQChannel = SD_SDIO_DMA_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	res = SD_Init();

	if(res == SD_OK)
		res = SD_OK;
	else
		return STA_NOINIT;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{
	SD_Error Status;

	if(count==1)
		Status = SD_ReadBlock(buff ,sector<< 9 , 512);//SDCardInfo.CardBlockSize );
	else
		Status = SD_ReadMultiBlocks(buff ,sector<< 9 , 512 ,count);//SDCardInfo.CardBlockSize,count);

	/* Check if the Transfer is finished */
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);

	if(Status == SD_OK)
		return RES_OK;
	else
		return RES_ERROR;

	return RES_PARERR;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	SD_Error Status;

	if(count==1)
		Status = SD_WriteBlock((u8 *)buff ,sector << 9 , 512);
	else
		Status = SD_WriteMultiBlocks((u8 *)buff ,sector << 9 , 512, count);

	/* Check if the Transfer is finished */
	Status = SD_WaitReadOperation();
	while(SD_GetStatus() != SD_TRANSFER_OK);

	if(Status == SD_OK)
		return RES_OK;
	else
		return RES_ERROR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	SD_CardInfo SDCardInfo;
	__IO SD_Error errorstatus = SD_OK;

	errorstatus = SD_GetCardInfo(&SDCardInfo);

	if (errorstatus != SD_OK)
	{
		return RES_PARERR;
	}

	switch(cmd) {
	  case CTRL_SYNC:
			return RES_OK;
	  case GET_SECTOR_COUNT:
	    *(DWORD*)buff = SDCardInfo.CardCapacity / SDCardInfo.CardBlockSize;
	    return RES_OK;
	  case GET_SECTOR_SIZE:		// Get R/W sector size (WORD)
	    *(WORD*)buff = SDCardInfo.CardBlockSize;
	    return RES_OK;
	  case GET_BLOCK_SIZE:
	    *(WORD*)buff = SDCardInfo.CardBlockSize;
	    return RES_OK;
	  case CTRL_POWER:
			return RES_OK;
	  case CTRL_LOCK:
			return RES_OK;
	  case CTRL_EJECT:
			return RES_OK;
      /* MMC/SDC command */
	  case MMC_GET_TYPE:
			return RES_OK;
	  case MMC_GET_CSD:
			return RES_OK;
	  case MMC_GET_CID:
			return RES_OK;
	  case MMC_GET_OCR:
			return RES_OK;
	  case MMC_GET_SDSTAT:
			return RES_OK;
	}

	return RES_PARERR;
}
#endif


/*-----------------------------------------------------------------------*/
/* Get current time                                                      */
/*-----------------------------------------------------------------------*/

//DWORD get_fattime()
//{
//	return	((2006UL-1980) << 25)	// Year = 2006
//			| (2UL << 21)			// Month = Feb
//			| (9UL << 16)			// Day = 9
//			| (22U << 11)			// Hour = 22
//			| (30U << 5)			// Min = 30
//			| (0U >> 1)				// Sec = 0
//			;
//}
