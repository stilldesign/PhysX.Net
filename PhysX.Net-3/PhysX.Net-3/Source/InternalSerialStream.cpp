#include "StdAfx.h"
#include "InternalSerialStream.h"
#include "MemoryStream.h"

InternalSerialStream::InternalSerialStream()
{
	_memoryStream = new MemoryStream();
}
InternalSerialStream::~InternalSerialStream()
{
	SAFE_DELETE(_memoryStream);
}

void InternalSerialStream::storeBuffer(const void *buffer, PxU32 size)
{
	_memoryStream->storeBuffer(buffer, size);
}
PxU32 InternalSerialStream::getTotalStoredSize()
{
	return _memoryStream->getMemorySize();
}

InternalMemoryStream* InternalSerialStream::GetMemoryStream()
{
	return _memoryStream;
}