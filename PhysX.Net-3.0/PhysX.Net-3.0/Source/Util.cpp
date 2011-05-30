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
	if (T::typeid == short::typeid || T::typeid == unsigned short::typeid)
		return PrimitiveTypeSize::Bit16;
	else if (T::typeid == int::typeid || T::typeid == unsigned int::typeid)
		return PrimitiveTypeSize::Bit32;
	else
		return (PrimitiveTypeSize)0;
}