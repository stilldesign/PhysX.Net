#include "StdAfx.h"
#include "ControllerDesc.h"
#include "Material.h"
#include "FilterData.h"

ControllerDesc::ControllerDesc(ControllerShapeType type)
{
	_type = type;
}

ControllerShapeType ControllerDesc::Type::get()
{
	return _type;
}

void ControllerDesc::AssignToUnmanaged(ControllerDesc^ desc, PxControllerDesc& d)
{
	ThrowIfNull(desc, "desc");

	//d->callback = desc->Callback;
	d.contactOffset = desc->ContactOffset;
	//d.controllerSimulationFilterData = FilterData::ToUnmanaged(desc->ControllerSimulationFilterData);
	d.interactionMode = ToUnmanagedEnum(PxCCTInteractionMode, desc->InteractionMode);
	d.material = (desc->Material == nullptr ? NULL : desc->Material->UnmanagedPointer);
	d.position = MathUtil::Vector3ToPxExtendedVec3(desc->Position);
	//d.globalPose = MathUtil::MatrixToPxTransform(desc->GlobalPose);
	d.slopeLimit = desc->SlopeLimit;
	d.stepOffset = desc->StepOffset;
	d.upDirection = MathUtil::Vector3ToPxVec3(desc->UpDirection);
}
void ControllerDesc::AssignToManaged(PxControllerDesc& d, ControllerDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	//d->callback = desc->Callback;
	desc->ContactOffset = d.contactOffset;
	//desc->ControllerSimulationFilterData = FilterData::ToManaged(d.controllerSimulationFilterData);
	desc->InteractionMode = ToManagedEnum(CCTInteractionMode, d.interactionMode);
	desc->Material = ObjectTable::GetObject<PhysX::Material^>((intptr_t)d.material);
	desc->Position = MathUtil::PxExtendedVec3ToVector3(d.position);
	desc->SlopeLimit = d.slopeLimit;
	desc->StepOffset = d.stepOffset;
	desc->UpDirection = MathUtil::PxVec3ToVector3(d.upDirection);
}