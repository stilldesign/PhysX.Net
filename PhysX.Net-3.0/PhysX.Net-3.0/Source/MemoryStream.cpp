#include "StdAfx.h"
#include "MemoryStream.h"

MemoryStream::MemoryStream()
{
	_capacity = 0;
	_memory = _seek = new const PxU8[0];

	assert(_memory != NULL);
}
MemoryStream::MemoryStream(const PxU8* memory, int size)
{
	assert(_memory != NULL);
	assert(size >= 0);

	_capacity = size;
	_memory = _seek = memory;
}
MemoryStream::MemoryStream(long byteSize)
{
	assert(byteSize >= 0);

	_capacity = sizeof(PxU8) * byteSize;
	_memory = _seek = new const PxU8[_capacity];

	assert(_memory != NULL);
}
MemoryStream::~MemoryStream()
{
	if (_memory)
		delete[] _memory;

	_memory = _seek = NULL;
	_capacity = 0;
}

PxU8 MemoryStream::readByte() const
{
	PxU8 b;
	memcpy(&b, _seek, sizeof(PxU8));
	_seek += sizeof(PxU8);
	return b;
}
PxU16 MemoryStream::readWord() const
{
	PxU16 w;
	memcpy(&w, _seek, sizeof(PxU16));
	_seek += sizeof(PxU16);
	return w;
}
PxU32 MemoryStream::readDword() const
{
	PxU32 d;
	memcpy(&d, _seek, sizeof(PxU32));
	_seek += sizeof(PxU32);
	return d;
}
PxF32 MemoryStream::readFloat() const
{
	float f;
	memcpy(&f, _seek, sizeof(float));
	_seek += sizeof(float);
	return f;
}
PxF64 MemoryStream::readDouble() const
{
	double f;
	memcpy(&f, _seek, sizeof(double));
	_seek += sizeof(double);
	return f;
}
void MemoryStream::readBuffer(void* buffer, PxU32 size) const
{
	memcpy(buffer, _seek, size);
	_seek += size;
}

PxStream& MemoryStream::storeByte(PxU8 b)
{
	return storeBuffer(&b, sizeof(PxU8));
}
PxStream& MemoryStream::storeWord(PxU16 w)
{
	return storeBuffer(&w, sizeof(PxU16));
}
PxStream& MemoryStream::storeDword(PxU32 d)
{
	return storeBuffer(&d, sizeof(PxU32));
}
PxStream& MemoryStream::storeFloat(PxF32 f)
{
	return storeBuffer(&f, sizeof(PxF32));
}
PxStream& MemoryStream::storeDouble(PxF64 f)
{
	return storeBuffer(&f, sizeof(PxF64));
}
PxStream& MemoryStream::storeBuffer(const void* buffer, PxU32 size)
{
	size_t usedSize = getMemorySize();

	size_t expectedSize = usedSize + size;
	if(expectedSize > _capacity)
	{
		_capacity = expectedSize + 4096;

		PxU8* newData = new PxU8[_capacity];
		PX_ASSERT(newData!=NULL);

		if (_memory)
		{
			memcpy(newData, _memory, usedSize);
			delete[] _memory;
		}
		_memory = newData;
		_seek = newData + usedSize;
	}
	memcpy((void*)_seek, buffer, size);
	_seek += size;
	return *this;
}