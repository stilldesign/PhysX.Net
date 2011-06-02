#include "StdAfx.h"
#include "Util.h"
#include "MemoryStream.h"

using namespace PhysX;

generic<typename T>
T Util::CloneFloatStruct(int numOfFloats, void* p_unmanaged)
{
	int size = numOfFloats * sizeof(float);

#if DEBUG
	if (sizeof(T) != size)
		throw gcnew ArgumentException(String::Format("T must be of size {0}*float", numOfFloats));
#endif

	T managed = T();

	pin_ptr<T> p_managed = &managed;

	memcpy_s(p_managed, size, p_unmanaged, size);

	return managed;
}

generic<typename T>
array<T>^ Util::AsManagedArray(const void* memory, int count)
{
	return AsManagedArray<T>((void*)memory, count);
}
generic<typename T>
array<T>^ Util::AsManagedArray(void* memory, int count)
{
	if (memory == NULL)
		throw gcnew ArgumentNullException("memory");

	if (count < 0)
		count = 0;

	array<T>^ arr = gcnew array<T>(count);

	pin_ptr<T> arrPin = &arr[0];

	memcpy_s(arrPin, count*sizeof(T), memory, count*sizeof(T));

	return arr;
}

generic<typename T>
void Util::AsUnmanagedArray(array<T>^ arr, void* dest)
{
	AsUnmanagedArray(arr, dest, -1);
}
generic<typename T>
void Util::AsUnmanagedArray(array<T>^ arr, void* dest, int requiredCount)
{
	if (arr == nullptr)
		throw gcnew ArgumentNullException("arr");
	if (requiredCount != -1 && arr->Length != requiredCount)
		throw gcnew ArgumentException(String::Format("Array argument is not of the required length {0}", requiredCount));

	pin_ptr<T> arrPin = &arr[0];

	memcpy_s(dest, arr->Length * sizeof(T), arrPin, arr->Length * sizeof(T));
}

String^ Util::ToManagedString(const char* string)
{
	return Marshal::PtrToStringAnsi((IntPtr)(char*)string);
}
char* Util::ToUnmanagedString(String^ string)
{
	return (char*)Marshal::StringToHGlobalAnsi(string).ToPointer();
}

generic<typename T> where T : value class
PrimitiveTypeSize Util::Is16Or32Bit()
{
	return Is16Or32Bit(T::typeid);
}
PrimitiveTypeSize Util::Is16Or32Bit(Type^ type)
{
	ThrowIfNull(type, "type");

	if (type == short::typeid || type == unsigned short::typeid)
		return PrimitiveTypeSize::Bit16;
	else if (type == int::typeid || type == unsigned int::typeid)
		return PrimitiveTypeSize::Bit32;
	else
		return (PrimitiveTypeSize)0;
}

MemoryStream* Util::StreamToUnmanagedMemoryStream(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanRead)
		throw gcnew ArgumentException("Cannot read from stream");
	if (stream->Length > 0xFFFFFFFF) // Max 32 bit (somewhat arbitary, but nothing will ever allocate this much)
		throw gcnew OutOfMemoryException("Trying to allocation too much memory");

	int streamSize = (int)stream->Length;

	if (streamSize == 0)
		return new MemoryStream(0);

	const PxU8* memoryStreamPtr = (const PxU8*)malloc(streamSize * sizeof(PxU8));
	ZeroMemory((void*)memoryStreamPtr, streamSize);

	array<Byte>^ buffer = gcnew array<Byte>(streamSize);
	stream->Read(buffer, 0, streamSize);
	pin_ptr<Byte> b = &buffer[0];

	memcpy_s((void*)memoryStreamPtr, streamSize, b, streamSize);

	return new MemoryStream(memoryStreamPtr, streamSize);
}
System::IO::MemoryStream^ Util::UnmanagedMemoryStreamToStream(MemoryStream& memoryStream)
{
	auto stream = gcnew System::IO::MemoryStream();

	CopyIntoStream(memoryStream, stream);

	return stream;
}
void Util::CopyIntoStream(MemoryStream& memoryStream, System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (memoryStream.GetMemory() == NULL)
		throw gcnew ArgumentException("Cannot read from stream");
	if (memoryStream.getMemorySize() > 0xFFFFFFFF)
		throw gcnew OutOfMemoryException("Trying to allocation too much memory");

	int streamSize = (int)memoryStream.getMemorySize();

	if (streamSize == 0)
		return;

	const PxU8* memoryPtr = memoryStream.GetMemory();

	array<Byte>^ buffer = gcnew array<Byte>(streamSize);
	pin_ptr<Byte> b = &buffer[0];

	memcpy_s(b, streamSize, memoryPtr, streamSize);

	stream->Write(buffer, 0, streamSize);
}