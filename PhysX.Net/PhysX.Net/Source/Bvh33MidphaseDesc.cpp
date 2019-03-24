#include "StdAfx.h"
#include "Bvh33MidphaseDesc.h"

PxBVH33MidphaseDesc Bvh33MidphaseDesc::ToUnmanaged(Bvh33MidphaseDesc^ managed)
{
	PxBVH33MidphaseDesc unmanaged;
	unmanaged.meshCookingHint = ToUnmanagedEnum(PxMeshCookingHint, managed->MeshCookingHint);
	unmanaged.meshSizePerformanceTradeOff = managed->MeshSizePerformanceTradeOff;

	return unmanaged;
}
Bvh33MidphaseDesc^ Bvh33MidphaseDesc::ToManaged(PxBVH33MidphaseDesc unmanaged)
{
	auto managed = gcnew Bvh33MidphaseDesc();
	managed->MeshCookingHint = ToManagedEnum(PhysX::MeshCookingHint, unmanaged.meshCookingHint);
	managed->MeshSizePerformanceTradeOff = unmanaged.meshSizePerformanceTradeOff;

	return managed;
}

void Bvh33MidphaseDesc::SetToDefault()
{
	PxBVH33MidphaseDesc unmanaged;
	unmanaged.setToDefault();

	this->MeshCookingHint = ToManagedEnum(PhysX::MeshCookingHint, unmanaged.meshCookingHint);
	this->MeshSizePerformanceTradeOff = unmanaged.meshSizePerformanceTradeOff;
}
bool Bvh33MidphaseDesc::IsValid()
{
	return ToUnmanaged(this).isValid();
}