#include "StdAfx.h"
#include "Util.h"

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

	if (count <= 0)
		return gcnew array<T>(0);

	array<T>^ arr = gcnew array<T>(count);

	pin_ptr<T> arrPin = &arr[0];

	memcpy_s(arrPin,count*sizeof(T), memory, count*sizeof(T));

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

	if (arr->Length == 0)
		return;

	int s = sizeof(T);
	int n = arr->Length;

	pin_ptr<T> arrPin = &arr[0];

	memcpy_s(dest, n * s, arrPin, n * s);
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
Nullable<bool> Util::Is16Or32Bit(Array^ values)
{
	if (values == nullptr)
		return Nullable<bool>();

	Type^ type = values->GetType();

	if (!type->HasElementType || Util::Is16Or32Bit(type->GetElementType()) == (PrimitiveTypeSize)0)
		return Nullable<bool>();

	PrimitiveTypeSize t = Util::Is16Or32Bit(type->GetElementType());

	if (t == PrimitiveTypeSize::Bit16)
		return true;
	else if (t == PrimitiveTypeSize::Bit32)
		return false;

	return Nullable<bool>();
}

PxDefaultMemoryInputData* Util::StreamToUnmanagedInputStream(System::IO::Stream^ stream)
{
	ThrowIfNull(stream, "stream");
	if (!stream->CanRead)
		throw gcnew ArgumentException("Cannot read from stream", "stream");
	if (stream->Length > 0xFFFFFFFF) // Max 32 bit (4 GB) (somewhat arbitary, but nothing will ever allocate this much)
		throw gcnew OutOfMemoryException("Trying to allocation too much memory, the max is 4 GB");

	int streamSize = (int)stream->Length;

	if (streamSize == 0)
		return new PxDefaultMemoryInputData(NULL, 0);

	PxU8* memoryStreamPtr = (PxU8*)malloc(streamSize * sizeof(PxU8));

	auto data = new PxDefaultMemoryInputData(memoryStreamPtr, streamSize);

	if (memoryStreamPtr == NULL)
		throw gcnew InvalidOperationException("Failed to allocate memory used for cloning managed stream");

	ZeroMemory((void*)memoryStreamPtr, streamSize);

	array<Byte>^ buffer = gcnew array<Byte>(streamSize);
	stream->Read(buffer, 0, streamSize);
	pin_ptr<Byte> b = &buffer[0];

	memcpy_s((void*)memoryStreamPtr, streamSize, b, streamSize);
	
	return data;
}
//System::IO::MemoryStream^ Util::UnmanagedMemoryStreamToStream(MemoryStream& memoryStream)
//{
//	auto stream = gcnew System::IO::MemoryStream();
//
//	CopyIntoStream(memoryStream, stream);
//
//	return stream;
//}
void Util::CopyIntoStream(PxDefaultMemoryOutputStream* from, System::IO::Stream^ to)
{
	if (from->getData() == NULL)
		throw gcnew ArgumentException("Cannot read from unmanaged stream, its memory is null", "from");
	if (from->getSize() > 0xFFFFFFFF)
		throw gcnew OutOfMemoryException("Trying to allocation too much memory");
	ThrowIfNull(to, "stream");
	if (!to->CanWrite)
		throw gcnew ArgumentException("Cannot write to destination stream", "to");

	int streamSize = (int)from->getSize();

	if (streamSize <= 0)
		return;

	PxU8* fromData = from->getData();

	array<Byte>^ buffer = gcnew array<Byte>(streamSize);
	pin_ptr<Byte> b = &buffer[0];

	memcpy_s(b, streamSize, fromData, streamSize);

	to->Write(buffer, 0, streamSize);
}

generic<typename T> where T : value class
array<T>^ Util::CopyToValueTypeArray(array<Byte>^ bytes)
{
	ThrowIfNull(bytes, "bytes");

	int t = sizeof(T);
	int size = bytes->Length;
	int n = size / t;

	auto dst = gcnew array<T>(n);

	pin_ptr<Byte> src_pin = &bytes[0];
	pin_ptr<T> dst_pin = &dst[0];

	memcpy(dst_pin, src_pin, size);

	return dst;
}