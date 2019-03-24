#include "StdAfx.h"
#include "Bvh34MidphaseDesc.h"

PxBVH34MidphaseDesc Bvh34MidphaseDesc::ToUnmanaged(Bvh34MidphaseDesc^ managed)
{
	PxBVH34MidphaseDesc unmanaged;
	unmanaged.numPrimsPerLeaf = managed->PrimitivesPerLeaf;

	return unmanaged;
}
Bvh34MidphaseDesc^ Bvh34MidphaseDesc::ToManaged(PxBVH34MidphaseDesc unmanaged)
{
	auto managed = gcnew Bvh34MidphaseDesc();
	managed->PrimitivesPerLeaf = unmanaged.numPrimsPerLeaf;

	return managed;
}

void Bvh34MidphaseDesc::SetToDefault()
{
	PxBVH34MidphaseDesc unmanaged;
	unmanaged.setToDefault();

	this->PrimitivesPerLeaf = unmanaged.numPrimsPerLeaf;
}
bool Bvh34MidphaseDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}