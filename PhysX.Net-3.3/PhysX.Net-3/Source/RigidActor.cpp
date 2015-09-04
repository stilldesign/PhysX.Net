#include "StdAfx.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Material.h"
#include "Shape.h"
#include "ShapeCreationException.h"
#include "Physics.h"
#include "RigidStatic.h"

RigidActor::RigidActor(PxRigidActor* rigidActor, PhysX::IDisposable^ owner)
	: Actor(rigidActor, owner)
{
	auto existingShapes = CreateShapesInActor(rigidActor);

	_shapes = gcnew List<Shape^>(existingShapes);
}
RigidActor::~RigidActor()
{
	this->!RigidActor();
}
RigidActor::!RigidActor()
{
	for each (auto shape in _shapes)
	{
		DetachShape(shape);
	}

	_shapes->Clear();
	_shapes = nullptr;
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

Shape^ RigidActor::CreateShape(Geometry^ geometry, Material^ material, [Optional] Nullable<Matrix> localPose)
{
	ThrowIfNull(geometry, "geometry");
	ThrowIfNullOrDisposed(material, "material");

	Matrix pose = localPose.GetValueOrDefault(Matrix::Identity);

	PxGeometry* geom = geometry->ToUnmanaged();

	PxShape* s = this->UnmanagedPointer->createShape(*geom, *material->UnmanagedPointer, MathUtil::MatrixToPxTransform(pose));

	if (s == NULL)
		throw gcnew ShapeCreationException("Failed to create shape");

	// PxGeometry instances are created when we call ToUnmanaged()
	SAFE_DELETE(geom);

	Shape^ shape = gcnew Shape(s, this);

	shape->OnDisposed += gcnew EventHandler(this, &RigidActor::OnShapeDisposed);

	_shapes->Add(shape);

	return shape;
}
void PhysX::RigidActor::OnShapeDisposed(Object ^sender, EventArgs ^e)
{
	auto shape = (PhysX::Shape^)sender;

	shape->OnDisposed -= gcnew EventHandler(this, &RigidActor::OnShapeDisposed);

	_shapes->Remove(shape);
}

void RigidActor::AttachShape(Shape^ shape)
{
	ThrowIfNullOrDisposed(shape, "shape");

	this->UnmanagedPointer->attachShape(*shape->UnmanagedPointer);
}

void RigidActor::DetachShape(Shape^ shape)
{
	DetachShape(shape, true);
}
void RigidActor::DetachShape(Shape^ shape, bool wakeOnLostTouch)
{
	ThrowIfNullOrDisposed(shape, "shape");

	this->UnmanagedPointer->detachShape(*shape->UnmanagedPointer, wakeOnLostTouch);
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

IEnumerable<Shape^>^ RigidActor::Shapes::get()
{
	return _shapes;
}

PxRigidActor* RigidActor::UnmanagedPointer::get()
{
	return (PxRigidActor*)Actor::UnmanagedPointer;
}