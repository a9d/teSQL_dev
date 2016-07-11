#include "crc.h"


static UINT16_T crc = 0xFFFF;

///*
//  Name  : CRC-8
//  Poly  : 0x31    x^8 + x^5 + x^4 + 1
//  Init  : 0xFF
//  Revert: false
//  XorOut: 0x00
//  Check : 0xF7 ("123456789")
//  MaxLen: 15 байт(127 бит) - обнаружение
//    одинарных, двойных, тройных и всех нечетных ошибок
//*/
//UINT8_T Crc8(UINT8_T *pcBlock, UINT8_T len)
//{
//    UINT8_T crc = 0xFF;
//    UINT16_T i;
//
//    while (len--)
//    {
//        crc ^= *pcBlock++;
//
//        for (i = 0; i < 8; i++)
//            crc = crc & 0x80 ? (crc << 1) ^ 0x31 : crc << 1;
//    }
//
//    return crc;
//}

/*
  Name  : CRC-16 CCITT
  Poly  : 0x1021    x^16 + x^12 + x^5 + 1
  Init  : 0xFFFF
  Revert: false
  XorOut: 0x0000
  Check : 0x29B1 ("123456789")
  MaxLen: 4095 байт (32767 бит) - обнаружение
    одинарных, двойных, тройных и всех нечетных ошибок
*/
UINT16_T Crc16(UINT8_T *pcBlock, UINT16_T len)
{
    //UINT16_T crc = 0xFFFF;
    UINT8_T i;
	UINT16_T j=0;

    while (len--)
    {
        crc ^= *(pcBlock+j) << 8;
		j++;
        for (i = 0; i < 8; i++)
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
    }
    return crc;
}

void Crc16_Clear()
{
	crc = 0xFFFF;
}

UINT16_T Crc16_Get()
{
	return crc;
}