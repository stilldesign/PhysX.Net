#include "StdAfx.h"
#include "ContactSet.h"

#include <PxContactModifyCallback.h> 

ContactSet::ContactSet(PxContactSet unmanaged)
{
	// Clone the PxContactSet
	_contactSet = new PxContactSet(unmanaged);
}
ContactSet::~ContactSet()
{
	this->!ContactSet();
}
ContactSet::!ContactSet()
{
	SAFE_DELETE(_contactSet);
}

Vector3 ContactSet::GetPoint(int i)
{
	return MV(_contactSet->getPoint(i));
}
void ContactSet::SetPoint(int i, Vector3 p)
{
	_contactSet->setPoint(i, UV(p));
}

Vector3 ContactSet::GetNormal(int i)
{
	return MV(_contactSet->getNormal(i));
}
void ContactSet::SetNormal(int i, Vector3 n)
{
	_contactSet->setNormal(i, UV(n));
}

float ContactSet::GetSeparation(int i)
{
	return _contactSet->getSeparation(i);
}
void ContactSet::SetSeparation(int i, float s)
{
	_contactSet->setSeparation(i, s);
}

Vector3 ContactSet::GetTargetVelocity(int i)
{
	return MV(_contactSet->getTargetVelocity(i));
}
void ContactSet::SetTargetVelocity(int i, Vector3 v)
{
	_contactSet->setTargetVelocity(i, UV(v));
}

int ContactSet::GetInternalFaceIndex0(int i)
{
	return _contactSet->getInternalFaceIndex0(i);
}
int ContactSet::GetInternalFaceIndex1(int i)
{
	return _contactSet->getInternalFaceIndex1(i);
}

float ContactSet::GetMaxImpulse(int i)
{
	return _contactSet->getMaxImpulse(i);
}
void ContactSet::SetMaxImpulse(int i, float s)
{
	_contactSet->setMaxImpulse(i, s);
}

void ContactSet::Ignore(int i)
{
	_contactSet->ignore(i);
}
int ContactSet::Size::get()
{
	return _contactSet->size();
}

float ContactSet::GetInvMassScale0()
{
	return _contactSet->getInvMassScale0();
}
float ContactSet::GetInvMassScale1()
{
	return _contactSet->getInvMassScale1();
}

float ContactSet::GetInvInertiaScale0()
{
	return _contactSet->getInvInertiaScale0();
}
float ContactSet::GetInvInertiaScale1()
{
	return _contactSet->getInvInertiaScale1();
}

void ContactSet::SetInvMassScale0(float scale)
{
	_contactSet->setInvMassScale0(scale);
}
void ContactSet::SetInvMassScale1(float scale)
{
	_contactSet->setInvMassScale1(scale);
}

void ContactSet::SetInvInertiaScale0(float scale)
{
	_contactSet->setInvInertiaScale0(scale);
}
void ContactSet::SetInvInertiaScale1(float scale)
{
	_contactSet->setInvInertiaScale1(scale);
}

PxContactSet* ContactSet::UnmanagedPointer::get()
{
	return _contactSet;
}