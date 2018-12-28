#include "StdAfx.h"
#include "ArticulationJoint.h"
#include "Scene.h"
#include "Serializable.h"

ArticulationJoint::ArticulationJoint(PxArticulationJoint* joint, PhysX::Scene^ owner)
{
	if (joint == NULL)
		throw gcnew ArgumentNullException("joint");
	ThrowIfNullOrDisposed(owner, "owner");

	_joint = joint;
	_scene = owner;

	ObjectTable::Instance->Add((intptr_t)joint, this, owner);
}
ArticulationJoint::~ArticulationJoint()
{
	this->!ArticulationJoint();
}
ArticulationJoint::!ArticulationJoint()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	// TODO: Release art joint

	OnDisposed(this, nullptr);
}

bool ArticulationJoint::Disposed::get()
{
	return (_joint == NULL);
}

Serializable^ ArticulationJoint::AsSerializable()
{
	return gcnew Serializable(_joint);
}

PhysX::Scene^ ArticulationJoint::Scene::get()
{
	return _scene;
}

Matrix ArticulationJoint::ParentPose::get()
{
	return MathUtil::PxTransformToMatrix(&_joint->getParentPose());
}
void ArticulationJoint::ParentPose::set(Matrix value)
{
	_joint->setParentPose(MathUtil::MatrixToPxTransform(value));
}

Matrix ArticulationJoint::ChildPose::get()
{
	return MathUtil::PxTransformToMatrix(&_joint->getChildPose());
}
void ArticulationJoint::ChildPose::set(Matrix value)
{
	_joint->setChildPose(MathUtil::MatrixToPxTransform(value));
}

Quaternion ArticulationJoint::TargetOrientation::get()
{
	return MathUtil::PxQuatToQuaternion(_joint->getTargetOrientation());
}
void ArticulationJoint::TargetOrientation::set(Quaternion value)
{
	_joint->setTargetOrientation(MathUtil::QuaternionToPxQuat(value));
}

Vector3 ArticulationJoint::TargetVelocity::get()
{
	return MathUtil::PxVec3ToVector3(_joint->getTargetVelocity());
}
void ArticulationJoint::TargetVelocity::set(Vector3 value)
{
	_joint->setTargetVelocity(MathUtil::Vector3ToPxVec3(value));
}

float ArticulationJoint::TangentialStiffness::get()
{
	return _joint->getTangentialStiffness();
}
void ArticulationJoint::TangentialStiffness::set(float value)
{
	_joint->setTangentialStiffness(value);
}

float ArticulationJoint::Damping::get()
{
	return _joint->getDamping();
}
void ArticulationJoint::Damping::set(float value)
{
	_joint->setDamping(value);
}

float ArticulationJoint::InternalCompliance::get()
{
	return _joint->getInternalCompliance();
}
void ArticulationJoint::InternalCompliance::set(float value)
{
	_joint->setInternalCompliance(value);
}

float ArticulationJoint::ExternalCompliance::get()
{
	return _joint->getExternalCompliance();
}
void ArticulationJoint::ExternalCompliance::set(float value)
{
	_joint->setExternalCompliance(value);
}

float ArticulationJoint::SwingLimitY::get()
{
	float y, z;
	_joint->getSwingLimit(y, z);

	return y;
}
void ArticulationJoint::SwingLimitY::set(float value)
{
	float y, z;
	_joint->getSwingLimit(y, z);

	_joint->setSwingLimit(value, z);
}

float ArticulationJoint::SwingLimitZ::get()
{
	float y, z;
	_joint->getSwingLimit(y, z);

	return z;
}
void ArticulationJoint::SwingLimitZ::set(float value)
{
	float y, z;
	_joint->getSwingLimit(y, z);

	_joint->setSwingLimit(y, value);
}

bool ArticulationJoint::SwingLimitEnabled::get()
{
	return _joint->getSwingLimitEnabled();
}
void ArticulationJoint::SwingLimitEnabled::set(bool value)
{
	_joint->setSwingLimitEnabled(value);
}

float ArticulationJoint::TwistLimitLower::get()
{
	float l, u;
	_joint->getTwistLimit(l, u);

	return l;
}
void ArticulationJoint::TwistLimitLower::set(float value)
{
	float l, u;
	_joint->getTwistLimit(l, u);

	_joint->setTwistLimit(value, u);
}

float ArticulationJoint::TwistLimitUpper::get()
{
	float l, u;
	_joint->getTwistLimit(l, u);

	return u;
}
void ArticulationJoint::TwistLimitUpper::set(float value)
{
	float l, u;
	_joint->getTwistLimit(l, u);

	_joint->setTwistLimit(l, value);
}

bool ArticulationJoint::TwistLimitEnabled::get()
{
	return _joint->getTwistLimitEnabled();
}
void ArticulationJoint::TwistLimitEnabled::set(bool value)
{
	_joint->setTwistLimitEnabled(value);
}

PxArticulationJoint* ArticulationJoint::UnmanagedPointer::get()
{
	return _joint;
}
