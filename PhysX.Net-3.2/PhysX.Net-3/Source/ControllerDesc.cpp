#include "StdAfx.h"
#include "ControllerDesc.h"
#include "Material.h"
#include "FilterData.h"
#include "UserControllerHitReport.h"

ControllerDesc::ControllerDesc(ControllerShapeType type)
{
	_type = type;

	SetToDefault();
}

void ControllerDesc::SetToDefault()
{
	UpDirection			= Vector3(0.0f, 1.0f, 0.0f);
	SlopeLimit			= 0.707f;
	ContactOffset		= 0.1f;
	StepOffset			= 0.5f;
	Density				= 10.0f;
	ScaleCoefficient	= 0.8f;
	VolumeGrowth		= 1.5f;
	Callback			= nullptr;
	//BehaviorCallback	= nullptr;
	UserData			= nullptr;
	InteractionMode		= CCTInteractionMode::Include;
	NonWalkableMode		= CCTNonWalkableMode::PreventClimbing;
	GroupsBitmask		= 0xffffffff;
	Position			= Vector3(0, 0, 0);
	Material			= nullptr;
	InvisibleWallHeight	= 0.0f;
	MaximumJumpHeight	= 0.0f;
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
	d.maxJumpHeight = desc->MaximumJumpHeight;
	d.contactOffset = desc->ContactOffset;
	d.stepOffset = desc->StepOffset;
	d.density = desc->Density;
	d.scaleCoeff = desc->ScaleCoefficient;
	d.volumeGrowth = desc->VolumeGrowth;
	d.callback = (desc->Callback == nullptr ? NULL : desc->Callback->UnmanagedPointer);
	d.interactionMode = ToUnmanagedEnum(PxCCTInteractionMode, desc->InteractionMode);
	d.nonWalkableMode = ToUnmanagedEnum(PxCCTNonWalkableMode, desc->NonWalkableMode);
	d.groupsBitmask = desc->GroupsBitmask;
	d.material = (desc->Material == nullptr ? NULL : desc->Material->UnmanagedPointer);
}
void ControllerDesc::AssignToManaged(PxControllerDesc& d, ControllerDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	desc->Position = MathUtil::PxExtendedVec3ToVector3(d.position);
	desc->UpDirection = MathUtil::PxVec3ToVector3(d.upDirection);
	desc->SlopeLimit = d.slopeLimit;
	desc->InvisibleWallHeight = d.invisibleWallHeight;
	desc->MaximumJumpHeight = d.maxJumpHeight;
	desc->ContactOffset = d.contactOffset;
	desc->StepOffset = d.stepOffset;
	desc->Density = d.density;
	desc->ScaleCoefficient = d.scaleCoeff;
	desc->VolumeGrowth = d.volumeGrowth;
	// TODO: ControllerDesc.Callback to unmanaged
	//desc->Callback = 
	desc->InteractionMode = ToManagedEnum(CCTInteractionMode, d.interactionMode);
	desc->NonWalkableMode = ToManagedEnum(CCTNonWalkableMode, d.nonWalkableMode);
	desc->GroupsBitmask = d.groupsBitmask;
	desc->Material = ObjectTable::GetObject<PhysX::Material^>((intptr_t)d.material);
}