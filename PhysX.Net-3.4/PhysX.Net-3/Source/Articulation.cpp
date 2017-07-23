#include "StdAfx.h"
#include "Articulation.h"
#include "Scene.h"
#include "Bounds3.h"
#include "Serializable.h"
#include "Physics.h"

Articulation::Articulation(PxArticulation* articulation, PhysX::Physics^ owner)
{
	if (articulation == NULL)
		throw gcnew ArgumentNullException("articulation");
	ThrowIfNullOrDisposed(owner, "owner");

	_articulation = articulation;

	ObjectTable::Instance->Add((intptr_t)articulation, this, owner);
}
Articulation::~Articulation()
{
	this->!Articulation();
}
Articulation::!Articulation()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_articulation->release();
	_articulation = NULL;

	OnDisposed(this, nullptr);
}

bool Articulation::Disposed::get()
{
	return (_articulation == NULL);
}

Serializable^ Articulation::AsSerializable()
{
	return gcnew Serializable(_articulation);
}

//

PhysX::Scene^ Articulation::Scene::get()
{
	return ObjectTable::Instance->GetObject<PhysX::Scene^>((intptr_t)_articulation->getScene());
}

int Articulation::MaximumProjectionIterations::get()
{
	return _articulation->getMaxProjectionIterations();
}
void Articulation::MaximumProjectionIterations::set(int value)
{
	_articulation->setMaxProjectionIterations(value);
}

float Articulation::SeparationTolerance::get()
{
	return _articulation->getSeparationTolerance();
}
void Articulation::SeparationTolerance::set(float value)
{
	_articulation->setSeparationTolerance(value);
}

int Articulation::InternalDriveIterations::get()
{
	return _articulation->getInternalDriveIterations();
}
void Articulation::InternalDriveIterations::set(int value)
{
	_articulation->setInternalDriveIterations(value);
}

int Articulation::ExternalDriveIterations::get()
{
	return _articulation->getExternalDriveIterations();
}
void Articulation::ExternalDriveIterations::set(int value)
{
	_articulation->setExternalDriveIterations(value);
}

array<ArticulationLink^>^ Articulation::ArticulationLinks::get()
{
	int n = _articulation->getNbLinks();
	array<ArticulationLink^>^ links = gcnew array<ArticulationLink^>(n);

	PxArticulationLink** l = (PxArticulationLink**)malloc(sizeof(PxArticulationLink*) * n);
	_articulation->getLinks(l, n);

	for (int i = 0; i < n; i++)
	{
		links[i] = ObjectTable::Instance->GetObject<ArticulationLink^>((intptr_t)l + i);
	}

	free(l);

	return links;
}

String^ Articulation::Name::get()
{
	return Util::ToManagedString(_articulation->getName());
}
void Articulation::Name::set(String^ value)
{
	if (_articulation->getName() != NULL)
		Marshal::FreeHGlobal(IntPtr((char*)_articulation->getName()));

	_articulation->setName(Util::ToUnmanagedString(value));
}

Bounds3 Articulation::WorldBounds::get()
{
	return Bounds3::ToManaged(_articulation->getWorldBounds());
}

PhysX::Aggregate^ Articulation::Aggregate::get()
{
	return ObjectTable::Instance->GetObject<PhysX::Aggregate^>((intptr_t)_articulation->getAggregate());
}

PxArticulation* Articulation::UnmanagedPointer::get()
{
	return _articulation;
}