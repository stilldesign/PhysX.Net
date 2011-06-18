#include "StdAfx.h"
#include "Observable.h"
#include "ObservableInstance.h"
#include "Observer.h"

ObservableType ObservableExtensions::GetObservableType(PhysX::IObservable^ observable)
{
	ThrowIfNull(observable, "observable");

	auto instance = observable->GetObservableInstance();

	return ToManagedEnum(ObservableType, instance->UnmanagedPointer->getObservableType());
}

void ObservableExtensions::RegisterObserver(PhysX::IObservable^ observable, PhysX::Observer^ observer)
{
	ThrowIfNull(observable, "observable");
	ThrowIfNull(observer, "observer");

	auto instance = observable->GetObservableInstance();

	return instance->UnmanagedPointer->registerObserver(*observer->UnmanagedPointer);
}

void ObservableExtensions::UnregisterObserver(PhysX::IObservable^ observable, PhysX::Observer^ observer)
{
	ThrowIfNull(observable, "observable");
	ThrowIfNull(observer, "observer");

	auto instance = observable->GetObservableInstance();

	return instance->UnmanagedPointer->unregisterObserver(*observer->UnmanagedPointer);
}

int ObservableExtensions::GetNumberOfObservers(PhysX::IObservable^ observable)
{
	ThrowIfNull(observable, "observable");

	auto instance = observable->GetObservableInstance();

	return instance->UnmanagedPointer->getNbObservers();
}

array<PhysX::Observer^>^ ObservableExtensions::GetObservers(PhysX::IObservable^ observable)
{
	ThrowIfNull(observable, "observable");

	auto instance = observable->GetObservableInstance();

	int n = instance->UnmanagedPointer->getNbObservers();

	PxObserver** o = new PxObserver*[n];
	instance->UnmanagedPointer->getObservers(o, n);

	auto observers = gcnew array<PhysX::Observer^>(n);

	for (int i = 0; i < n; i++)
	{
		observers[i] = gcnew PhysX::Observer(o[i]);
	}

	delete o;

	return observers;
}