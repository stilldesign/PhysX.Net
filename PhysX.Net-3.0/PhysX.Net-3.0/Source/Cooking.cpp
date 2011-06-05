#include "StdAfx.h"
#include "Cooking.h"
#include "Foundation.h"
#include "TriangleMeshDesc.h"
#include "MemoryStream.h"
#include "ConvexMeshDesc.h"
#include "DeformableMeshDesc.h"
#include "MemoryStream.h"
#include <PxCooking.h> 

Cooking::Cooking(PxCooking* cooking, PhysX::Foundation^ owner)
{
	if (cooking == NULL)
		throw gcnew ArgumentNullException("cooking");
	ThrowIfNullOrDisposed(owner, "owner");

	_cooking = cooking;

	ObjectTable::Add((intptr_t)_cooking, this, owner);
}
Cooking::~Cooking()
{
	this->!Cooking();
}
Cooking::!Cooking()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_cooking->release();
	_cooking = NULL;

	OnDisposed(this, nullptr);
}

bool Cooking::Disposed::get()
{
	return _cooking == NULL;
}

bool Cooking::CookTriangleMesh(TriangleMeshDesc^ desc, System::IO::Stream^ stream)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");
	ThrowIfNull(stream, "stream");

	PxTriangleMeshDesc d = TriangleMeshDesc::ToUnmanaged(desc);

	// TODO: TriangleMeshDesc.IsValid()
	if(!d.isValid())
		throw gcnew ArgumentException("The triangle mesh description is invalid");

	MemoryStream memoryStream;
	bool result = _cooking->cookTriangleMesh(d, memoryStream);

	Util::CopyIntoStream(memoryStream, stream);

	delete[] d.points.data;
	delete[] d.triangles.data;
	delete[] d.materialIndices.data;

	return result;
}

bool Cooking::CookConvexMesh(ConvexMeshDesc^ desc, System::IO::Stream^ stream)
{
	throw gcnew NotImplementedException();
	/*ThrowIfNull(desc, "desc");
	ThrowIfNull(stream, "stream");

	MemoryStream s;
	s.storeBuffer(stream->PositionPointer, stream->Length);

	return _cooking->cookConvexMesh(ConvexMeshDesc::ToUnmanaged(desc), s);*/
}

bool Cooking::CookDeformableMesh(DeformableMeshDesc^ desc, System::IO::Stream^ stream)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");
	ThrowIfNull(stream, "stream");

	PxDeformableMeshDesc d = DeformableMeshDesc::ToUnmanaged(desc);

	// TODO: DeformableMeshDesc.IsValid()
	if(!d.isValid())
		throw gcnew ArgumentException("The deformable mesh description is invalid");

	MemoryStream memoryStream;
	bool result = _cooking->cookDeformableMesh(d, memoryStream);

	Util::CopyIntoStream(memoryStream, stream);

	delete[] d.vertices;
	delete[] d.primitives;
	delete[] d.vertexMasses;
	delete[] d.vertexFlags;

	return result;
}

CookingParams^ Cooking::Parameters::get()
{
	return CookingParams::ToManaged(_cooking->getParams());
}
void Cooking::Parameters::set(CookingParams^ value)
{
	_cooking->setParams(CookingParams::ToUnmanaged(value));
}

bool Cooking::PlatformMismatch::get()
{
	return _cooking->platformMismatch();
}

PxCooking* Cooking::UnmanagedPointer::get()
{
	return _cooking;
}