#ifndef _PORTABLE
#define _PORTABLE

#include <stdint.h>

//TYPEDEF
typedef uint8_t		UINT8_T;
typedef uint16_t   	UINT16_T;
typedef uint32_t	UINT32_T;

/* Define NULL pointer value */
#ifndef NULL
#ifdef __cplusplus
#define NULL    0
#else
#define NULL    ((void *)0)
#endif
#endif

#ifndef TRUE
#define TRUE 1
#endif 

#ifndef FALSE
#define FALSE 0
#endif

#endif
