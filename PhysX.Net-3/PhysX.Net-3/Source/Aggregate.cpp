#include "StdAfx.h"
#include "Aggregate.h"
#include "Scene.h"
#include "Actor.h"
#include "Articulation.h"
#include <PxAggregate.h> 

Aggregate::Aggregate(PxAggregate* aggregate, PhysX::Scene^ owner)
{
	if (aggregate == NULL)
		throw gcnew ArgumentNullException("aggregate");
	ThrowIfNullOrDisposed(owner, "owner");

	_aggregate = aggregate;
	_scene = owner;
	_actors = gcnew List<Actor^>();

	ObjectTable::Add((intptr_t)aggregate, this, owner);
}
Aggregate::~Aggregate()
{
	this->!Aggregate();
}
Aggregate::!Aggregate()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_aggregate->release();
	_aggregate = NULL;

	OnDisposed(this, nullptr);
}

bool Aggregate::Disposed::get()
{
	return _aggregate == NULL;
}

bool Aggregate::AddActor(Actor^ actor)
{
	ThrowIfNullOrDisposed(actor, "actor");

	_actors->Add(actor);

	return _aggregate->addActor(*actor->UnmanagedPointer);
}

bool Aggregate::RemoveActor(Actor^ actor)
{
	ThrowIfNullOrDisposed(actor, "actor");

	_actors->Remove(actor);

	return _aggregate->removeActor(*actor->UnmanagedPointer);
}

bool Aggregate::AddArticulation(Articulation^ articulation)
{
	ThrowIfNullOrDisposed(articulation, "articulation");

	return _aggregate->addArticulation(*articulation->UnmanagedPointer);
}

bool Aggregate::RemoveArticulation(Articulation^ articulation)
{
	ThrowIfNullOrDisposed(articulation, "articulation");

	return _aggregate->removeArticulation(*articulation->UnmanagedPointer);
}

Actor^ Aggregate::GetActor(int index)
{
	PxActor* a = _aggregate->getActor(index);

	if (a == NULL)
		return nullptr;

	return ObjectTable::GetObject<Actor^>((intptr_t)a);
}

PhysX::Scene^ Aggregate::Scene::get()
{
	return _scene;
}

int Aggregate::MaximumSize::get()
{
	return _aggregate->getMaxSize();
}

int Aggregate::CurrentSize::get()
{
	return _aggregate->getCurrentSize();
}

IEnumerable<Actor^>^ Aggregate::Actors::get()
{
	return _actors;
}

bool Aggregate::SelfCollision::get()
{
	return _aggregate->getSelfCollision();
}

PxAggregate* Aggregate::UnmanagedPointer::get()
{
	return _aggregate;
}