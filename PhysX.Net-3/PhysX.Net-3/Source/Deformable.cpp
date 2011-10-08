#include "StdAfx.h"
#include "Deformable.h"
#include "Physics.h"
#include "DeformableMesh.h"
#include "Bounds3.h"
#include "FilterData.h"

Deformable::Deformable(PxDeformable* deformable, PhysX::DeformableMesh^ deformableMesh, PhysX::Physics^ owner)
	: Actor(deformable, owner)
{
	//ThrowIfNullOrDisposed(deformableMesh, "deformableMesh");

	_deformableMesh = deformableMesh;
}
Deformable::~Deformable()
{
	this->!Deformable();
}
Deformable::!Deformable()
{
	
}

//

bool Deformable::TearVertex(int vertexId, Vector3 normal)
{
	return this->UnmanagedPointer->tearVertex(vertexId, MathUtil::Vector3ToPxVec3(normal));
}

Nullable<int> Deformable::Raycast(Vector3 rayOrigin, Vector3 rayDirection, Vector3 hit)
{
	PxU32 v;
	bool result = this->UnmanagedPointer->raycast(MathUtil::Vector3ToPxVec3(rayOrigin), MathUtil::Vector3ToPxVec3(rayDirection), MathUtil::Vector3ToPxVec3(hit), v);

	if (!result)
		return Nullable<int>();

	return Nullable<int>(v);
}

void Deformable::SetPositions(array<Vector3>^ positions, [Optional] array<int>^ indices)
{
	auto p = (PxVec3*)malloc(sizeof(PxVec3) * positions->Length);
	Util::AsUnmanagedArray(positions, (void*)p, positions->Length);
	auto pIter = PxStrideIterator<PxVec3>(p);

	PxStrideIterator<PxU32> iIter;
	PxU32* i = NULL;
	if (indices != nullptr)
	{
		i = (PxU32*)malloc(sizeof(PxU32) * indices->Length);
		Util::AsUnmanagedArray(indices, (void*)i, indices->Length);
		iIter = PxStrideIterator<PxU32>(i);
	}

	this->UnmanagedPointer->setPositions(positions->Length, pIter, iIter);

	free(p);
	if (i)
		free(i);
}

void Deformable::SetVelocities(array<Vector3>^ velocities, [Optional] array<int>^ indices)
{

}

void Deformable::SetConstrainPositins(array<Vector3>^ positions)
{

}

void Deformable::SetConstrainNormals(array<Vector3>^ normals)
{

}

void Deformable::SetConstrainCoefficients(array<DeformableConstrainCoefficients^>^ coefficients)
{

}

void Deformable::WakeUp([Optional] Nullable<float> wakeCounterValue)
{
	this->UnmanagedPointer->wakeUp(wakeCounterValue.GetValueOrDefault(PX_SLEEP_INTERVAL));
}

void Deformable::PutToSleep()
{
	this->UnmanagedPointer->putToSleep();
}

void Deformable::ResetFiltering()
{
	this->UnmanagedPointer->resetFiltering();
}

void Deformable::AddForces(array<Vector3>^ forces, ForceMode mode, [Optional] array<int>^ indices)
{

}

DeformableReadData^ Deformable::LockDeformableReadData()
{
	return nullptr;
}

DeformableDesc^ Deformable::SaveToDesc()
{
	return nullptr;
}

//

PhysX::DeformableMesh^ Deformable::DeformableMesh::get()
{
	return _deformableMesh;
}

float Deformable::BendingStiffness::get()
{
	return this->UnmanagedPointer->getBendingStiffness();
}
void Deformable::BendingStiffness::set(float value)
{
	this->UnmanagedPointer->setBendingStiffness(value);
}

float Deformable::VolumeStiffness::get()
{
	return this->UnmanagedPointer->getVolumeStiffness();
}
void Deformable::VolumeStiffness::set(float value)
{
	this->UnmanagedPointer->setVolumeStiffness(value);
}

float Deformable::StretchingStiffness::get()
{
	return this->UnmanagedPointer->getStretchingStiffness();
}
void Deformable::StretchingStiffness::set(float value)
{
	this->UnmanagedPointer->setStretchingStiffness(value);
}

float Deformable::DampingCoefficient::get()
{
	return this->UnmanagedPointer->getDampingCoefficient();
}
void Deformable::DampingCoefficient::set(float value)
{
	this->UnmanagedPointer->setDampingCoefficient(value);
}

float Deformable::StaticFriction::get()
{
	return this->UnmanagedPointer->getStaticFriction();
}
void Deformable::StaticFriction::set(float value)
{
	this->UnmanagedPointer->setStaticFriction(value);
}

float Deformable::DynamicFriction::get()
{
	return this->UnmanagedPointer->getDynamicFriction();
}
void Deformable::DynamicFriction::set(float value)
{
	this->UnmanagedPointer->setDynamicFriction(value);
}

float Deformable::Pressure::get()
{
	return this->UnmanagedPointer->getPressure();
}
void Deformable::Pressure::set(float value)
{
	this->UnmanagedPointer->setPressure(value);
}

float Deformable::TearFactor::get()
{
	return this->UnmanagedPointer->getTearFactor();
}
void Deformable::TearFactor::set(float value)
{
	this->UnmanagedPointer->setTearFactor(value);
}

float Deformable::AttachmentTearFactor::get()
{
	return this->UnmanagedPointer->getAttachmentTearFactor();
}
void Deformable::AttachmentTearFactor::set(float value)
{
	this->UnmanagedPointer->setAttachmentTearFactor(value);
}

float Deformable::Mass::get()
{
	return this->UnmanagedPointer->getMass();
}
float Deformable::RelativeGridSpacing::get()
{
	return this->UnmanagedPointer->getRelativeGridSpacing();
}
int Deformable::SolverIterations::get()
{
	return this->UnmanagedPointer->getSolverIterations();
}
void Deformable::SolverIterations::set(int value)
{
	this->UnmanagedPointer->setSolverIterations(value);
}

int Deformable::HierarchicalSolverIterations::get()
{
	return this->UnmanagedPointer->getHierarchicalSolverIterations();
}
void Deformable::HierarchicalSolverIterations::set(int value)
{
	this->UnmanagedPointer->setHierarchicalSolverIterations(value);
}

Bounds3 Deformable::WorldBounds::get()
{
	return Bounds3::FromUnmanaged(this->UnmanagedPointer->getWorldBounds());
}

Bounds3 Deformable::ValidBounds::get()
{
	return Bounds3::FromUnmanaged(this->UnmanagedPointer->getValidBounds());
}
void Deformable::ValidBounds::set(Bounds3 value)
{
	this->UnmanagedPointer->setValidBounds(Bounds3::ToUnmanaged(value));
}

int Deformable::NumberOfVertices::get()
{
	return this->UnmanagedPointer->getNumVertices();
}
int Deformable::MaximumVertices::get()
{
	return this->UnmanagedPointer->getMaxVertices();
}
float Deformable::CollisionStiffness::get()
{
	return this->UnmanagedPointer->getCollisionStiffness();
}
void Deformable::CollisionStiffness::set(float value)
{
	this->UnmanagedPointer->setCollisionStiffness(value);
}

float Deformable::AttachmentStiffness::get()
{
	return this->UnmanagedPointer->getAttachmentStiffness();
}
void Deformable::AttachmentStiffness::set(float value)
{
	this->UnmanagedPointer->setAttachmentStiffness(value);
}

float Deformable::ContactOffset::get()
{
	return this->UnmanagedPointer->getContactOffset();
}
void Deformable::ContactOffset::set(float value)
{
	this->UnmanagedPointer->setContactOffset(value);
}

float Deformable::RestOffset::get()
{
	return this->UnmanagedPointer->getRestOffset();
}
void Deformable::RestOffset::set(float value)
{
	this->UnmanagedPointer->setRestOffset(value);
}

float Deformable::PenetrationOffset::get()
{
	return this->UnmanagedPointer->getPenetrationOffset();
}
void Deformable::PenetrationOffset::set(float value)
{
	this->UnmanagedPointer->setPenetrationOffset(value);
}

float Deformable::SelfCollisionOffset::get()
{
	return this->UnmanagedPointer->getSelfCollisionOffset();
}
void Deformable::SelfCollisionOffset::set(float value)
{
	this->UnmanagedPointer->setSelfCollisionOffset(value);
}

Vector3 Deformable::ExternalAcceleration::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getExternalAcceleration());
}
void Deformable::ExternalAcceleration::set(Vector3 value)
{
	this->UnmanagedPointer->setExternalAcceleration(MathUtil::Vector3ToPxVec3(value));
}

Vector3 Deformable::WindAcceleration::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getWindAcceleration());
}
void Deformable::WindAcceleration::set(Vector3 value)
{
	this->UnmanagedPointer->setWindAcceleration(MathUtil::Vector3ToPxVec3(value));
}

bool Deformable::IsSleeping::get()
{
	return this->UnmanagedPointer->isSleeping();
}

float Deformable::SleepLinearVelocity::get()
{
	return this->UnmanagedPointer->getSleepLinearVelocity();
}
void Deformable::SleepLinearVelocity::set(float value)
{
	this->UnmanagedPointer->setSleepLinearVelocity(value);
}

FilterData Deformable::SimulationFilterData::get()
{
	return FilterData::ToManaged(this->UnmanagedPointer->getSimulationFilterData());
}
void Deformable::SimulationFilterData::set(FilterData value)
{
	this->UnmanagedPointer->setSimulationFilterData(FilterData::ToUnmanaged(value));
}

DeformableFlag Deformable::DeformableFlags::get()
{
	return ToManagedEnum(DeformableFlag, this->UnmanagedPointer->getDeformableFlags());
}
void Deformable::DeformableFlags::set(DeformableFlag value)
{
	throw gcnew NotImplementedException();
}

PxDeformable* Deformable::UnmanagedPointer::get()
{
	return (PxDeformable*)Actor::UnmanagedPointer;
}