#include "StdAfx.h"
#include "Shape.h"
#include "Actor.h"

using namespace PhysX;

Shape::Shape(PxShape* shape, PhysX::Actor^ parentActor)
{
	if (shape == NULL)
		throw gcnew ArgumentException("shape");
	ThrowIfNullOrDisposed(parentActor, "parentActor");

	_shape = shape;
	_actor = parentActor;

	ObjectTable::Add((intptr_t)_shape, this, parentActor);
}
Shape::~Shape()
{
	this->!Shape();
}
Shape::!Shape()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_shape->release();
	_shape = NULL;

	OnDisposed(this, nullptr);
}

bool Shape::Disposed::get()
{
	return _shape == NULL;
}

GeometryType Shape::Type::get()
{
	return ToManagedEnum(GeometryType, _shape->getGeometryType());
}

PhysX::Actor^ Shape::Actor::get()
{
	return _actor;
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