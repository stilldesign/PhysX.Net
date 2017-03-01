#include "StdAfx.h"
#include "Bvh34MidphaseDesc.h"

PxBVH34MidphaseDesc Bvh34MidphaseDesc::ToUnmanaged(Bvh34MidphaseDesc^ managed)
{
	PxBVH34MidphaseDesc unmanaged;
	unmanaged.numTrisPerLeaf = managed->TrianglesPerLeaf;

	return unmanaged;
}
Bvh34MidphaseDesc^ Bvh34MidphaseDesc::ToManaged(PxBVH34MidphaseDesc unmanaged)
{
	auto managed = gcnew Bvh34MidphaseDesc();
	managed->TrianglesPerLeaf = unmanaged.numTrisPerLeaf;

	return managed;
}

void Bvh34MidphaseDesc::SetToDefault()
{
	PxBVH34MidphaseDesc unmanaged;
	unmanaged.setToDefault();

	this->TrianglesPerLeaf = unmanaged.numTrisPerLeaf;
}
bool Bvh34MidphaseDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}