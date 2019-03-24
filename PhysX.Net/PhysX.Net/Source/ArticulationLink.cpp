#include "StdAfx.h"
#include "ArticulationLink.h"
#include "Articulation.h"
#include "Scene.h"
#include "Physics.h"

ArticulationLink::ArticulationLink(PxArticulationLink* articulationLink, PhysX::Articulation^ owner)
	: RigidBody(articulationLink, owner->Scene->Physics)
{
	
}
ArticulationLink::~ArticulationLink()
{
	this->!ArticulationLink();
}
ArticulationLink::!ArticulationLink()
{
	
}

PhysX::Articulation^ ArticulationLink::Articulation::get()
{
	return ObjectTable::Instance->GetObject<PhysX::Articulation^>((intptr_t)&this->UnmanagedPointer->getArticulation());
}

PhysX::ArticulationJoint^ ArticulationLink::ArticulationJoint::get()
{
	auto j = this->UnmanagedPointer->getInboundJoint();
	return ObjectTable::Instance->GetObject<PhysX::ArticulationJoint^>((intptr_t)&j);
}

array<PhysX::ArticulationLink^>^ ArticulationLink::Children::get()
{
	int n = this->UnmanagedPointer->getNbChildren();

	auto l = gcnew array<ArticulationLink^>(n);

	PxArticulationLink** links = new PxArticulationLink*[n];
	int q = this->UnmanagedPointer->getChildren(links, n);

	assert(q<=n);

	for (int i = 0; i < q; i++)
	{
		PxArticulationBase& a = links[i]->getArticulation();
		auto articulation = ObjectTable::Instance->GetObject<PhysX::Articulation^>((intptr_t)&a);

		l[i] = gcnew ArticulationLink(links[i], articulation);
	}

	return l;
}

PxArticulationLink* ArticulationLink::UnmanagedPointer::get()
{
	return (PxArticulationLink*)RigidBody::UnmanagedPointer;
}