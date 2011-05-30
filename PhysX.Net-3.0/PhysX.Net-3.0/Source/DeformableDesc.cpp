#include "StdAfx.h"
#include "DeformableDesc.h"
#include "ActorDesc.h"
#include "DeformableMesh.h"

DeformableDesc::DeformableDesc([Optional] Nullable<TolerancesScale> scale)
	: ActorDesc(ActorType::Deformable)
{
	SetToDefault();
}

void DeformableDesc::SetToDefault()
{
	this->ValidBounds = Bounds3::Extremes;
	this->DeformableMesh = nullptr;
	this->GlobalPose = Matrix::Identity;
	this->Mass = 0.0f;	
	this->BendingStiffness = 1.0f;
	this->VolumeStiffness = 1.0f;
	this->StretchingStiffness = 1.0f;
	this->DampingCoefficient = 0.0f;
	this->StaticFriction = 0.2f;
	this->DynamicFriction = 0.2f;
	this->Pressure = 1.0f;
	this->TearFactor = 1.5f;
	this->AttachmentTearFactor = 1.5f;
	this->AttachmentStiffness = 1.0f;
	this->CollisionStiffness = 0.6f;
	this->RestOffset = 0.01f;
	this->ContactOffset = 0.02f;
	this->PenetrationOffset = -0.05f;
	this->SelfCollisionOffset = 0.02f;
	this->DeformableFlags = DeformableFlag::VolumeConservation;
	this->DeformableReadDataFlags = DeformableReadDataFlag::PositionBuffer | DeformableReadDataFlag::NormalBuffer;
	this->SolverIterations = 5;
	this->HierarchicalSolverIterations = 2;
	this->WakeUpCounter = PX_SLEEP_INTERVAL;
	this->SleepLinearVelocity = -1.0f;
	this->ExternalAcceleration = Vector3(0.0f, 0.0f, 0.0f);
	this->WindAcceleration = Vector3(0.0f, 0.0f, 0.0f);
	this->RelativeGridSpacing = 0.4f;
	this->SimulationFilterData = FilterData();
	this->MaximumPrimitiveSplitPairs = 0;
	this->SleepLinearVelocity = 0.15f;
}
bool DeformableDesc::IsValid()
{
	auto d = ToUnmanaged(this);

	return d.isValid();
}

PxDeformableDesc DeformableDesc::ToUnmanaged(DeformableDesc^ desc)
{
	PxDeformableDesc d = PxDeformableDesc(PxTolerancesScale());
	
	desc->PopulateUnmanaged(d);

	d.attachmentStiffness = desc->AttachmentStiffness;
	d.attachmentTearFactor = desc->AttachmentTearFactor;
	d.bendingStiffness = desc->BendingStiffness;
	d.collisionStiffness = desc->CollisionStiffness;
	d.contactOffset = desc->ContactOffset;
	d.dampingCoefficient = desc->DampingCoefficient;
	d.deformableFlags = ToUnmanagedEnum(PxDeformableFlag, desc->DeformableFlags);
	d.deformableMesh = GetPointerOrNull(desc->DeformableMesh);
	d.deformableReadDataFlags = ToUnmanagedEnum(PxDeformableReadDataFlag, desc->DeformableReadDataFlags);
	d.dynamicFriction = desc->DynamicFriction;
	d.externalAcceleration = MathUtil::Vector3ToPxVec3(desc->ExternalAcceleration);
	d.globalPose = MathUtil::MatrixToPxTransform(desc->GlobalPose);
	d.hierarchicalSolverIterations = desc->HierarchicalSolverIterations;
	d.mass = desc->Mass;
	d.maxPrimitiveSplitPairs = desc->MaximumPrimitiveSplitPairs;
	d.maxVertices = desc->MaximumVertices;
	d.penetrationOffset = desc->PenetrationOffset;
	d.pressure = desc->Pressure;
	d.relativeGridSpacing = desc->RelativeGridSpacing;
	d.restOffset = desc->RestOffset;
	d.simulationFilterData = FilterData::ToUnmanaged(desc->SimulationFilterData);
	d.sleepLinearVelocity = desc->SleepLinearVelocity;
	d.solverIterations = desc->SolverIterations;
	d.staticFriction = desc->StaticFriction;
	d.stretchingStiffness = desc->StretchingStiffness;
	d.validBounds = Bounds3::ToUnmanaged(desc->ValidBounds);
	d.volumeStiffness = desc->VolumeStiffness;

	return d;
}
DeformableDesc^ DeformableDesc::ToManaged(PxDeformableDesc desc)
{
	DeformableDesc^ d = gcnew DeformableDesc(Nullable<TolerancesScale>());

	d->PopulateManaged(desc);

	d->AttachmentStiffness = desc.attachmentStiffness;
	d->AttachmentTearFactor = desc.attachmentTearFactor;
	d->BendingStiffness = desc.bendingStiffness;
	d->CollisionStiffness = desc.collisionStiffness;
	d->ContactOffset = desc.contactOffset;
	d->DampingCoefficient = desc.dampingCoefficient;
	d->DeformableFlags = ToManagedEnum(DeformableFlag, desc.deformableFlags);
	d->DeformableMesh = ObjectTable::GetObject<PhysX::DeformableMesh^>((intptr_t)desc.deformableMesh);
	d->DeformableReadDataFlags = ToManagedEnum(DeformableReadDataFlag, desc.deformableReadDataFlags);
	d->DynamicFriction = desc.dynamicFriction;
	d->ExternalAcceleration = MathUtil::PxVec3ToVector3(desc.externalAcceleration);
	d->GlobalPose = MathUtil::PxTransformToMatrix(&desc.globalPose);
	d->HierarchicalSolverIterations = desc.hierarchicalSolverIterations;
	d->Mass = desc.mass;
	d->MaximumPrimitiveSplitPairs = desc.maxPrimitiveSplitPairs;
	d->MaximumVertices = desc.maxVertices;
	d->PenetrationOffset = desc.penetrationOffset;
	d->Pressure = desc.pressure;
	d->RelativeGridSpacing = desc.relativeGridSpacing;
	d->RestOffset = desc.restOffset;
	d->SimulationFilterData = FilterData::ToManaged(desc.simulationFilterData);
	d->SleepLinearVelocity = desc.sleepLinearVelocity;
	d->SolverIterations = desc.solverIterations;
	d->StaticFriction = desc.staticFriction;
	d->StretchingStiffness = desc.stretchingStiffness;
	d->ValidBounds = Bounds3::FromUnmanaged(desc.validBounds);
	d->VolumeStiffness = desc.volumeStiffness;

	return d;
}