#include "StdAfx.h"
#include "Shape.h"
#include "Actor.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Serializable.h"
#include "BoxGeometry.h"
#include "SphereGeometry.h"
#include "CapsuleGeometry.h"
#include "PlaneGeometry.h"
#include "ConvexMeshGeometry.h"
#include "TriangleMeshGeometry.h"
#include "HeightFieldGeometry.h"
#include "ShapeUtil.h"
//#include <PxShapeExt.h>

Shape::Shape(PxShape* shape, PhysX::RigidActor^ parentActor)
{
	if (shape == NULL)
		throw gcnew ArgumentException("shape");
	ThrowIfNullOrDisposed(parentActor, "parentActor");

	_shape = shape;
	_actor = parentActor;

	ObjectTable::Add((intptr_t)_shape, this, parentActor);

	this->UnmanagedOwner = true;
}
Shape::~Shape()
{
	this->!Shape();
}
Shape::!Shape()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	// TODO: What does it mean to Dispose a Shape which is used on multiple Actors?
	// Should be using _actor->detachShape(...)
	if (this->UnmanagedOwner)
		_shape->release();

	_shape = NULL;

	OnDisposed(this, nullptr);
}

bool Shape::Disposed::get()
{
	return (_shape == NULL);
}

Serializable^ Shape::AsSerializable()
{
	return gcnew Serializable(_shape);
}

BoxGeometry^ Shape::GetBoxGeometry()
{
	PxBoxGeometry box;
	if (!_shape->getBoxGeometry(box))
		return nullptr;

	return BoxGeometry::ToManaged(box);
}
SphereGeometry^ Shape::GetSphereGeometry()
{
	PxSphereGeometry sphere;
	if (!_shape->getSphereGeometry(sphere))
		return nullptr;

	return SphereGeometry::ToManaged(sphere);
}
CapsuleGeometry^ Shape::GetCapsuleGeometry()
{
	PxCapsuleGeometry capsule;
	if (!_shape->getCapsuleGeometry(capsule))
		return nullptr;

	return CapsuleGeometry::ToManaged(capsule);
}
PlaneGeometry^ Shape::GetPlaneGeometry()
{
	PxPlaneGeometry plane;
	if (!_shape->getPlaneGeometry(plane))
		return nullptr;

	return PlaneGeometry::ToManaged(plane);
}
ConvexMeshGeometry^ Shape::GetConvexMeshGeometry()
{
	PxConvexMeshGeometry convexMesh;
	if (!_shape->getConvexMeshGeometry(convexMesh))
		return nullptr;

	return ConvexMeshGeometry::ToManaged(convexMesh);
}
TriangleMeshGeometry^ Shape::GetTriangleMeshGeometry()
{
	PxTriangleMeshGeometry triangleMesh;
	if (!_shape->getTriangleMeshGeometry(triangleMesh))
		return nullptr;

	return TriangleMeshGeometry::ToManaged(triangleMesh);
}
HeightFieldGeometry^ Shape::GetHeightFieldGeometry()
{
	PxHeightFieldGeometry heightField;
	if (!_shape->getHeightFieldGeometry(heightField))
		return nullptr;

	return HeightFieldGeometry::ToManaged(heightField);
}

Material^ Shape::GetMaterialFromInternalFaceIndex(int faceIndex)
{
	PxMaterial* material = _shape->getMaterialFromInternalFaceIndex(faceIndex);

	if (material == NULL)
		return nullptr;

	return ObjectTable::GetObject<Material^>((intptr_t)material);
}

//

PhysX::GeometryType Shape::GeometryType::get()
{
	return ToManagedEnum(PhysX::GeometryType, _shape->getGeometryType());
}

PhysX::RigidActor^ Shape::Actor::get()
{
	return _actor;
}

Matrix Shape::GlobalPose::get()
{
	PxRigidActor* actor = _shape->getActor();

	if (actor == NULL)
		throw gcnew InvalidOperationException("The shape is attached to more than one actor. Use Shape.GetGlobalPose(actor) instead.");

	return MathUtil::PxTransformToMatrix(&PxShapeExt::getGlobalPose(*_shape, *actor));
}

String^ Shape::Name::get()
{
	return Util::ToManagedString(_shape->getName());
}
void Shape::Name::set(String^ value)
{
	if (_shape->getName() != NULL)
		Marshal::FreeHGlobal(IntPtr((char*)_shape->getName()));

	_shape->setName(Util::ToUnmanagedString(value));
}

Bounds3 Shape::WorldBounds::get()
{
	PxBounds3 bounds = ShapeUtil::GetWorldBoundsUnmanaged(_shape, _actor->UnmanagedPointer);

	return Bounds3::ToManaged(bounds);
}

float Shape::ContactOffset::get()
{
	return _shape->getContactOffset();
}
void Shape::ContactOffset::set(float value)
{
	_shape->setContactOffset(value);
}

float Shape::RestOffset::get()
{
	return _shape->getRestOffset();
}
void Shape::RestOffset::set(float value)
{
	_shape->setRestOffset(value);
}

ShapeFlag Shape::Flags::get()
{
	return ToManagedEnum(ShapeFlag, _shape->getFlags());
}
void Shape::Flags::set(ShapeFlag value)
{
	_shape->setFlags((PxShapeFlags)(PxU32)value);
}

Matrix Shape::LocalPose::get()
{
	return MathUtil::PxTransformToMatrix(&_shape->getLocalPose());
}
void Shape::LocalPose::set(Matrix value)
{
	_shape->setLocalPose(MathUtil::MatrixToPxTransform(value));
}

PxShape* Shape::UnmanagedPointer::get()
{
	return _shape;
}