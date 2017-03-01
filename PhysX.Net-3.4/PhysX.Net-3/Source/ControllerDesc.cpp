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
	UserData			= nullptr;
	Position			= Vector3(0, 0, 0);
	Material			= nullptr;
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
	d.contactOffset = desc->ContactOffset;
	d.stepOffset = desc->StepOffset;
	d.density = desc->Density;
	d.scaleCoeff = desc->ScaleCoefficient;
	d.nonWalkableMode = ToUnmanagedEnum(PxControllerNonWalkableMode, desc->NonWalkableMode);
	d.material = (desc->Material == nullptr ? NULL : desc->Material->UnmanagedPointer);
	d.reportCallback = (desc->ReportCallback == nullptr ? NULL : desc->ReportCallback->UnmanagedPointer);
}
void ControllerDesc::AssignToManaged(PxControllerDesc& d, ControllerDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	desc->Position = MathUtil::PxExtendedVec3ToVector3(d.position);
	desc->UpDirection = MathUtil::PxVec3ToVector3(d.upDirection);
	desc->SlopeLimit = d.slopeLimit;
	desc->ContactOffset = d.contactOffset;
	desc->StepOffset = d.stepOffset;
	desc->Density = d.density;
	desc->ScaleCoefficient = d.scaleCoeff;
	desc->NonWalkableMode = ToManagedEnum(ControllerNonWalkableMode, d.nonWalkableMode);
	desc->Material = ObjectTable::GetObject<PhysX::Material^>((intptr_t)d.material);
	desc->ReportCallback = ObjectTable::GetObject<PhysX::UserControllerHitReport^>((intptr_t)d.reportCallback);
}