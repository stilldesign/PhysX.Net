#include "StdAfx.h"
#include "Joint.h"
#include "Scene.h"
#include "Actor.h"
#include <PxJoint.h>
#include <PxRigidActor.h>

Joint::Joint(PxJoint* joint, JointType type, PhysX::Scene^ owner)
{
	if (joint == NULL)
		throw gcnew ArgumentNullException("joint");
	ThrowIfNullOrDisposed(owner, "owner");

	_joint = joint;
	_scene = owner;
	_type = type;

	ObjectTable::Add((intptr_t)joint, this, owner);
}
Joint::~Joint()
{
	this->!Joint();
}
Joint::!Joint()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_joint->release();
	_joint = NULL;

	OnDisposed(this, nullptr);
}

bool Joint::Disposed::get()
{
	return _joint == NULL;
}

JointType Joint::Type::get()
{
	return _type;
}

PhysX::Scene^ Joint::Scene::get()
{
	return _scene;
}

PhysX::Actor^ Joint::GetActor0::get()
{
	PxRigidActor* a0 = NULL;
	PxRigidActor* a1 = NULL;
	_joint->getActors(a0, a1);

	if (a0 == NULL)
		return nullptr;

	return ObjectTable::GetObject<Actor^>((intptr_t)a0);
}
PhysX::Actor^ Joint::GetActor1::get()
{
	PxRigidActor* a0 = NULL;
	PxRigidActor* a1 = NULL;
	_joint->getActors(a0, a1);

	if (a1 == NULL)
		return nullptr;

	return ObjectTable::GetObject<Actor^>((intptr_t)a1);
}

Matrix Joint::LocalPose0::get()
{
	return MathUtil::PxTransformToMatrix(&_joint->getLocalPose(0));
}
void Joint::LocalPose0::set(Matrix value)
{
	_joint->setLocalPose(0, MathUtil::MatrixToPxTransform(value));
}

Matrix Joint::LocalPose1::get()
{
	return MathUtil::PxTransformToMatrix(&_joint->getLocalPose(1));
}
void Joint::LocalPose1::set(Matrix value)
{
	_joint->setLocalPose(1, MathUtil::MatrixToPxTransform(value));
}

float Joint::BreakForce::get()
{
	float f, t;
	_joint->getBreakForce(f, t);

	return f;
}
void Joint::BreakForce::set(float value)
{
	float f, t;
	_joint->getBreakForce(f, t);

	_joint->setBreakForce(value, t);
}

float Joint::BreakForceTorque::get()
{
	float f, t;
	_joint->getBreakForce(f, t);

	return t;
}
void Joint::BreakForceTorque::set(float value)
{
	float f, t;
	_joint->getBreakForce(f, t);

	_joint->setBreakForce(f, value);
}

PhysX::ConstraintFlag Joint::ConstraintFlag::get()
{
	return ToManagedEnum(PhysX::ConstraintFlag, _joint->getConstraintFlags());
}
void Joint::ConstraintFlag::set(PhysX::ConstraintFlag value)
{
	_joint->setConstraintFlags(ToUnmanagedEnum2(PxConstraintFlags, value));
}

String^ Joint::Name::get()
{
	return Util::ToManagedString(_joint->getName());
}
void Joint::Name::set(String^ value)
{
	const char* name = _joint->getName();

	if (name != NULL)
		delete name;

	_joint->setName(Util::ToUnmanagedString(value));
}

PxJoint* Joint::UnmanagedPointer::get()
{
	return _joint;
}