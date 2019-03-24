#include "StdAfx.h"
#include "DefaultMemoryOutputStream.h"
#include "Foundation.h"

DefaultMemoryOutputStream::DefaultMemoryOutputStream()
{
	_defaultMemoryOutputStream = new PxDefaultMemoryOutputStream();
}
DefaultMemoryOutputStream::DefaultMemoryOutputStream(array<Byte>^ buffer)
{
	if (!Foundation::Initalized)
		throw gcnew InvalidOperationException("Foundation must be initalized first");

	_defaultMemoryOutputStream = new PxDefaultMemoryOutputStream();

	Write(buffer);
}
DefaultMemoryOutputStream::~DefaultMemoryOutputStream()
{
	this->!DefaultMemoryOutputStream();
}
DefaultMemoryOutputStream::!DefaultMemoryOutputStream()
{
	SAFE_DELETE(_defaultMemoryOutputStream);
}

int DefaultMemoryOutputStream::Write(array<Byte>^ buffer)
{
	ThrowIfNull(buffer, "buffer");
	if (buffer->Length == 0)
		return 0;

	pin_ptr<Byte> p = &buffer[0];

	int size = sizeof(Byte) * buffer->Length;

	void* b = malloc(size);
	memcpy(b, p, size);

	int written = _defaultMemoryOutputStream->write(b, size);

	return written;
}

array<Byte>^ DefaultMemoryOutputStream::GetData()
{
	PxU8* data = _defaultMemoryOutputStream->getData();
	int length = _defaultMemoryOutputStream->getSize();
	int size = sizeof(Byte) * length;

	auto buffer = gcnew array<Byte>(size);
	
	if (size == 0)
		return buffer;

	pin_ptr<Byte> d = &buffer[0];

	memcpy(d, data, size);

	return buffer;
}

int DefaultMemoryOutputStream::Size::get()
{
	return _defaultMemoryOutputStream->getSize();
}