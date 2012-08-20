#include "StdAfx.h"
#include "Shape.h"
#include "Actor.h"
#include "Geometry.h"
#include "SphereGeometry.h"
#include "Serializable.h"
#include "BoxGeometry.h"
#include "SphereGeometry.h"
#include "CapsuleGeometry.h"
#include "PlaneGeometry.h"
#include "ConvexMeshGeometry.h"
#include "TriangleMeshGeometry.h"
#include "HeightFieldGeometry.h"
#include <PxGeometryHelpers.h>
#include <PxShapeExt.h>

using namespace PhysX;
using namespace System::Runtime::InteropServices;

Shape::Shape(PxShape* shape, PhysX::Actor^ parentActor)
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
	_shape->getBoxGeometry(box);

	return BoxGeometry::ToManaged(box);
}
SphereGeometry^ Shape::GetSphereGeometry()
{
	PxSphereGeometry sphere;
	_shape->getSphereGeometry(sphere);

	return SphereGeometry::ToManaged(sphere);
}
CapsuleGeometry^ Shape::GetCapsuleGeometry()
{
	PxCapsuleGeometry capsule;
	_shape->getCapsuleGeometry(capsule);

	return CapsuleGeometry::ToManaged(capsule);
}
PlaneGeometry^ Shape::GetPlaneGeometry()
{
	PxPlaneGeometry plane;
	_shape->getPlaneGeometry(plane);

	return PlaneGeometry::ToManaged(plane);
}
ConvexMeshGeometry^ Shape::GetConvexMeshGeometry()
{
	PxConvexMeshGeometry convexMesh;
	_shape->getConvexMeshGeometry(convexMesh);

	return ConvexMeshGeometry::ToManaged(convexMesh);
}
TriangleMeshGeometry^ Shape::GetTriangleMeshGeometry()
{
	PxTriangleMeshGeometry triangleMesh;
	_shape->getTriangleMeshGeometry(triangleMesh);

	return TriangleMeshGeometry::ToManaged(triangleMesh);
}
HeightFieldGeometry^ Shape::GetHeightFieldGeometry()
{
	PxHeightFieldGeometry heightField;
	_shape->getHeightFieldGeometry(heightField);

	return HeightFieldGeometry::ToManaged(heightField);
}

//

PhysX::GeometryType Shape::GeometryType::get()
{
	return ToManagedEnum(PhysX::GeometryType, _shape->getGeometryType());
}

PhysX::Actor^ Shape::Actor::get()
{
	return _actor;
}

Matrix Shape::GlobalPose::get()
{
	return MathUtil::PxTransformToMatrix(&PxShapeExt::getGlobalPose(*_shape));
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
	return Bounds3::FromUnmanaged(_shape->getWorldBounds());
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