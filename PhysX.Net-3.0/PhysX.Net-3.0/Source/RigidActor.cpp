#include "StdAfx.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Material.h"
#include "Shape.h"
#include "ShapeCreationException.h"
#include <PxRigidActor.h>
#include <PxShape.h>
#include <PxBoxGeometry.h>

RigidActor::RigidActor(PxRigidActor* rigidActor, PhysX::Physics^ owner)
	: Actor(rigidActor, owner)
{
	_shapes = gcnew List<Shape^>();
}
RigidActor::~RigidActor()
{
	
}
RigidActor::!RigidActor()
{
	
}

Shape^ RigidActor::CreateShape(Geometry^ geometry, Material^ material, [Optional] Nullable<Matrix> localPose)
{
	ThrowIfNull(geometry, "geometry");
	ThrowIfNullOrDisposed(material, "material");

	Matrix pose = localPose.GetValueOrDefault(Matrix::Identity);

	PxGeometry* geom = geometry->ToUnmanaged();

	PxShape* s = this->UnmanagedPointer->createShape(*geom, *material->UnmanagedPointer, MathUtil::MatrixToPxTransform(pose));

	if (s == NULL)
		throw gcnew ShapeCreationException("Failed to create shape");

	//delete geom;

	Shape^ shape = gcnew Shape(s, this);

	_shapes->Add(shape);

	return shape;
}

Matrix RigidActor::GlobalPose::get()
{
	return MathUtil::PxTransformToMatrix(&this->UnmanagedPointer->getGlobalPose());
}
void RigidActor::GlobalPose::set(Matrix value)
{
	return this->UnmanagedPointer->setGlobalPose(MathUtil::MatrixToPxTransform(value));
}

IEnumerable<Shape^>^ RigidActor::Shapes::get()
{
	return _shapes;
}

PxRigidActor* RigidActor::UnmanagedPointer::get()
{
	return (PxRigidActor*)Actor::UnmanagedPointer;
}