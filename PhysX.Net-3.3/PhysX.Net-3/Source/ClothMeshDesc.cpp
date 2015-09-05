#include "StdAfx.h"
#include "ClothMeshDesc.h"

ClothMeshDesc::ClothMeshDesc()
{

}

PxClothMeshDesc ClothMeshDesc::ToUnmanaged(ClothMeshDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	int indexStride = desc->Flags.HasFlag(MeshFlag::Indices16Bit) ? sizeof(short) : sizeof(int);

	// Points
	PxBoundedData points;
	if (desc->Points != nullptr)
	{
		points.count = desc->Points->Length;
		points.stride = MathUtil::Vector3SizeInBytes;

		points.data = new BYTE[points.count * points.stride];
		Util::AsUnmanagedArray(desc->Points, (void*)points.data);
	}

	PxBoundedData quads;
	if (desc->Quads != nullptr)
	{
		quads.count = desc->Quads->Length;
		quads.stride = indexStride*4;

		quads.data = new BYTE[quads.count * quads.stride];
		Util::AsUnmanagedArray(desc->Quads, (void*)quads.data);
	}

	PxBoundedData triangles;
	if (desc->Triangles != nullptr)
	{
		triangles.count = (desc->Triangles->Length / indexStride) / 3;
		triangles.stride = indexStride*3; // 3 indices per triangle

		triangles.data = new BYTE[triangles.count * triangles.stride];
		Util::AsUnmanagedArray(desc->Triangles, (void*)triangles.data);
	}

	PxBoundedData invMasses;
	if (desc->InverseMasses != nullptr)
	{
		// The number of inverse masses must be the same as the number of points.
		if (desc->InverseMasses->Length != desc->Points->Length)
			throw gcnew ArgumentException("The length of InverseMasses must equal the length of Points, or be null");

		invMasses.count = desc->InverseMasses->Length;
		invMasses.stride = sizeof(float);
		invMasses.data = new float[invMasses.count * invMasses.stride];
		Util::AsUnmanagedArray(desc->InverseMasses, (void*)invMasses.data);
	}

	PxClothMeshDesc d;
		d.points = points;
		d.invMasses = invMasses;
		d.triangles = triangles;
		d.quads = quads;
		d.flags = ToUnmanagedEnum(PxMeshFlag, desc->Flags);

	return d;
}

void ClothMeshDesc::SetToDefault()
{
	Points = nullptr;
	InverseMasses = nullptr;
	Quads = nullptr;
	Triangles = nullptr;
	Flags = (MeshFlag)0;
}
bool ClothMeshDesc::IsValid()
{
	// TODO: Do I copy into a temp unmanaged var and call isValid(), or copy-paste the code into here, either way is stupid
	return ToUnmanaged(this).isValid();
}

array<short>^ ClothMeshDesc::GetQuads16()
{
	return Util::CopyToValueTypeArray<short>(this->Quads);
}
array<int>^ ClothMeshDesc::GetQuads32()
{
	return Util::CopyToValueTypeArray<int>(this->Quads);
}

array<short>^ ClothMeshDesc::GetTriangles16()
{
	return Util::CopyToValueTypeArray<short>(this->Triangles);
}
array<int>^ ClothMeshDesc::GetTriangles32()
{
	return Util::CopyToValueTypeArray<int>(this->Triangles);
}