#include "StdAfx.h"
#include "RigidBody.h"
#include "BatchQuery.h"
#include "FilterData.h"
#include "Scene.h"
#include "QueryFilterCallback.h"
#include "QueryCache.h"
#include "LinearSweepSingleResult.h"
#include "LinearSweepMultipleResult.h"
#include "SweepHit.h"
#include "LinearSweepMultipleResult.h"
#include "MassProperties.h"
#include "VelocityDeltaFromImpulseResult.h"
#include "LinearAngularImpulseResult.h"

RigidBody::RigidBody(PxRigidBody* rigidBody, PhysX::IDisposable^ owner)
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
	ClearForce(ForceMode::Force);
}
void RigidBody::ClearForce(ForceMode mode)
{
	this->UnmanagedPointer->clearForce(ToUnmanagedEnum(PxForceMode, mode));
}

void RigidBody::AddTorque(Vector3 force)
{
	AddTorque(force, ForceMode::Force, true);
}
void RigidBody::AddTorque(Vector3 force, ForceMode mode, bool wake)
{
	this->UnmanagedPointer->addTorque(MathUtil::Vector3ToPxVec3(force), ToUnmanagedEnum(PxForceMode, mode), wake);
}

void RigidBody::ClearTorque()
{
	ClearTorque(ForceMode::Force);
}
void RigidBody::ClearTorque(ForceMode mode)
{
	this->UnmanagedPointer->clearTorque(ToUnmanagedEnum(PxForceMode, mode));
}

bool RigidBody::UpdateMassAndInertia(float density, [Optional] Nullable<Vector3> massLocalPose, [Optional] bool includeNonSimShapes)
{
	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);

	return PxRigidBodyExt::updateMassAndInertia(*this->UnmanagedPointer, density, mlp, includeNonSimShapes);
}
bool RigidBody::UpdateMassAndInertia(array<float>^ shapeDensities, Nullable<Vector3> massLocalPose, [Optional] bool includeNonSimShapes)
{
	float* sd = new float[shapeDensities->Length];
	Util::AsUnmanagedArray(shapeDensities, sd, shapeDensities->Length);

	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);

	bool result = PxRigidBodyExt::updateMassAndInertia(*this->UnmanagedPointer, sd, shapeDensities->Length, mlp, includeNonSimShapes);

	delete[] sd;

	return result;
}

bool RigidBody::SetMassAndUpdateInertia(float mass, [Optional] Nullable<Vector3> massLocalPose)
{
	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);
	return PxRigidBodyExt::setMassAndUpdateInertia(*this->UnmanagedPointer, mass, mlp);
}
bool RigidBody::SetMassAndUpdateInertia(array<float>^ shapeMasses, [Optional] Nullable<Vector3> massLocalPose)
{
	float* sm = new float[shapeMasses->Length];
	Util::AsUnmanagedArray(shapeMasses, sm, shapeMasses->Length);

	PxVec3* mlp = (massLocalPose.HasValue ? &MathUtil::Vector3ToPxVec3(massLocalPose.Value) : NULL);

	bool result = PxRigidBodyExt::setMassAndUpdateInertia(*this->UnmanagedPointer, sm, shapeMasses->Length, mlp);

	delete[] sm;

	return result;
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
	PxRigidBodyExt::addLocalForceAtPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

void RigidBody::AddLocalForceAtLocalPosition(Vector3 force, Vector3 position)
{
	AddLocalForceAtLocalPosition(force, position, ForceMode::Force, true);
}
void RigidBody::AddLocalForceAtLocalPosition(Vector3 force, Vector3 position, ForceMode forceMode, bool wakeUp)
{
	PxRigidBodyExt::addLocalForceAtLocalPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(force), MathUtil::Vector3ToPxVec3(position), ToUnmanagedEnum(PxForceMode, forceMode), wakeUp);
}

Vector3 RigidBody::GetVelocityAtPosition(Vector3 position)
{
	PxVec3 v = PxRigidBodyExt::getVelocityAtPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(position));

	return MathUtil::PxVec3ToVector3(v);
}

Vector3 RigidBody::GetLocalVelocityAtLocalPosition(Vector3 position)
{
	PxVec3 v = PxRigidBodyExt::getLocalVelocityAtLocalPos(*this->UnmanagedPointer, MathUtil::Vector3ToPxVec3(position));

	return MathUtil::PxVec3ToVector3(v);
}

Vector3 RigidBody::GetVelocityAtOffset(Vector3 position)
{
	return MV(PxRigidBodyExt::getLocalVelocityAtLocalPos(*this->UnmanagedPointer, UV(position)));
}

//void RigidBody::LinearSweepSingle(BatchQuery^ batchQuery, Vector3 unitDirection, float distance, QueryFlag filterFlags)
//{
//	LinearSweepSingle(batchQuery, unitDirection, distance, filterFlags, true, nullptr, nullptr);
//}
LinearSweepSingleResult^ RigidBody::LinearSweepSingle(RigidBody^ body, PhysX::Scene^ scene, Vector3 unitDirection, float distance, HitFlag outputFlags, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCall, [Optional] QueryCache^ queryCache, [Optional] Nullable<float> inflation)
{
	ThrowIfNullOrDisposed(body, "body");
	ThrowIfNullOrDisposed(scene, "scene");

	PxQueryFilterData fd = (filterData.HasValue ? QueryFilterData::ToUnmanaged(filterData.Value) : PxQueryFilterData());

	PxHitFlags of = ToManagedEnum(PxHitFlags, outputFlags);
	PxSweepHit sh;

	PxU32 shapeIndex;

	UserQueryFilterCallback* fc = (filterCall == nullptr ? NULL : filterCall->UnmanagedPointer);

	PxQueryCache* c = (queryCache == nullptr ? NULL : &QueryCache::ToUnmanaged(queryCache));

	PxRigidBodyExt::linearSweepSingle(
		*body->UnmanagedPointer,
		*scene->UnmanagedPointer,
		UV(unitDirection), 
		distance, 
		of,
		sh, 
		shapeIndex,
		fd,
		fc, 
		c,
		inflation.GetValueOrDefault(0));

	//

	auto result = gcnew LinearSweepSingleResult();

	result->ClosestHit = SweepHit::ToManaged(sh);
	result->ShapeIndex = shapeIndex;

	return result;
}

LinearSweepMultipleResult^ RigidBody::LinearSweepMultiple(RigidBody^ body, PhysX::Scene^ scene, Vector3 unitDirection, float distance, HitFlag outputFlags, int hitBufferSize, [Optional] Nullable<QueryFilterData> filterData, [Optional] QueryFilterCallback^ filterCall, [Optional] QueryCache^ queryCache, [Optional] Nullable<float> inflation)
{
	ThrowIfNullOrDisposed(body, "body");
	ThrowIfNullOrDisposed(scene, "scene");
	if (hitBufferSize < 0)
		throw gcnew ArgumentOutOfRangeException("hitBufferSize");

	PxQueryFilterData fd = (filterData.HasValue ? QueryFilterData::ToUnmanaged(filterData.Value) : PxQueryFilterData());

	PxHitFlags of = ToManagedEnum(PxHitFlags, outputFlags);
	PxSweepHit block;

	PxSweepHit* touchHitBuffer;
	PxU32* touchHitShapeIndices;

	PxI32 blockingShapeIndex;
	bool overflow;

	UserQueryFilterCallback* fc = (filterCall == nullptr ? NULL : filterCall->UnmanagedPointer);

	PxQueryCache* c = (queryCache == nullptr ? NULL : &QueryCache::ToUnmanaged(queryCache));

	try
	{
		touchHitBuffer = new PxSweepHit[hitBufferSize];
		touchHitShapeIndices = new PxU32[hitBufferSize];

		PxRigidBodyExt::linearSweepMultiple(
			*body->UnmanagedPointer,
			*scene->UnmanagedPointer,
			UV(unitDirection), 
			distance, 
			of,
			touchHitBuffer,
			touchHitShapeIndices,
			hitBufferSize,
			block,
			blockingShapeIndex,
			overflow,
			fd,
			fc, 
			c,
			inflation.GetValueOrDefault(0));

		//

		auto result = gcnew LinearSweepMultipleResult();

		result->Hits = gcnew array<SweepHit^>(hitBufferSize);
		for (int i = 0; i < hitBufferSize; i++)
		{
			result->Hits[i] = SweepHit::ToManaged(touchHitBuffer[i]);
		}

		result->HitShapeIndices = Util::AsManagedArray<int>(touchHitShapeIndices, hitBufferSize);
		result->Block = SweepHit::ToManaged(block);
		result->BlockingShapeIndex = blockingShapeIndex;
		result->Overflow = overflow;

		return result;
	}
	finally
	{
		delete[] touchHitBuffer, touchHitShapeIndices;
		touchHitBuffer = NULL;
		touchHitShapeIndices = NULL;
	}
}

MassProperties RigidBody::ComputeMassPropertiesFromShapes(array<Shape^>^ shapes)
{
	ThrowIfNull(shapes, "shapes");

	int n = shapes->Length;

	PxShape** s = new PxShape*[n];
	for (int i = 0; i < n; i++)
	{
		PxShape* si = shapes[i]->UnmanagedPointer;

		if (si == nullptr)
			throw gcnew ArgumentException("Shapes array cannot include a null shape");

		s[i] = si;
	}

	PxMassProperties m = PxRigidBodyExt::computeMassPropertiesFromShapes(s, n);

	delete[] s;

	return MassProperties::ToManaged(m);
}

VelocityDeltaFromImpulseResult RigidBody::ComputeVelocityDeltaFromImpulse(Vector3 impulsiveForce, Vector3 impulsiveTorque)
{
	PxVec3 deltaLinearVelocity, deltaAngularVelocity;

	PxRigidBodyExt::computeVelocityDeltaFromImpulse(*this->UnmanagedPointer, UV(impulsiveForce), UV(impulsiveTorque), deltaLinearVelocity, deltaAngularVelocity);

	VelocityDeltaFromImpulseResult result;
	result.DeltaLinearVelocity = MV(deltaLinearVelocity);
	result.DeltaAngularVelocity = MV(deltaAngularVelocity);
	return result;
}
VelocityDeltaFromImpulseResult RigidBody::ComputeVelocityDeltaFromImpulse(Transform globalPose, Vector3 point, Vector3 impulse, float invMassScale, float invInertiaScale)
{
	PxVec3 deltaLinearVelocity, deltaAngularVelocity;

	PxRigidBodyExt::computeVelocityDeltaFromImpulse(
		*this->UnmanagedPointer,
		Transform::ToUnmanaged(globalPose),
		UV(point),
		UV(impulse),
		invMassScale,
		invInertiaScale,
		deltaLinearVelocity, deltaAngularVelocity);

	VelocityDeltaFromImpulseResult result;
	result.DeltaLinearVelocity = MV(deltaLinearVelocity);
	result.DeltaAngularVelocity = MV(deltaAngularVelocity);
	return result;
}

LinearAngularImpulseResult RigidBody::ComputeLinearAngularImpulse(Transform globalPose, Vector3 point, Vector3 impulse, float invMassScale, float invInertiaScale)
{
	PxVec3 linearImpulse, angularImpulse;

	PxRigidBodyExt::computeLinearAngularImpulse(
		*this->UnmanagedPointer,
		Transform::ToUnmanaged(globalPose),
		UV(point),
		UV(impulse),
		invMassScale,
		invInertiaScale,
		linearImpulse,
		angularImpulse);

	LinearAngularImpulseResult result;
	result.LinearImpulse = MV(linearImpulse);
	result.AngularImpulse = MV(angularImpulse);
	return result;
}

//

float RigidBody::MaxDepenetrationVelocity::get()
{
	return this->UnmanagedPointer->getMaxDepenetrationVelocity();
}
void RigidBody::MaxDepenetrationVelocity::set(float value)
{
	this->UnmanagedPointer->setMaxDepenetrationVelocity(value);
}

float RigidBody::MinCCDAdvanceCoefficient::get()
{
	return this->UnmanagedPointer->getMinCCDAdvanceCoefficient();
}
void RigidBody::MinCCDAdvanceCoefficient::set(float value)
{
	this->UnmanagedPointer->setMinCCDAdvanceCoefficient(value);
}

RigidBodyFlag RigidBody::RigidBodyFlags::get()
{
	return ToManagedEnum(RigidBodyFlag, this->UnmanagedPointer->getRigidBodyFlags());
}
void RigidBody::RigidBodyFlags::set(RigidBodyFlag value)
{
	this->UnmanagedPointer->setRigidBodyFlags(ToUnmanagedEnum(PxRigidBodyFlag, value));
}

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

float RigidBody::InverseMass::get()
{
	return this->UnmanagedPointer->getInvMass();
}

Vector3 RigidBody::MassSpaceInertiaTensor::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getMassSpaceInertiaTensor());
}
void RigidBody::MassSpaceInertiaTensor::set(Vector3 value)
{
	return this->UnmanagedPointer->setMassSpaceInertiaTensor(MathUtil::Vector3ToPxVec3(value));
}

Vector3 RigidBody::MassSpaceInverseInertiaTensor::get()
{
	return MV(this->UnmanagedPointer->getMassSpaceInvInertiaTensor());
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