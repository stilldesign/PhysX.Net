#include "StdAfx.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Material.h"
#include "Shape.h"
#include "ShapeCreationException.h"
#include "Physics.h"
#include "RigidStatic.h"
#include "RigidDynamic.h"

RigidActor::RigidActor(PxRigidActor* rigidActor, PhysX::IDisposable^ owner)
	: Actor(rigidActor, owner)
{
	
}

List<Shape^>^ RigidActor::GetOrCreateShapesOfActor(PxRigidActor* actor)
{
	auto managedShapes = gcnew List<Shape^>();

	int n = actor->getNbShapes();

	PxShape** shapes = new PxShape*[n];
	actor->getShapes(shapes, n);

	for (int i = 0; i < n; i++)
	{
		PxShape* shape = shapes[i];

		// Try to get the existing managed Shape instance, or create a new one
		// if it doesn't already exist
		Shape^ managedShape = ObjectTable::Instance->TryGetObject<Shape^>((intptr_t)shape);
		if (managedShape == nullptr)
			managedShape = gcnew Shape(shape, this);

		managedShapes->Add(managedShape);
	}

	delete[] shapes;

	return managedShapes;
}

Shape^ RigidActor::GetShape(int index)
{
	if (index < 0 || index >= this->Shapes->Count)
		throw gcnew ArgumentOutOfRangeException("index");

	return this->Shapes[index];
}

void RigidActor::AttachShape(Shape^ shape)
{
	ThrowIfNullOrDisposed(shape, "shape");

	this->UnmanagedPointer->attachShape(*shape->UnmanagedPointer);
}

void RigidActor::Scale(float scale)
{
	Scale(scale, true);
}
void RigidActor::Scale(float scale, bool scaleMassProperties)
{
	PxScaleRigidActor(*this->UnmanagedPointer, scale, scaleMassProperties);
}

RigidStatic^ RigidActor::CloneStatic(Matrix transform)
{
	PxRigidStatic* rigidStatic = PxCloneStatic(
		*this->Physics->UnmanagedPointer, 
		MathUtil::MatrixToPxTransform(transform),
		*this->UnmanagedPointer);

	return gcnew RigidStatic(rigidStatic, this->Physics);
}

Matrix RigidActor::GlobalPose::get()
{
	return MathUtil::PxTransformToMatrix(&this->UnmanagedPointer->getGlobalPose());
}
void RigidActor::GlobalPose::set(Matrix value)
{
	return this->UnmanagedPointer->setGlobalPose(MathUtil::MatrixToPxTransform(value));
}

Vector3 RigidActor::GlobalPosePosition::get()
{
	return MV(this->UnmanagedPointer->getGlobalPose().p);
}
void RigidActor::GlobalPosePosition::set(Vector3 value)
{
	PxTransform t = this->UnmanagedPointer->getGlobalPose();
	t.p = UV(value);

	this->UnmanagedPointer->setGlobalPose(t);
}
Quaternion RigidActor::GlobalPoseQuat::get()
{
	return MathUtil::PxQuatToQuaternion(this->UnmanagedPointer->getGlobalPose().q);
}
void RigidActor::GlobalPoseQuat::set(Quaternion value)
{
	PxTransform t = this->UnmanagedPointer->getGlobalPose();
	t.q = MathUtil::QuaternionToPxQuat(value);

	this->UnmanagedPointer->setGlobalPose(t);
}

IReadOnlyList<Shape^>^ RigidActor::Shapes::get()
{
	return GetOrCreateShapesOfActor(this->UnmanagedPointer);
}

bool RigidActor::IsDynamic::get()
{
	return IsInstanceOf<RigidDynamic^>(this);
}

PxRigidActor* RigidActor::UnmanagedPointer::get()
{
	return (PxRigidActor*)Actor::UnmanagedPointer;
}