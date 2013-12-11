#include "StdAfx.h"
#include "Constraint.h"
#include "RigidActor.h"
#include "Physics.h"
#include "Constraint.h"
//#include <PxConstraint.h> 

Constraint::Constraint(PxConstraint* constraint, PhysX::IDisposable^ owner)
{
	if (constraint == NULL)
		throw gcnew ArgumentNullException("constraint");
	ThrowIfNullOrDisposed(owner, "owner");

	_constraint = constraint;

	// Constraints can be created either manually which means they are owned by their parent PxPhysics,
	// or they are automatically created by a joint
	if (owner != nullptr)
		ObjectTable::Add((intptr_t)constraint, this, owner);
}
Constraint::~Constraint()
{
	this->!Constraint();
}
Constraint::!Constraint()
{
	if (this->Disposed)
		return;

	_constraint->release();
	_constraint = NULL;
}

bool Constraint::Disposed::get()
{
	return (_constraint == NULL);
}

void Constraint::SetActors(PhysX::RigidActor^ actor0, PhysX::RigidActor^ actor1)
{
	ThrowIfNull(actor0, "actor0");
	ThrowIfNull(actor1, "actor1");

	_constraint->setActors(actor0->UnmanagedPointer, actor1->UnmanagedPointer);
}

void Constraint::MarkDirty()
{
	_constraint->markDirty();
}

void Constraint::SetBreakForce(float linear, float angular)
{
	_constraint->setBreakForce(linear, angular);
}

Serializable^ Constraint::AsSerializable()
{
	return gcnew Serializable(_constraint);
}

//

PhysX::Scene^ Constraint::Scene::get()
{
	PxScene* scene = _constraint->getScene();

	return ObjectTable::GetObject<PhysX::Scene^>((intptr_t)scene);
}

PhysX::RigidActor^ Constraint::Actor0::get()
{
	PxRigidActor *a = NULL, *b = NULL;
	_constraint->getActors(a, b);

	if (a == NULL)
		return nullptr;

	return ObjectTable::GetObject<RigidActor^>((intptr_t)a);
}
void Constraint::Actor0::set(PhysX::RigidActor^ value)
{
	ThrowIfNull(value, "value");

	PxRigidActor *a = NULL, *b = NULL;
	_constraint->getActors(a, b);

	_constraint->setActors(value->UnmanagedPointer, b);
}

PhysX::RigidActor^ Constraint::Actor1::get()
{
	PxRigidActor *a, *b;
	_constraint->getActors(a, b);

	if (b == NULL)
		return nullptr;

	return ObjectTable::GetObject<RigidActor^>((intptr_t)b);
}
void Constraint::Actor1::set(PhysX::RigidActor^ value)
{
	ThrowIfNull(value, "value");

	PxRigidActor *a, *b;
	_constraint->getActors(a, b);

	_constraint->setActors(a, value->UnmanagedPointer);
}

ConstraintFlag Constraint::Flags::get()
{
	return ToManagedEnum(ConstraintFlag, _constraint->getFlags());
}
void Constraint::Flags::set(ConstraintFlag value)
{
	_constraint->setFlags(ToUnmanagedEnum(PxConstraintFlag, value));
}

Vector3 Constraint::LinearForce::get()
{
	PxVec3 linear, angular;
	_constraint->getForce(linear, angular);

	return MV(linear);
}
Vector3 Constraint::AngularForce::get()
{
	PxVec3 linear, angular;
	_constraint->getForce(linear, angular);

	return MV(angular);
}

float Constraint::LinearBreakForce::get()
{
	float linear, angular;
	_constraint->getBreakForce(linear, angular);

	return linear;
}
void Constraint::LinearBreakForce::set(float value)
{
	float linear, angular;
	_constraint->getBreakForce(linear, angular);

	_constraint->setBreakForce(value, angular);
}

float Constraint::AngularBreakForce::get()
{
	float linear, angular;
	_constraint->getBreakForce(linear, angular);

	return angular;
}
void Constraint::AngularBreakForce::set(float value)
{
	float linear, angular;
	_constraint->getBreakForce(linear, angular);

	_constraint->setBreakForce(linear, value);
}