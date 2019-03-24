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
	auto existingShapes = CreateShapesInActor(rigidActor);

	_shapes = gcnew List<Shape^>(existingShapes);
}

array<Shape^>^ RigidActor::CreateShapesInActor(PxRigidActor* actor)
{
	auto managedShapes = gcnew List<Shape^>();

	int n = actor->getNbShapes();

	PxShape** shapes = new PxShape*[n];
	actor->getShapes(shapes, n);

	for (int i = 0; i < n; i++)
	{
		PxShape* shape = shapes[i];

		Shape^ s = gcnew Shape(shape, this);

		managedShapes->Add(s);
	}

	delete[] shapes;

	return managedShapes->ToArray();
}

Shape^ RigidActor::GetShape(int index)
{
	if (index < 0 || index >= _shapes->Count)
		throw gcnew ArgumentOutOfRangeException("index");

	return _shapes[index];
}

void RigidActor::AttachShape(Shape^ shape)
{
	ThrowIfNullOrDisposed(shape, "shape");

	this->UnmanagedPointer->attachShape(*shape->UnmanagedPointer);
}

//Shape^ RigidActor::CreateShape(Geometry^ geometry, Material^ material)
//{
//	ThrowIfNullOrDisposed(material, "material");
//
//	array<Material^>^ materials = { material };
//
//	return CreateShape(geometry, materials);
//}
//Shape^ RigidActor::CreateShape(Geometry^ geometry, array<Material^>^ materials)
//{
//	ThrowIfNull(geometry, "geometry");
//	ThrowIfNull(materials, "materials");
//
//	for each (auto material in materials)
//	{
//		ThrowIfNullOrDisposed(material, "materials");
//	}
//
//	//
//
//	PxGeometry* geom = geometry->ToUnmanaged();
//
//	PxMaterial** mats = new PxMaterial*[materials->Length];
//	for (size_t i = 0; i < materials->Length; i++)
//	{
//		mats[i] = materials[i]->UnmanagedPointer;
//	}
//
//	PxShape* s = this->UnmanagedPointer->create(*geom, mats, materials->Length);
//
//	if (s == NULL)
//		throw gcnew ShapeCreationException("Failed to create shape");
//
//	// PxGeometry instances are created when we call ToUnmanaged()
//	SAFE_DELETE(geom);
//
//	Shape^ shape = gcnew Shape(s, this);
//
//	shape->OnDisposed += gcnew EventHandler(this, &RigidActor::OnShapeDisposed);
//
//	_shapes->Add(shape);
//
//	OnShapeAdded(shape);
//
//	return shape;
//}

void PhysX::RigidActor::OnShapeDisposed(Object ^sender, EventArgs ^e)
{
	auto shape = (PhysX::Shape^)sender;

	shape->OnDisposed -= gcnew EventHandler(this, &RigidActor::OnShapeDisposed);

	_shapes->Remove(shape);

	OnShapeRemoved(shape);
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
	return _shapes;
}

bool RigidActor::IsDynamic::get()
{
	return IsInstanceOf<RigidDynamic^>(this);
}

PxRigidActor* RigidActor::UnmanagedPointer::get()
{
	return (PxRigidActor*)Actor::UnmanagedPointer;
}