#include "StdAfx.h"
#include "BitAndData.h"

BitAndByte::BitAndByte(Byte data, bool bit)
{
	_data = data;

	if (bit)
		SetBit();
	else
		ClearBit();
}

PxBitAndByte BitAndByte::ToUnmanaged(BitAndByte b)
{
	BYTE data = b.GetData();
	bool bit = b.IsBitSet();

	return PxBitAndByte(data, bit);
}