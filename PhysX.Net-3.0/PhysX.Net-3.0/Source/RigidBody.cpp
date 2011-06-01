#include "StdAfx.h"
#include "RigidBody.h"
#include <PxRigidBody.h>
#include <PxRigidBodyExt.h>

RigidBody::RigidBody(PxRigidBody* rigidBody, PhysX::Physics^ owner)
	: RigidActor(rigidBody, owner)
{
	
}

void RigidBody::AddForce(Vector3 force)
{
	AddForce(force, ForceMode::Force, true);
}
void RigidBody::AddForce(Vector3 force, ForceMode mode, bool wake)
{
	this->UnmanagedPointer->addForce(MathUtil::Vector3ToPxVec3(force), ToUnmanagedEnum(PxForceMode, mode), wake);
}

void RigidBody::ClearForce()
{
	ClearForce(ForceMode::Force, true);
}
void RigidBody::ClearForce(ForceMode mode, bool wake)
{
	this->UnmanagedPointer->clearForce(ToUnmanagedEnum(PxForceMode, mode), wake);
}

void RigidBody::ClearTorque()
{
	ClearTorque(ForceMode::Force, true);
}
void RigidBody::ClearTorque(ForceMode mode, bool wake)
{
	this->UnmanagedPointer->clearTorque(ToUnmanagedEnum(PxForceMode, mode), wake);
}

bool RigidBody::UpdateMassAndInertia(float density, [Optional] Nullable<Vector3> massLocalPose)
{
	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);
	return PxRigidBodyExt::updateMassAndInertia(*this->UnmanagedPointer, density, mlp);
}

bool RigidBody::SetMassAndUpdateInertia(float mass, [Optional] Nullable<Vector3> massLocalPose)
{
	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);
	return PxRigidBodyExt::setMassAndUpdateInertia(*this->UnmanagedPointer, mass, mlp);
}

void RigidBody::AddForceAtPosition(Vector3 force, Vector3 position)
{
	AddForceAtPosition(force, position, ForceMode::Force, true);
}
void RigidBody::AddForceAtPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp)
{
	PxRigidBodyExt::addForceAtPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

void RigidBody::AddForceAtLocalPosition(Vector3 force, Vector3 position)
{
	AddForceAtLocalPosition(force, position, ForceMode::Force, true);
}
void RigidBody::AddForceAtLocalPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp)
{
	PxRigidBodyExt::addForceAtLocalPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

void RigidBody::AddLocalForceAtPosition(Vector3 force, Vector3 position)
{
	AddLocalForceAtPosition(force, position, ForceMode::Force, true);
}
void RigidBody::AddLocalForceAtPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp)
{
	PxRigidBodyExt::addForceAtLocalPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

void RigidBody::AddLocalForceAtLocalPosition(Vector3 force, Vector3 position)
{
	AddLocalForceAtLocalPosition(force, position, ForceMode::Force, true);
}
void RigidBody::AddLocalForceAtLocalPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp)
{
	PxRigidBodyExt::addLocalForceAtLocalPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

Vector3 RigidBody::GetPointVelocity(Vector3 point)
{
	PxVec3 v = PxRigidBodyExt::getPointVelocity(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(point));

	return MathUtil::PxVec3ToVector3(v);
}

//

Matrix RigidBody::CenterOfMassLocalPose::get()
{
	return MathUtil::PxTransformToMatrix(&this->UnmanagedPointer->getCMassLocalPose());
}
void RigidBody::CenterOfMassLocalPose::set(Matrix value)
{
	this->UnmanagedPointer->setCMassLocalPose(MathUtil::MatrixToPxTransform(value));
}

float RigidBody::Mass::get()
{
	return this->UnmanagedPointer->getMass();
}
void RigidBody::Mass::set(float value)
{
	this->UnmanagedPointer->setMass(value);
}

Vector3 RigidBody::MassSpaceInertiaTensor::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getMassSpaceInertiaTensor());
}
void RigidBody::MassSpaceInertiaTensor::set(Vector3 value)
{
	return this->UnmanagedPointer->setMassSpaceInertiaTensor(MathUtil::Vector3ToPxVec3(value));
}

Vector3 RigidBody::LinearVelocity::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getLinearVelocity());
}
void RigidBody::LinearVelocity::set(Vector3 value)
{
	return this->UnmanagedPointer->setLinearVelocity(MathUtil::Vector3ToPxVec3(value));
}

Vector3 RigidBody::AngularVelocity::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getAngularVelocity());
}
void RigidBody::AngularVelocity::set(Vector3 value)
{
	return this->UnmanagedPointer->setAngularVelocity(MathUtil::Vector3ToPxVec3(value));
}

PxRigidBody* RigidBody::UnmanagedPointer::get()
{
	return (PxRigidBody*) RigidActor::UnmanagedPointer;
}