#include "StdAfx.h"
#include "Cooking.h"
#include "Foundation.h"
#include "TriangleMeshDesc.h"
#include "ConvexMeshDesc.h"
#include "HeightFieldDesc.h"

Cooking::Cooking(PxCooking* cooking, PhysX::Foundation^ owner)
{
	if (cooking == NULL)
		throw gcnew ArgumentNullException("cooking");
	ThrowIfNullOrDisposed(owner, "owner");

	_cooking = cooking;

	ObjectTable::Instance->Add((intptr_t)_cooking, this, owner);
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

bool Cooking::CookHeightField(HeightFieldDesc^ desc, System::IO::Stream^ stream)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");
	ThrowIfNull(stream, "stream");

	PxHeightFieldDesc d = HeightFieldDesc::ToUnmanaged(desc);

	if (!d.isValid())
		throw gcnew ArgumentException("The height field description is invalid");

	PxDefaultMemoryOutputStream cookedStream;
	bool result = _cooking->cookHeightField(d, cookedStream);

	// Copy the cooked data into the managed stream (only if the cooked stream actually has data)
	if (result)
		Util::CopyIntoStream(&cookedStream, stream);

	delete[] d.samples.data;

	return result;
}
TriangleMeshCookingResult Cooking::CookTriangleMesh(TriangleMeshDesc^ desc, System::IO::Stream^ stream)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");
	ThrowIfNull(stream, "stream");

	PxTriangleMeshDesc d = TriangleMeshDesc::ToUnmanaged(desc);

	if(!d.isValid())
		throw gcnew ArgumentException("The triangle mesh description is invalid");

	PxTriangleMeshCookingResult::Enum result;
	PxDefaultMemoryOutputStream cookedStream;

	_cooking->cookTriangleMesh(d, cookedStream, &result);

	// Copy the cooked data into the managed stream (only if the cooked stream actually has data)
	if (result == PxTriangleMeshCookingResult::eSUCCESS)
		Util::CopyIntoStream(&cookedStream, stream);

	delete[] d.points.data;
	delete[] d.triangles.data;
	delete[] d.materialIndices.data;

	return ToManagedEnum(TriangleMeshCookingResult, result);
}

ConvexMeshCookingResult Cooking::CookConvexMesh(ConvexMeshDesc^ desc, System::IO::Stream^ stream)
{
	ThrowIfDescriptionIsNullOrInvalid(desc, "desc");
	ThrowIfNull(stream, "stream");

	PxConvexMeshDesc d = ConvexMeshDesc::ToUnmanaged(desc);

	if(!d.isValid())
		throw gcnew ArgumentException("The convex mesh description is invalid");

	PxConvexMeshCookingResult::Enum result;

	PxDefaultMemoryOutputStream cookedStream;
	_cooking->cookConvexMesh(d, cookedStream, &result);

	// Copy the cooked data into the managed stream (only if the cooked stream actually has data)
	if (result == PxConvexMeshCookingResult::eSUCCESS)
		Util::CopyIntoStream(&cookedStream, stream);

	delete[] d.points.data;
	delete[] d.polygons.data;

	return ToManagedEnum(ConvexMeshCookingResult, result);
}

//

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