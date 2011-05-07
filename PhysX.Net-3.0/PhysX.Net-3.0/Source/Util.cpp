#include "StdAfx.h"
#include "Util.h"

using namespace PhysX;

generic<typename T>
T PhysX::Util::CloneFloatStruct(int numOfFloats, void* p_unmanaged)
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
