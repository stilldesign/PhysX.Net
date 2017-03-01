#include "StdAfx.h"
#include "MidphaseDesc.h"
#include "Bvh33MidphaseDesc.h"
#include "Bvh34MidphaseDesc.h"

PxMidphaseDesc MidphaseDesc::ToUnmanaged(MidphaseDesc^ managed)
{
	PxMidphaseDesc unmanaged;
	
	if (managed->Bvh33Desc != nullptr)
		unmanaged.mBVH33Desc = Bvh33MidphaseDesc::ToUnmanaged(managed->Bvh33Desc);
	else if (managed->Bvh34Desc != nullptr)
		unmanaged.mBVH34Desc = Bvh34MidphaseDesc::ToUnmanaged(managed->Bvh34Desc);

	return unmanaged;
}
MidphaseDesc^ MidphaseDesc::ToManaged(PxMidphaseDesc unmanaged)
{
	auto managed = gcnew MidphaseDesc();

	switch (unmanaged.getType())
	{
	case PxMeshMidPhase::eBVH33:
		managed->Bvh33Desc = Bvh33MidphaseDesc::ToManaged(unmanaged.mBVH33Desc);
		break;
	case PxMeshMidPhase::eBVH34:
		managed->Bvh34Desc = Bvh34MidphaseDesc::ToManaged(unmanaged.mBVH34Desc);
		break;
	}

	return managed;
}

bool MidphaseDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}

Nullable<MeshMidPhase> MidphaseDesc::Type::get()
{
	if (Bvh33Desc != nullptr)
		return MeshMidPhase::BoundingVolumeHierarchy33;
	else if (Bvh34Desc != nullptr)
		return MeshMidPhase::BoundingVolumeHierarchy34;
	else
		return Nullable<MeshMidPhase>();
}