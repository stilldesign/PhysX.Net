#include "StdAfx.h"
#include "ObjectTable.h"
#include "IDisposable.h"
#include "PhysXException.h"

using namespace System::Threading;
using namespace System::Linq;

void ObjectTable::disposableObject_OnDisposing(Object^ sender, EventArgs^ e)
{
	// In this method we build a complete list of objects that need disposal, then iterate through them.
	// Each disposal call will trigger the OnDisposing event which won't cause a crash, but is not needed
	// and will hurt performance.
	if (_performingDisposal)
		return;

	_performingDisposal = true;

		// Call Dispose on the object and its dependents
		DisposeOfObjectAndDependents(dynamic_cast<IDisposable^>(sender));

		// Remove the object from all the dictionaries
		Remove(sender);

	_performingDisposal = false;
}

void ObjectTable::DisposeOfObjectAndDependents(PhysX::IDisposable^ disposable)
{
	if (disposable == nullptr || disposable->Disposed || !_ownership->ContainsKey(disposable))
		return;

	// Get all dependent objects of the current disposable object
	// Objects are returned in reverse depedent order - (Shape, Actor, Scene, Physics)
	auto dependents = GetDependents(disposable);

	// Dispose of the object's children first
	for each(PhysX::IDisposable^ dependent in dependents)
	{
		delete dependent;
	}
		
	// Dispose the object
	delete disposable;

	// Remove the object and its dependents from the various dictionaries
	for each(PhysX::IDisposable^ dependent in dependents)
	{
		Remove(dependent);
	}
}

array<PhysX::IDisposable^>^ ObjectTable::GetDependents(PhysX::IDisposable^ disposable)
{
	auto allDependents = gcnew List<PhysX::IDisposable^>();

	GetDependents(disposable, allDependents);

	return allDependents->ToArray();
}
void ObjectTable::GetDependents(PhysX::IDisposable^ disposable, List<PhysX::IDisposable^>^ allDependents)
{
	// TODO: Make a reverse dictionary of _ownership to avoid this O(N)
	for each(KeyValuePair<PhysX::IDisposable^, PhysX::IDisposable^> d in _ownership)
	{
		// Get the object (child) of the disposable arg
		PhysX::IDisposable^ dependent = d.Key;

		if (dependent == nullptr)
			continue;

		// Check the owner
		if (d.Value == disposable)
		{
			// Recurse first before adding the object to make a reverse tree
			// e.g. Actor - Scene - Physics
			GetDependents(dependent, allDependents);

			allDependents->Add(dependent);
		}
	}
}