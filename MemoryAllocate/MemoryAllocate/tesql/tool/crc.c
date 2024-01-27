#include "crc.h"

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
UINT16_T Crc16(UINT16_T crc, UINT8_T *pcBlock, UINT16_T len)
{
    UINT16_T crc16 = crc;
    UINT8_T i;
	UINT16_T j=0;

    while (len--)
    {
        crc16 ^= *(pcBlock+j) << 8;
		j++;
        for (i = 0; i < 8; i++)
            crc16 = crc16 & 0x8000 ? (crc16 << 1) ^ 0x1021 : crc16 << 1;
    }
    return crc16;
}