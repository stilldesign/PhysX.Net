#include "StdAfx.h"
#include "ArticulationLink.h"
#include "Articulation.h"
#include "Scene.h"
#include <PxArticulationLink.h> 
#include <PxArticulation.h> 

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
	return ObjectTable::GetObject<PhysX::Articulation^>((intptr_t)&this->UnmanagedPointer->getArticulation());
}

PhysX::ArticulationJoint^ ArticulationLink::ArticulationJoint::get()
{
	auto j = this->UnmanagedPointer->getInboundJoint();
	return ObjectTable::GetObject<PhysX::ArticulationJoint^>((intptr_t)&j);
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
		PxArticulation& a = links[i]->getArticulation();
		auto articulation = ObjectTable::GetObject<PhysX::Articulation^>((intptr_t)&a);

		l[i] = gcnew ArticulationLink(links[i], articulation);
	}

	return l;
}

PxArticulationLink* ArticulationLink::UnmanagedPointer::get()
{
	return (PxArticulationLink*)RigidBody::UnmanagedPointer;
}