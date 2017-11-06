#include "StdAfx.h"
#include "Constraint.h"
#include "Joint.h"
#include "Scene.h"
#include "RigidActor.h"
#include "Serializable.h"
#include "Physics.h"
#include "Scene.h"

Joint::Joint(PxJoint* joint, PhysX::Physics^ owner)
{
	if (joint == NULL)
		throw gcnew ArgumentNullException("joint");
	ThrowIfNullOrDisposed(owner, "owner");

	_joint = joint;
	_owner = owner;

	// Constraint objects appear to be reused, so try get the existing wrapped one, otherwise create it
	_constraint = ObjectTable::Instance->TryGetObject<PhysX::Constraint^>((intptr_t)_joint->getConstraint());
	if (_constraint == nullptr)
		_constraint = gcnew PhysX::Constraint(_joint->getConstraint(), this, false);

	ObjectTable::Instance->Add((intptr_t)joint, this, owner);
}
Joint::~Joint()
{
	this->!Joint();
}
Joint::!Joint()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_joint->release();
	_joint = NULL;

	_owner = nullptr;
	_constraint = nullptr;

	OnDisposed(this, nullptr);
}

bool Joint::Disposed::get()
{
	return (_joint == NULL);
}

void Joint::SetActors(RigidActor^ actor0, RigidActor^ actor1)
{
	_joint->setActors(GetPointerOrNull(actor0), GetPointerOrNull(actor1));
}

Vector3 Joint::GetRelativeAngularVelocity()
{
	return MV(_joint->getRelativeAngularVelocity());
}

Vector3 Joint::GetRelativeLinearVelocity()
{
	return MV(_joint->getRelativeLinearVelocity());
}

Matrix Joint::GetRelativeTransform()
{
	return MathUtil::PxTransformToMatrix(&_joint->getRelativeTransform());
}

Serializable^ Joint::AsSerializable()
{
	return gcnew Serializable(_joint);
}

void Joint::SetGlobalFrame(Vector3 anchor, Vector3 axis)
{
	PxSetJointGlobalFrame(*this->UnmanagedPointer, &UV(anchor), &UV(axis));
}

//

PhysX::Scene^ Joint::Scene::get()
{
	return ObjectTable::Instance->TryGetObject<PhysX::Scene^>((intptr_t)_joint->getScene());
}

PhysX::Constraint^ Joint::Constraint::get()
{
	return _constraint;
}

JointType Joint::Type::get()
{
	return ToManagedEnum(JointType, _joint->getConcreteType());
}

PhysX::RigidActor^ Joint::Actor0::get()
{
	PxRigidActor* a0 = NULL;
	PxRigidActor* a1 = NULL;
	_joint->getActors(a0, a1);

	if (a0 == NULL)
		return nullptr;

	return ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)a0);
}
PhysX::RigidActor^ Joint::Actor1::get()
{
	PxRigidActor* a0 = NULL;
	PxRigidActor* a1 = NULL;
	_joint->getActors(a0, a1);

	if (a1 == NULL)
		return nullptr;

	return ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)a1);
}

Transform Joint::LocalPose0::get()
{
	return Transform::ToManaged(_joint->getLocalPose(PxJointActorIndex::eACTOR0));
}
void Joint::LocalPose0::set(Transform value)
{
	_joint->setLocalPose(PxJointActorIndex::eACTOR0, Transform::ToUnmanaged(value));
}

Transform Joint::LocalPose1::get()
{
	return Transform::ToManaged(_joint->getLocalPose(PxJointActorIndex::eACTOR1));
}
void Joint::LocalPose1::set(Transform value)
{
	_joint->setLocalPose(PxJointActorIndex::eACTOR1, Transform::ToUnmanaged(value));
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

PhysX::ConstraintFlag Joint::ConstraintFlags::get()
{
	return ToManagedEnum(PhysX::ConstraintFlag, _joint->getConstraintFlags());
}
void Joint::ConstraintFlags::set(PhysX::ConstraintFlag value)
{
	_joint->setConstraintFlags(ToUnmanagedEnum2(PxConstraintFlags, value));
}

/// <summary>
/// Gets or sets the inverse mass scale for actor0.
/// </summary>
float Joint::InverseMassScale0::get()
{
	return _joint->getInvMassScale0();
}
void Joint::InverseMassScale0::set(float value)
{
	_joint->setInvMassScale0(value);
}

float Joint::InverseMassScale1::get()
{
	return _joint->getInvMassScale1();
}
void Joint::InverseMassScale1::set(float value)
{
	_joint->setInvMassScale1(value);
}

float Joint::InverseInertiaScale0::get()
{
	return _joint->getInvInertiaScale0();
}
void Joint::InverseInertiaScale0::set(float value)
{
	_joint->setInvInertiaScale0(value);
}

float Joint::InverseInertiaScale1::get()
{
	return _joint->getInvInertiaScale1();
}
void Joint::InverseInertiaScale1::set(float value)
{
	_joint->setInvInertiaScale1(value);
}

String^ Joint::Name::get()
{
	return Util::ToManagedString(_joint->getName());
}
void Joint::Name::set(String^ value)
{
	if (_joint->getName() != NULL)
		Marshal::FreeHGlobal(IntPtr((char*)_joint->getName()));
	
	_joint->setName(Util::ToUnmanagedString(value));
}

PxJoint* Joint::UnmanagedPointer::get()
{
	return _joint;
}