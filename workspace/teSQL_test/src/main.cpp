//******************************************************************************
//*
//*     FULLNAME:  Single-Chip Microcontroller Real-Time Operating System
//*
//*     NICKNAME:  scmRTOS
//*
//*     PROCESSOR: ARM Cortex-M4F
//*
//*     TOOLKIT:   ARM GCC
//*
//*     PURPOSE:   Port Test File
//*
//*     Version: v5.1.0
//*
//*
//*     Copyright (c) 2003-2016, scmRTOS Team
//*
//*     Permission is hereby granted, free of charge, to any person 
//*     obtaining  a copy of this software and associated documentation 
//*     files (the "Software"), to deal in the Software without restriction, 
//*     including without limitation the rights to use, copy, modify, merge, 
//*     publish, distribute, sublicense, and/or sell copies of the Software, 
//*     and to permit persons to whom the Software is furnished to do so, 
//*     subject to the following conditions:
//*
//*     The above copyright notice and this permission notice shall be included 
//*     in all copies or substantial portions of the Software.
//*
//*     THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 
//*     EXPRESS  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF 
//*     MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
//*     IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY 
//*     CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, 
//*     TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH 
//*     THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
//*
//*     =================================================================
//*     Project sources: https://github.com/scmrtos/scmrtos
//*     Documentation:   https://github.com/scmrtos/scmrtos/wiki/Documentation
//*     Wiki:            https://github.com/scmrtos/scmrtos/wiki
//*     Sample projects: https://github.com/scmrtos/scmrtos-sample-projects
//*     =================================================================
//*
//******************************************************************************
//*     gcc port by Anton B. Gusev aka AHTOXA, Copyright (c) 2009-2016

#include <scmRTOS.h>
#include <stm32f4xx.h>
#include "stm32f4_sdio_sd.h"
#include "ff.h"

#include "heap.h"
#include "sql_db_config.h"

#include "heap_4.h"

//---------------------------------------------------------------------------
//
//      Process types
//
typedef OS::process<OS::pr0, 1500> TProc1;
typedef OS::process<OS::pr1, 700> TProc2;
typedef OS::process<OS::pr2, 1000> TProc3;
typedef OS::process<OS::pr3, 700> TProc4;
//---------------------------------------------------------------------------
//
//      Process objects
//
TProc1 Proc1;
TProc2 Proc2;
TProc3 Proc3;
TProc4 Proc4;

//
//typedef Pin<'D', 15> BlueLED;
//typedef Pin<'D', 14> RedLED;
//typedef Pin<'D', 12> GreenLED;
//typedef Pin<'D', 13> OrangeLED;

#define RED_LED		GPIO_Pin_14
#define BLUE_LED	GPIO_Pin_15
#define GREEN_LED	GPIO_Pin_12
#define ORANGE_LED	GPIO_Pin_13

#define RED_ON()		GPIO_SetBits(GPIOD,RED_LED)
#define RED_OFF()		GPIO_ResetBits(GPIOD,RED_LED)

#define BLUE_ON()		GPIO_SetBits(GPIOD,BLUE_LED)
#define BLUE_OFF()		GPIO_ResetBits(GPIOD,BLUE_LED)

#define GREEN_ON()		GPIO_SetBits(GPIOD,GREEN_LED)
#define GREEN_OFF()		GPIO_ResetBits(GPIOD,GREEN_LED)

#define ORANGE_ON()		GPIO_SetBits(GPIOD,ORANGE_LED)
#define ORANGE_OFF()	GPIO_ResetBits(GPIOD,ORANGE_LED)


//======================================================= teSQL ============================================
FATFS FatFs;
FIL fil;       /* File object */

extern "C" void ApplicationSectorPrepareHook(void)
{
	FRESULT fr;    /* FatFs return code */

	/* Register work area to the default drive */
	f_mount(&FatFs, "", 0);

	fr = f_open(&fil, "tesql.db", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
	if (fr)
	{

	}
}

extern "C" void ApplicationSectorOpenHook(UINT8_T index, UINT32_T start_addr,UINT32_T size)
{
	//подготовка сектора
}

extern "C" void ApplicationSectorDelete(UINT8_T index, UINT32_T start_addr, UINT32_T size)
{
	//удаление заданного сектора
}


extern "C" void fat_write(UINT32_T addr, void *data, UINT16_T size)
{
	UINT bw;
	FRESULT fr;

	fr=f_lseek(&fil,addr);
	fr=f_write(&fil, data, size, &bw);
}

extern "C" void fat_read(UINT32_T addr, void *data, UINT16_T size)
{
	UINT br;
	FRESULT fr;

	fr=f_lseek(&fil,addr);
	fr=f_read(&fil, data, size, &br);  /* Read a chunk of source file */
}

//======================================================= FatFs ============================================

OS::TMutex MutexFatFs;

extern "C" void FatLock()
{
	MutexFatFs.lock();
}

extern "C" void FatUnlock()
{
	MutexFatFs.unlock();
}


//======================================================= heap ============================================
OS::TMutex MutexHeap;

extern "C" void vTaskSuspendAll()
{
	MutexHeap.lock();
}

extern "C" void xTaskResumeAll()
{
	MutexHeap.unlock();
}

extern "C" void vApplicationMallocFailedHook()
{

}

//==============================================================================================================

void LED_Configuration()
{
	GPIO_InitTypeDef GPIO_InitStructure;

	/* GPIOG Peripheral clock enable */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	/* Configure PG6 and PG8 in output pushpull mode */
	GPIO_InitStructure.GPIO_Pin = RED_LED | BLUE_LED | GREEN_LED | ORANGE_LED;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure);
}

int main()
{
	LED_Configuration();

    // run
    OS::run();
}

namespace OS
{
    template <>
    OS_PROCESS void TProc1::exec()
    {
    	SectorConfig config;
    	UINT32_T addr1,addr2,addr3,addr4,addr5;
    	UINT8_T buf[]={1,2,3,4,5,6};

    	sector_Create(1,2);

    	config.index=0;
		config.type=(SECTOR_MAIN|SECTOR_START|SECTOR_CRC|SECTOR_FLASH);
		config.ByteAligment=2;
		config.StartAddr=0;
		config.StartAddrLen=BYTES_2;
		config.SectorSize=2000;
		config.SectorSizeLen=BYTES_2;
		sector_ConfigCheck(&config);
		sector_Insert(&config);

		sector_Malloc(0,&addr1,6);
		sector_write(0,addr1,(void*)buf,6);

		sector_Malloc(0,&addr2,6);
		sector_write(0,addr2,(void*)buf,6);

		sector_Malloc(0,&addr3,6);
		sector_write(0,addr3,(void*)buf,6);

		sector_Malloc(0,&addr4,6);
		sector_write(0,addr4,(void*)buf,6);

		sector_Malloc(0,&addr5,6);
		sector_write(0,addr5,(void*)buf,6);

		sector_Free(0,addr1);
		sector_Free(0,addr3);
		sector_Free(0,addr2);
		sector_Free(0,addr4);
		sector_Free(0,addr5);

		sector_Close();
		f_close(&fil);


		sector_Open(0, 2 ,0);

		sector_Malloc(0,&addr1,6);
		sector_write(0,addr1,(void*)buf,6);

		sector_Close();
		f_close(&fil);

//        FIL fil;       /* File object */
//        char line[10]={'t','e','s','t',0,0,0,0,0,0}; /* Line buffer */
//        FRESULT fr;    /* FatFs return code */
//        UINT br, bw;         /* File read/write count */
//
//        /* Register work area to the default drive */
//        f_mount(&FatFs, "", 0);
//
//        /* Open a text file */
//        fr = f_open(&fil, "message.txt", FA_READ | FA_WRITE | FA_OPEN_ALWAYS);
//        if (fr)
//		{
//        	//error
//        	//return (int)fr;
//		}
//
//        br=10;
//        fr = f_write(&fil, line, br, &bw);
//        if (fr || bw < br)
//        {
//        	//error
//        }
//
//        fr = f_read(&fil, line, 10, &br);  /* Read a chunk of source file */
//        if (fr || br == 0)
//        {
//        	//error;
//        }
//
//        f_close(&fil);
//        f_mount(NULL, "", 0);

		for(;;)
		{

			RED_ON();
			sleep(2);
			RED_OFF();
			sleep(2);
		}
    }

    template <>
    OS_PROCESS void TProc2::exec()
    {
    	for(;;)
    	{
    		GREEN_ON();
    		sleep(300);
    		GREEN_OFF();
    		sleep(300);
    	}
    }

    template <>
    OS_PROCESS void TProc3::exec()
    {
    	for(;;)
    	{
    		BLUE_ON();
    		sleep(400);
    		BLUE_OFF();
    		sleep(400);
    	}
    }

    template <>
    OS_PROCESS void TProc4::exec()
    {
        for(;;)
        {
    		ORANGE_ON();
    		sleep(500);
    		ORANGE_OFF();
    		sleep(500);
        }
    }
}

OS_INTERRUPT void SDIO_IRQHandler(void)
{
	OS::TISRW tisrw;
	/* Process All SDIO Interrupt Sources */
	SD_ProcessIRQSrc();
}

OS_INTERRUPT void SD_SDIO_DMA_IRQHANDLER(void)
{
	OS::TISRW tisrw;
	/* Process DMA2 Stream3 or DMA2 Stream6 Interrupt Sources */
	SD_ProcessDMAIRQ();
}


#if scmRTOS_IDLE_HOOK_ENABLE
void OS::idle_process_user_hook()
{
	__WFI();
}
#endif
