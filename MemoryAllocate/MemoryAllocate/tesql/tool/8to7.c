#include "8to7.h"

UINT32_T SevenToEight(UINT8_T* in, UINT8_T* out, UINT32_T len)
{
	UINT32_T n, m;
	UINT8_T c, w;
	UINT8_T shift;
	shift = 1;
	m = 0;
	/* Decode into 7 bit characters */
	for (n = 0; n < (len - 1); ++n)
	{
		c = in[n] & 0x7f;
		c <<= shift;

		w = in[n + 1] & 0x7f;
		w >>= (7 - shift);

		shift += 1;
		c = c | w;
		
		if (shift > 7)
		{
			shift = 1;
			n++;
		}
		out[m] = c;
		m++;

	}

	for (UINT32_T i = m; i < len; i++)
		out[i] = 0;

	return m;
}

UINT32_T EightToSeven(UINT8_T* in, UINT8_T* out, UINT32_T len, UINT8_T msb_bit)
{
	UINT32_T bit_len = len * 8;
	UINT32_T index, index_out, bit;
	UINT8_T	shift;

	index_out = 0;
	for (UINT32_T i = 0; i < bit_len && index_out < len;)
	{
		if (msb_bit == 1)
			shift = 0x80;
		else
			shift = 0;

		for (int j = 6; j >= 0; j--)
		{
			index = i / 8;
			bit = 7 - i % 8;

			if ((in[index] & (0x01 << bit)) != 0)
				shift |= (0x01 << j);

			i++;
		}
		out[index_out] = shift;
		index_out++;
	}

	return index_out;
}