#include "StdAfx.h"

#include "User Memory Reader Stream.h"

using namespace StillDesign::PhysX;

UserMemoryReaderStream::UserMemoryReaderStream( const NxU8* data )
{
	_startBuffer = data;
	buffer = data;
}

UserMemoryReaderStream::~UserMemoryReaderStream()
{
	//NX_DELETE_ARRAY(buffer);
}

NxU8 UserMemoryReaderStream::readByte() const
{
	NxU8 b;
	memcpy(&b, buffer, sizeof(NxU8));
	buffer += sizeof(NxU8);
	return b;
}

NxU16 UserMemoryReaderStream::readWord() const
{
	NxU16 w;
	memcpy(&w, buffer, sizeof(NxU16));
	buffer += sizeof(NxU16);
	return w;
}

NxU32 UserMemoryReaderStream::readDword() const
{
	NxU32 d;
	memcpy(&d, buffer, sizeof(NxU32));
	buffer += sizeof(NxU32);
	return d;
}

float UserMemoryReaderStream::readFloat() const
{
	float f;
	memcpy(&f, buffer, sizeof(float));
	buffer += sizeof(float);
	return f;
}

double UserMemoryReaderStream::readDouble() const
{
	double f;
	memcpy(&f, buffer, sizeof(double));
	buffer += sizeof(double);
	return f;
}

void UserMemoryReaderStream::readBuffer(void* dest, NxU32 size) const
{
	memcpy(dest, buffer, size);
	buffer += size;
}

const NxU8* UserMemoryReaderStream::GetStartBuffer()
{
	return _startBuffer;
}
void UserMemoryReaderStream::Reset()
{
	buffer = _startBuffer;
}