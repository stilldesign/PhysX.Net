#include "StdAfx.h"
#include "CctHit.h"
#include "Controller.h"

void CctHit::PopulateManaged(PxCCTHit* unmanaged, CctHit^ managed)
{
	if (unmanaged == NULL)
		throw gcnew ArgumentNullException("unmanaged");
	ThrowIfNull(managed, "managed");

	managed->Controller = (unmanaged->controller == NULL ? nullptr : ObjectTable::GetObject<PhysX::Controller^>((intptr_t)unmanaged->controller));
	managed->WorldPosition = MathUtil::PxExtendedVec3ToVector3(unmanaged->worldPos);
	managed->WorldNormal = MathUtil::PxVec3ToVector3(unmanaged->worldNormal);
	managed->Direction = MathUtil::PxVec3ToVector3(unmanaged->dir);
	managed->Length = unmanaged->length;
}
void CctHit::PopulateUnmanaged(PxCCTHit* unmanaged, CctHit^ managed)
{
	if (unmanaged == NULL)
		throw gcnew ArgumentNullException("unmanaged");
	ThrowIfNull(managed, "managed");

	unmanaged->controller = (managed->Controller == nullptr ? NULL : managed->Controller->UnmanagedPointer);
	unmanaged->worldPos = MathUtil::Vector3ToPxExtendedVec3(managed->WorldPosition);
	unmanaged->worldNormal = MathUtil::Vector3ToPxVec3(managed->WorldNormal);
	unmanaged->dir = MathUtil::Vector3ToPxVec3(managed->Direction);
	unmanaged->length = managed->Length;
}