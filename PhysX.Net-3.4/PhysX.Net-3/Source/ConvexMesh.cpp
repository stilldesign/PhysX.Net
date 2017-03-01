#include "StdAfx.h"
#include "ConvexMesh.h"
#include "Physics.h"
#include "HullPolygon.h"
#include "ConvexMeshMassInformation.h"
#include "Serializable.h"

ConvexMesh::ConvexMesh(PxConvexMesh* convexMesh, PhysX::Physics^ physics)
{
	if (convexMesh == NULL)
		throw gcnew ArgumentNullException("convexMesh");
	ThrowIfNull(physics, "physics");

	_convexMesh = convexMesh;
	_physics = physics;
}

ConvexMesh::~ConvexMesh()
{
	this->!ConvexMesh();
}
ConvexMesh::!ConvexMesh()
{
	OnDisposing(this, nullptr);

	if (this->Disposed)
		return;

	_convexMesh->release();
	_convexMesh = NULL;

	_physics = nullptr;

	OnDisposed(this, nullptr);
}
bool ConvexMesh::Disposed::get()
{
	return _convexMesh == NULL;
}

array<Byte>^ ConvexMesh::GetIndexBuffer()
{
	auto ib = _convexMesh->getIndexBuffer();

	if (ib == NULL)
		return nullptr;

	return Util::AsManagedArray<Byte>((void*)ib, _convexMesh->getNbPolygons());
}

ConvexMeshMassInformation^ ConvexMesh::GetMassInformation()
{
	float mass;
	PxMat33 localInertia;
	PxVec3 localCenterOfMass;

	_convexMesh->getMassInformation(mass, localInertia, localCenterOfMass);

	auto info = gcnew ConvexMeshMassInformation();
		info->Mass = mass;
		info->LocalInertia = MathUtil::PxMat33ToMatrix(&localInertia);
		info->LocalCenterOfMass = MathUtil::PxVec3ToVector3(localCenterOfMass);

	return info;
}

Serializable^ ConvexMesh::AsSerializable()
{
	return gcnew Serializable(_convexMesh);
}

PhysX::Physics^ ConvexMesh::Physics::get()
{
	return _physics;
}

array<Vector3>^ ConvexMesh::GetVertices()
{
	return Util::AsManagedArray<Vector3>((void*)_convexMesh->getVertices(), _convexMesh->getNbVertices());
}
int ConvexMesh::NumberOfVertices::get()
{
	return _convexMesh->getNbVertices();
}

HullPolygon^ ConvexMesh::GetPolygonData(int index)
{
	PxHullPolygon p;
	_convexMesh->getPolygonData(index, p);

	return HullPolygon::ToManaged(p);
}
int ConvexMesh::NumberOfPolygons::get()
{
	return _convexMesh->getNbPolygons();
}

int ConvexMesh::ReferenceCount::get()
{
	return _convexMesh->getReferenceCount();
}


PxConvexMesh* ConvexMesh::UnmanagedPointer::get()
{
	return _convexMesh;
}