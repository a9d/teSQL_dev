/*
 * heap.h
 *
 *  Created on: 11 июл. 2016 г.
 *      Author: јндрей
 */

#ifndef HEAP_4_H_
#define HEAP_4_H_

#ifdef  __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>

void vTaskSuspendAll();
void xTaskResumeAll();
void vApplicationMallocFailedHook( void );

void *pvPortMalloc( size_t xWantedSize );
void vPortFree( void *pv );
size_t xPortGetFreeHeapSize( void );
size_t xPortGetMinimumEverFreeHeapSize( void );
void vPortInitialiseBlocks( void );

#ifdef  __cplusplus
}
#endif

#endif /* HEAP_4_H_ */
