#ifndef SQL_PORTABLE
#define SQL_PORTABLE

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