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
	throw gcnew NotImplementedException();
	/*ThrowIfNull(desc, "desc");
	ThrowIfNull(stream, "stream");

	MemoryStream s;
	s.storeBuffer(stream->PositionPointer, stream->Length);

	return _cooking->cookTriangleMesh(TriangleMeshDesc::ToUnmanaged(desc), s);*/
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
	if (desc == nullptr)
		throw gcnew ArgumentNullException("desc");
	//if (!desc->IsValid())
	//	throw gcnew ArgumentException("Description is invalid");

	if (stream == nullptr)
		throw gcnew ArgumentNullException("stream");
	if (!stream->CanWrite)
		throw gcnew ArgumentException("Stream is not writable", "stream");

	if (_cooking == NULL)
		throw gcnew InvalidOperationException("The cooking library has not been initialized");

	auto d = DeformableMeshDesc::ToUnmanaged(desc);

	bool valid = d.isValid();

	MemoryStream ms;
	auto s = ms.GetMemory();

	if (ms.getMemorySize() > 0xFFFFFFFF)
		throw gcnew OutOfMemoryException("Trying to allocation too much memory");

	bool result = _cooking->cookDeformableMesh(d, ms);

	if (!result)
		return false;

	int m = (int)ms.getMemorySize();

	array<Byte>^ data = gcnew array<Byte>((int)ms.getMemorySize());
	pin_ptr<Byte> b = &data[0];
	memcpy_s(b, m, ms.GetMemory(), m);

	stream->Write(data, 0, m);

	return true;
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