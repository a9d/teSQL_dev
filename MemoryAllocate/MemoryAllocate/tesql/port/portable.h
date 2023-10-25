#ifndef _PORTABLE
#define _PORTABLE

#define SECTOR_MAIN_INDEX	0	//номер сектора в котором хранится информация о секторах

#define RAM_ALIGMENT 2	//выравнивание RAM микроконтроллера,нет

//SECTOR NAME
#define SECTOR_RAM_0 0
#define SECTOR_RAM_1 1

//TYPEDEF
typedef unsigned __int8		UINT8_T;
typedef unsigned __int16    UINT16_T;
typedef unsigned __int32	UINT32_T;
typedef	unsigned char		UCHAR;
typedef char				CHAR;
typedef	unsigned __int32	SIZE_T;

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