#include "StdAfx.h"
#include "ModifiableContact.h"

PxModifiableContact ModifiableContact::ToUnmanaged(ModifiableContact^ managed)
{
	PxModifiableContact unmanaged;

	FeatureContact::PopulateUnmanaged(managed, unmanaged);

	unmanaged.normal = MathUtil::Vector3ToPxVec3(managed->Normal);
	unmanaged.targetVel= MathUtil::Vector3ToPxVec3(managed->TargetVelocity);
	unmanaged.maxImpulse = managed->MaximumImpulse;
	unmanaged.staticFriction = managed->StaticFriction;
	unmanaged.dynamicFriction = managed->DynamicFriction;
	unmanaged.restitution = managed->Restitution;
	unmanaged.materialIndex0 = managed->MaterialIndex0;
	unmanaged.materialIndex1 = managed->MaterialIndex1;
	unmanaged.flags = managed->Flags;

	return unmanaged;
}
//ModifiableContact^ ModifiableContact::ToManaged(PxModifiableContact contact)
//{
//	auto managed = gcnew ModifiableContact();
//
//	FeatureContact::PopulateUnmanaged(managed, &unmanaged);
//
//	unmanaged.normal = MathUtil::Vector3ToPxVec3(managed->Normal);
//	unmanaged.targetVel= MathUtil::Vector3ToPxVec3(managed->TargetVelocity);
//	unmanaged.maxImpulse = managed->MaximumImpulse;
//	unmanaged.staticFriction = managed->StaticFriction;
//	unmanaged.dynamicFriction = managed->DynamicFriction;
//	unmanaged.restitution = managed->Restitution;
//	unmanaged.materialIndex0 = managed->MaterialIndex0;
//	unmanaged.materialIndex1 = managed->MaterialIndex1;
//	unmanaged.flags = managed->Flags;
//
//	return unmanaged;
//}