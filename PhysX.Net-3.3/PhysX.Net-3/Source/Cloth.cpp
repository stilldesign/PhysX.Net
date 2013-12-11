#include "StdAfx.h"
#include "Cloth.h"
#include "ClothFabric.h"
#include "Bounds3.h"

Cloth::Cloth(PxCloth* cloth, PhysX::Physics^ owner)
	: Actor(cloth, owner)
{
	// Either wrap or get the managed cloth fabric instance
	PxClothFabric* fabric = cloth->getFabric();

	if (ObjectTable::Contains((intptr_t)fabric))
		_fabric = ObjectTable::GetObject<PhysX::ClothFabric^>((intptr_t)fabric);
	else
		_fabric = gcnew PhysX::ClothFabric(fabric, owner);
}

PhysX::ClothFabric^ Cloth::ClothFabric::get()
{
	return _fabric;
}

void Cloth::SetParticles(array<ClothParticle>^ currentParticles, array<ClothParticle>^ previousParticles)
{
	int particleCount = this->UnmanagedPointer->getNbParticles();

	if (currentParticles != nullptr && currentParticles->Length != particleCount)
		throw gcnew ArgumentException(String::Format("Current particles array must of length {0} to match what particles are in the cloth currently", particleCount));
	if (previousParticles != nullptr && previousParticles->Length != particleCount)
		throw gcnew ArgumentException(String::Format("Previous particles array must of length {0} to match what particles are in the cloth currently", particleCount));

	PxClothParticle* cp;
	if (currentParticles == nullptr)
	{
		cp = NULL;
	}
	else
	{
		cp = new PxClothParticle[particleCount];
		Util::AsUnmanagedArray<ClothParticle>(currentParticles, cp, particleCount);
	}

	PxClothParticle* pp;
	if (previousParticles == nullptr)
	{
		pp = NULL;
	}
	else
	{
		pp = new PxClothParticle[particleCount];
		Util::AsUnmanagedArray<ClothParticle>(previousParticles, pp, particleCount);
	}

	this->UnmanagedPointer->setParticles(cp, pp);

	delete[] cp, pp;
}

array<ClothParticleMotionConstraint>^ Cloth::GetMotionConstraints()
{
	int n = this->UnmanagedPointer->getNbMotionConstraints();
	PxClothParticleMotionConstraint* constraints = new PxClothParticleMotionConstraint[n];

	bool result = this->UnmanagedPointer->getMotionConstraints(constraints);

	try
	{
		if (!result)
			throw gcnew OperationFailedException("Failed to get motion constraints");

		return Util::AsManagedArray<ClothParticleMotionConstraint>(constraints, n);
	}
	finally
	{
		delete[] constraints;
	}
}
void Cloth::SetMotionConstraints(array<ClothParticleMotionConstraint>^ motionConstraints)
{
	if (motionConstraints == nullptr)
	{
		this->UnmanagedPointer->setMotionConstraints(NULL);
	}
	else
	{
		int particleCount = this->UnmanagedPointer->getNbParticles();

		if (motionConstraints->Length != particleCount)
			throw gcnew ArgumentException(String::Format("Motion constraints array must of length {0} to match what particles are in the cloth currently", particleCount));

		PxClothParticleMotionConstraint* c = new PxClothParticleMotionConstraint[particleCount];
		Util::AsUnmanagedArray(motionConstraints, c, particleCount);

		this->UnmanagedPointer->setMotionConstraints(c);

		delete[] c;
	}
}

array<ClothParticleSeparationConstraint>^ Cloth::GetSeparationConstraints()
{
	int n = this->UnmanagedPointer->getNbSeparationConstraints();
	PxClothParticleSeparationConstraint* c = new PxClothParticleSeparationConstraint[n];

	this->UnmanagedPointer->getSeparationConstraints(c);

	try
	{
		return Util::AsManagedArray<ClothParticleSeparationConstraint>(c, n);
	}
	finally
	{
		delete[] c;
	}
}
void Cloth::SetSeparationConstraints(array<ClothParticleSeparationConstraint>^ separationConstraints)
{
	if (separationConstraints == nullptr)
	{
		this->UnmanagedPointer->setSeparationConstraints(NULL);
	}
	else
	{
		int particleCount = this->UnmanagedPointer->getNbParticles();

		if (separationConstraints->Length != particleCount)
			throw gcnew ArgumentException(String::Format("Motion constraints array must of length {0} to match what particles are in the cloth currently", particleCount));

		PxClothParticleSeparationConstraint* c = new PxClothParticleSeparationConstraint[particleCount];

		Util::AsUnmanagedArray(separationConstraints, c, particleCount);

		this->UnmanagedPointer->setSeparationConstraints(c);

		delete[] c;
	}
}

void Cloth::ClearInterpolation()
{
	this->UnmanagedPointer->clearInterpolation();
}

array<Vector4>^ Cloth::GetParticleAccelerations()
{
	int n = this->UnmanagedPointer->getNbParticleAccelerations();
	auto a = gcnew array<Vector4>(n);
	pin_ptr<Vector4> d = &a[0];
	
	this->UnmanagedPointer->getParticleAccelerations((PxVec4*)d);

	return a;
}
array<Vector3>^ Cloth::GetParticleAccelerations3()
{
	int n = this->UnmanagedPointer->getNbParticleAccelerations();
	PxVec4* v = new PxVec4[n];
	
	this->UnmanagedPointer->getParticleAccelerations(v);

	auto v3 = gcnew array<Vector3>(n);
	for (int i = 0; i < n; i++)
	{
		v3[i].X = (v + i)->x;
		v3[i].Y = (v + i)->y;
		v3[i].Z = (v + i)->z;
	}

	return v3;
}
void Cloth::SetParticleAccelerations(array<Vector4>^ particleAccelerations)
{
	if (particleAccelerations == nullptr)
	{
		this->UnmanagedPointer->setParticleAccelerations(NULL);
	}
	else
	{
		pin_ptr<Vector4> a = &particleAccelerations[0];

		this->UnmanagedPointer->setParticleAccelerations((PxVec4*)a);
	}
}
void Cloth::SetParticleAccelerations(array<Vector3>^ particleAccelerations)
{
	if (particleAccelerations == nullptr)
	{
		this->UnmanagedPointer->setParticleAccelerations(NULL);
	}
	else
	{
		int particleCount = this->UnmanagedPointer->getNbParticles();

		if (particleAccelerations->Length != particleCount)
			throw gcnew ArgumentException(String::Format("Particle accelerations array must of length {0} to match what particles are in the cloth currently", particleCount));

		pin_ptr<Vector3> a = &particleAccelerations[0];
		PxVec3* apin = new PxVec3[particleCount];

		PxVec4* a4 = new PxVec4[particleCount];

		for (int i = 0; i < particleCount; i++)
		{
			PxVec3* q = apin + i;
			*(a4 + i) = PxVec4(q->x, q->y, q->z, 0);
		}

		this->UnmanagedPointer->setParticleAccelerations(a4);
	}
}

void Cloth::SetCollisionSpheres(array<ClothCollisionSphere>^ spheres)
{
	ThrowIfNull(spheres, "spheres");

	if (spheres->Length == 0)
	{
		this->UnmanagedPointer->setCollisionSpheres(NULL, 0);
	}
	else
	{
		pin_ptr<ClothCollisionSphere> pin = &spheres[0];
		PxClothCollisionSphere* first = (PxClothCollisionSphere*)pin;

		this->UnmanagedPointer->setCollisionSpheres(first, spheres->Length);
	}
}

void Cloth::AddCollisionPlane(ClothCollisionPlane plane)
{
	pin_ptr<ClothCollisionPlane> p = &plane;

	this->UnmanagedPointer->addCollisionPlane(*(PxClothCollisionPlane*)p);
}
void Cloth::RemoveCollisionPlane(int index)
{
	this->UnmanagedPointer->removeCollisionPlane(index);
}
void Cloth::SetCollisionPlanes(array<ClothCollisionPlane>^ planes)
{
	ThrowIfNull(planes, "planes");
	
	if (planes->Length == 0)
	{
		this->UnmanagedPointer->setCollisionPlanes(NULL, 0);
	}
	else
	{
		pin_ptr<ClothCollisionPlane> p = &planes[0];
		PxClothCollisionPlane* first = (PxClothCollisionPlane*)p;

		this->UnmanagedPointer->setCollisionPlanes(first, planes->Length);
	}
}

void Cloth::AddCollisionConvex(int mask)
{
	this->UnmanagedPointer->addCollisionConvex(mask);
}
void Cloth::RemoveCollisionConvex(int index)
{
	this->UnmanagedPointer->removeCollisionConvex(index);
}

void Cloth::SetVirtualParticles(array<int>^ triangleVertexAndWeightIndices, array<Vector3>^ triangleVertexWeightTable)
{
	ThrowIfNull(triangleVertexAndWeightIndices, "triangleVertexAndWeightIndices");
	ThrowIfNull(triangleVertexWeightTable, "triangleVertexWeightTable");

	pin_ptr<int> i = &triangleVertexAndWeightIndices[0];
	pin_ptr<Vector3> t = &triangleVertexWeightTable[0];

	this->UnmanagedPointer->setVirtualParticles
	(
		triangleVertexAndWeightIndices->Length,
		(PxU32*)i,
		triangleVertexWeightTable->Length,
		(PxVec3*)t
	);
}

array<int>^ Cloth::GetVirtualParticles()
{
	int n = this->UnmanagedPointer->getNbVirtualParticles();

	if (n == 0)
		return gcnew array<int>(0);
	
	auto vp = gcnew array<int>(n);

	pin_ptr<int> vp_pin = &vp[0];
	this->UnmanagedPointer->getVirtualParticles((PxU32*)vp_pin);

	return vp;
}

array<Vector3>^ Cloth::GetVirtualParticleWeights()
{
	int n = this->UnmanagedPointer->getNbVirtualParticleWeights();

	if (n == 0)
		return gcnew array<Vector3>(0);

	auto vpw = gcnew array<Vector3>(n);

	pin_ptr<Vector3> vpw_pin = &vpw[0];
	this->UnmanagedPointer->getVirtualParticleWeights((PxVec3*)vpw_pin);

	return vpw;
}

void Cloth::SetTargetPose(Matrix pose)
{
	this->UnmanagedPointer->setTargetPose(MathUtil::MatrixToPxTransform(pose));
}

void Cloth::WakeUp()
{
	this->UnmanagedPointer->wakeUp();
}

void Cloth::PutToSleep()
{
	this->UnmanagedPointer->putToSleep();
}

void Cloth::SetInertiaScale(float scale)
{
	this->UnmanagedPointer->setInertiaScale(scale);
}

//

int Cloth::NumberOfParticles::get()
{
	return this->UnmanagedPointer->getNbParticles();
}

int Cloth::NumberOfMotionConstraints::get()
{
	return this->UnmanagedPointer->getNbMotionConstraints();
}

int Cloth::NumberOfSeparationConstraints::get()
{
	return this->UnmanagedPointer->getNbSeparationConstraints();
}

int Cloth::NumberOfParticleAccelerations::get()
{
	return this->UnmanagedPointer->getNbParticleAccelerations();
}

int Cloth::NumberOfCollisionSpheres::get()
{
	return this->UnmanagedPointer->getNbCollisionSpheres();
}

//int Cloth::NumberOfCollisionSpherePairs::get()
//{
//	return this->UnmanagedPointer->getNbCollisionSpherePairs();
//}

int Cloth::NumberOfCollisionPlanes::get()
{
	return this->UnmanagedPointer->getNbCollisionPlanes();
}

int Cloth::NumberOfCollisionConvexes::get()
{
	return this->UnmanagedPointer->getNbCollisionConvexes();
}

int Cloth::NumberOfVirtualParticles::get()
{
	return this->UnmanagedPointer->getNbVirtualParticles();
}

int Cloth::NumberOfVirtualParticleWeights::get()
{
	return this->UnmanagedPointer->getNbVirtualParticleWeights();
}

Matrix Cloth::GlobalPose::get()
{
	return MathUtil::PxTransformToMatrix(&this->UnmanagedPointer->getGlobalPose());
}
void Cloth::GlobalPose::set(Matrix value)
{
	this->UnmanagedPointer->setGlobalPose(MathUtil::MatrixToPxTransform(value));
}

Vector3 Cloth::ExternalAcceleration::get()
{
	return MathUtil::PxVec3ToVector3(this->UnmanagedPointer->getExternalAcceleration());
}
void Cloth::ExternalAcceleration::set(Vector3 value)
{
	this->UnmanagedPointer->setExternalAcceleration(MathUtil::Vector3ToPxVec3(value));
}

Vector3 Cloth::DampingCoefficient::get()
{
	return MV(this->UnmanagedPointer->getDampingCoefficient());
}
void Cloth::DampingCoefficient::set(Vector3 value)
{
	this->UnmanagedPointer->setDampingCoefficient(UV(value));
}

float Cloth::FrictionCoefficient::get()
{
	return this->UnmanagedPointer->getFrictionCoefficient();
}
void Cloth::FrictionCoefficient::set(float value)
{
	this->UnmanagedPointer->setFrictionCoefficient(value);
}

Vector3 Cloth::LinearDragCoefficient::get()
{
	return MV(this->UnmanagedPointer->getLinearDragCoefficient());
}
void Cloth::LinearDragCoefficient::set(Vector3 value)
{
	this->UnmanagedPointer->setLinearDragCoefficient(UV(value));
}

Vector3 Cloth::AngularDragCoefficient::get()
{
	return MV(this->UnmanagedPointer->getAngularDragCoefficient());
}
void Cloth::AngularDragCoefficient::set(Vector3 value)
{
	this->UnmanagedPointer->setAngularDragCoefficient(UV(value));
}

float Cloth::CollisionMassScale::get()
{
	return this->UnmanagedPointer->getCollisionMassScale();
}
void Cloth::CollisionMassScale::set(float value)
{
	this->UnmanagedPointer->setCollisionMassScale(value);
}

float Cloth::SolverFrequency::get()
{
	return this->UnmanagedPointer->getSolverFrequency();
}
void Cloth::SolverFrequency::set(float value)
{
	this->UnmanagedPointer->setSolverFrequency(value);
}

ClothFlag Cloth::Flags::get()
{
	return ToManagedEnum(ClothFlag, this->UnmanagedPointer->getClothFlags());
}
void Cloth::Flags::set(ClothFlag value)
{
	ClothFlag currentFlags = this->Flags;

	auto diff = EnumUtil::Difference(currentFlags, value);

	for each(auto d in diff)
	{
		PxClothFlag::Enum f = (PxClothFlag::Enum)((PxU32)d->EnumInt);

		this->UnmanagedPointer->setClothFlag(f, d->Set);
	}
}

bool Cloth::IsSleeping::get()
{
	return this->UnmanagedPointer->isSleeping();
}

float Cloth::SleepLinearVelocity::get()
{
	return this->UnmanagedPointer->getSleepLinearVelocity();
}
void Cloth::SleepLinearVelocity::set(float value)
{
	this->UnmanagedPointer->setSleepLinearVelocity(value);
}

float Cloth::PreviousTimestep::get()
{
	return this->UnmanagedPointer->getPreviousTimeStep();
}

Bounds3 Cloth::WorldBounds::get()
{
	return Bounds3::FromUnmanaged(this->UnmanagedPointer->getWorldBounds());
}

ClothMotionConstraintConfig Cloth::MotionConstraintConfig::get()
{
	PxClothMotionConstraintConfig config = this->UnmanagedPointer->getMotionConstraintConfig();

	return ClothMotionConstraintConfig::ToManaged(config);
}
void Cloth::MotionConstraintConfig::set(ClothMotionConstraintConfig value)
{
	this->UnmanagedPointer->setMotionConstraintConfig(ClothMotionConstraintConfig::ToUnmanaged(value));
}

Vector3 Cloth::LinearInertiaScale::get()
{
	return MV(this->UnmanagedPointer->getLinearInertiaScale());
}
void Cloth::LinearInertiaScale::set(Vector3 value)
{
	this->UnmanagedPointer->setLinearInertiaScale(UV(value));
}

Vector3 Cloth::AngularInertiaScale::get()
{
	return MV(this->UnmanagedPointer->getAngularInertiaScale());
}
void Cloth::AngularInertiaScale::set(Vector3 value)
{
	this->UnmanagedPointer->setAngularInertiaScale(UV(value));
}

Vector3 Cloth::CentrifugalInertiaScale::get()
{
	return MV(this->UnmanagedPointer->getCentrifugalInertiaScale());
}
void Cloth::CentrifugalInertiaScale::set(Vector3 value)
{
	this->UnmanagedPointer->setCentrifugalInertiaScale(UV(value));
}


PxCloth* Cloth::UnmanagedPointer::get()
{
	return (PxCloth*)Actor::UnmanagedPointer;
}