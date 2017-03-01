#include "StdAfx.h"
#include "DefaultMemoryInputData.h"

DefaultMemoryInputData::DefaultMemoryInputData(int size)
{
	PxU8* buffer = (PxU8*)malloc(sizeof(Byte) * size);

	if (buffer == NULL)
		throw gcnew InvalidOperationException(String::Format("Failed to allocate memory for buffer of size {0} bytes", size));

	_defaultMemoryInputData = new PxDefaultMemoryInputData(buffer, size);
}

int DefaultMemoryInputData::Read(array<Byte>^ buffer, int count)
{
	pin_ptr<Byte> d = &buffer[0];

	int read = _defaultMemoryInputData->read(d, count);

	return read;
}

void DefaultMemoryInputData::Seek(int offset)
{
	_defaultMemoryInputData->seek(offset);
}

int DefaultMemoryInputData::Length::get()
{
	return _defaultMemoryInputData->getLength();
}

int DefaultMemoryInputData::Offset::get()
{
	return _defaultMemoryInputData->tell();
}