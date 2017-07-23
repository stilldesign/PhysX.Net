#include "StdAfx.h"
#include "ControllerDesc.h"
#include "Material.h"
#include "FilterData.h"
#include "UserControllerHitReport.h"
#include "ControllerBehaviorCallback.h"

ControllerDesc::ControllerDesc(ControllerShapeType type)
{
	_type = type;

	SetToDefault();
}

ControllerShapeType ControllerDesc::Type::get()
{
	return _type;
}

void ControllerDesc::AssignToUnmanaged(ControllerDesc^ desc, PxControllerDesc& d)
{
	ThrowIfNull(desc, "desc");

	d.position = MathUtil::Vector3ToPxExtendedVec3(desc->Position);
	d.upDirection = MathUtil::Vector3ToPxVec3(desc->UpDirection);
	d.slopeLimit = desc->SlopeLimit;
	d.invisibleWallHeight = desc->InvisibleWallHeight;
	d.maxJumpHeight = desc->MaxJumpHeight;
	d.contactOffset = desc->ContactOffset;
	d.stepOffset = desc->StepOffset;
	d.density = desc->Density;
	d.scaleCoeff = desc->ScaleCoefficient;
	d.volumeGrowth = desc->VolumeGrowth;
	d.nonWalkableMode = ToUnmanagedEnum(PxControllerNonWalkableMode, desc->NonWalkableMode);
	d.material = (desc->Material == nullptr ? NULL : desc->Material->UnmanagedPointer);
	d.reportCallback = (desc->ReportCallback == nullptr ? NULL : desc->ReportCallback->UnmanagedPointer);
	d.behaviorCallback = GetPointerOrNull(desc->BehaviorCallback);
}
void ControllerDesc::AssignToManaged(PxControllerDesc& d, ControllerDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	desc->Position = MathUtil::PxExtendedVec3ToVector3(d.position);
	desc->UpDirection = MathUtil::PxVec3ToVector3(d.upDirection);
	desc->SlopeLimit = d.slopeLimit;
	desc->InvisibleWallHeight = d.invisibleWallHeight;
	desc->MaxJumpHeight = d.maxJumpHeight;
	desc->ContactOffset = d.contactOffset;
	desc->StepOffset = d.stepOffset;
	desc->Density = d.density;
	desc->ScaleCoefficient = d.scaleCoeff;
	desc->VolumeGrowth = d.volumeGrowth;
	desc->NonWalkableMode = ToManagedEnum(ControllerNonWalkableMode, d.nonWalkableMode);
	desc->Material = ObjectTable::Instance->GetObject<PhysX::Material^>((intptr_t)d.material);
	desc->ReportCallback = ObjectTable::Instance->GetObject<PhysX::UserControllerHitReport^>((intptr_t)d.reportCallback);
	desc->BehaviorCallback = ObjectTable::Instance->TryGetObject<PhysX::ControllerBehaviorCallback^>((intptr_t)d.behaviorCallback);
}