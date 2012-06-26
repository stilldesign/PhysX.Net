#include "StdAfx.h"
#include "ClothCollisionData.h"

PxClothCollisionData ClothCollisionData::ToUnmanaged(ClothCollisionData^ data)
{
	ThrowIfNull(data, "data");

	PxClothCollisionData d;

	if (data->Spheres != nullptr && data->Spheres->Length > 0)
	{
		pin_ptr<ClothCollisionSphere> s = &data->Spheres[0];

		d.numSpheres = data->Spheres->Length;
		d.spheres = (PxClothCollisionSphere*)s;
	}
	else
	{
		d.numSpheres = 0;
		d.spheres = NULL;
	}

	if (data->PairIndices != nullptr && data->PairIndices->Length > 0)
	{
		pin_ptr<int> p = &data->PairIndices[0];

		d.numPairs = data->PairIndices->Length;
		d.pairIndexBuffer = (PxU32*)p;
	}
	else
	{
		d.numPairs = 0;
		d.pairIndexBuffer = NULL;
	}

	return d;
}

void ClothCollisionData::SetToDefault()
{
	this->Spheres = nullptr;
	this->PairIndices = nullptr;
}
bool ClothCollisionData::IsValid()
{
	return ToUnmanaged(this).isValid();
}