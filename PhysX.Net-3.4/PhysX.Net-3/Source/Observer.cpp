#include "StdAfx.h"
#include "Observer.h"

Observer::Observer(PxObserver* observer)
{
	if (observer == NULL)
		throw gcnew ArgumentNullException("observer");

	_observer = observer;
}

Observer::~Observer()
{
	this->!Observer();
}
Observer::!Observer()
{
	_observer = NULL;
}

PxObserver* Observer::UnmanagedPointer::get()
{
	return _observer;
}