#include "StdAfx.h"
#include "Foundation.h"
#include "Physics.h"
#include "ErrorCallback.h"
#include "FailedToCreateObjectException.h"
#include "FoundationAlreadyInitalizedException.h"

static Foundation::Foundation()
{
	_initalized = false;
}
Foundation::Foundation([Optional] PhysX::ErrorCallback^ errorCallback)
{
	if (Foundation::Initalized)
		throw gcnew FoundationAlreadyInitalizedException("Foundation can only be initalized once");

	PxErrorCallback* errors = (errorCallback == nullptr ? gcnew DefaultErrorCallback() : errorCallback)->UnmanagedPointer;

	_allocator = new PxDefaultAllocator();

	_foundation = PxCreateFoundation(PX_FOUNDATION_VERSION, *_allocator, *errors);
	
	if (_foundation == NULL)
		throw gcnew FailedToCreateObjectException("Failed to create Foundation");

	_initalized = true;

	_errorCallback = errorCallback;

	ObjectTable::Add((intptr_t)_foundation, this, nullptr);
}
Foundation::~Foundation()
{
	this->!Foundation();
}
Foundation::!Foundation()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_foundation->release();
	_foundation = NULL;

	SAFE_DELETE(_allocator);

	_errorCallback = nullptr;

	_initalized = false;

	OnDisposed(this, nullptr);
}

bool Foundation::Disposed::get()
{
	return (_foundation == NULL);
}

PxAllocatorCallback* Foundation::GetAllocator()
{
	return _allocator;
}

bool Foundation::Initalized::get()
{
	return _initalized;
}

PhysX::ErrorCallback^ Foundation::ErrorCallback::get()
{
	return _errorCallback;
}

PxFoundation* Foundation::UnmanagedPointer::get()
{
	return _foundation;
}