#include "StdAfx.h"
#include "LockedData.h"

LockedData::LockedData(PxLockedData* data)
{
	if (data == NULL)
		throw gcnew ArgumentNullException("data");

	_data = data;
}
LockedData::~LockedData()
{
	this->!LockedData();
}
LockedData::!LockedData()
{
	_data = NULL;
}

bool LockedData::Disposed::get()
{
	return _data == NULL;
}

void LockedData::Unlock()
{
	_data->unlock();
}

PhysX::DataAccessFlag LockedData::DataAccessFlag::get()
{
	return ToManagedEnum(PhysX::DataAccessFlag, _data->getDataAccessFlags());
}

PxLockedData* LockedData::UnmanagedPointer::get()
{
	return _data;
}