#include "StdAfx.h"

#include <NxStream.h> 

#include "User Memory Writer Stream.h"

using namespace StillDesign::PhysX;

UserMemoryWriterStream::UserMemoryWriterStream() : currentSize(0), maxSize(0), data(NULL)
{
	
}

UserMemoryWriterStream::~UserMemoryWriterStream()
{
	NX_DELETE_ARRAY(data);
}

void UserMemoryWriterStream::clear()
{
	currentSize = 0;
}

NxStream& UserMemoryWriterStream::storeByte(NxU8 b)
{
	return storeBuffer(&b, sizeof(NxU8));
}
NxStream& UserMemoryWriterStream::storeWord(NxU16 w)
{
	return storeBuffer(&w, sizeof(NxU16));
}
NxStream& UserMemoryWriterStream::storeDword(NxU32 d)
{
	return storeBuffer(&d, sizeof(NxU32));
}
NxStream& UserMemoryWriterStream::storeFloat(NxReal f)
{
	return storeBuffer(&f, sizeof(NxReal));
}
NxStream& UserMemoryWriterStream::storeDouble(NxF64 f)
{
	return storeBuffer(&f, sizeof(NxF64));
}
NxStream& UserMemoryWriterStream::storeBuffer(const void* buffer, NxU32 size)
{
	NxU32 expectedSize = currentSize + size;
	if(expectedSize > maxSize)
	{
		maxSize = expectedSize + 4096;

		NxU8* newData = new NxU8[maxSize];
		NX_ASSERT(newData!=NULL);

		if(data)
		{
			memcpy(newData, data, currentSize);
			delete[] data;
		}
		data = newData;
	}
	memcpy(data+currentSize, buffer, size);
	currentSize += size;
	return *this;
}