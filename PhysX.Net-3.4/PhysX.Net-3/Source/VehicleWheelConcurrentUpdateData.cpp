#include "StdAfx.h"
#include "VehicleWheelConcurrentUpdateData.h"
#include "RigidDynamic.h"

//PxVehicleWheelConcurrentUpdateData VehicleWheelConcurrentUpdateData::ToUnmanaged(VehicleWheelConcurrentUpdateData^ managed)
//{
//	PxVehicleWheelConcurrentUpdateData unmanaged;
//
//	unmanaged.localPose = MathUtil::MatrixToPxTransform(managed->LocalPose);
//	unmanaged.hitActor = managed->HitActor == nullptr ? NULL : managed->HitActor->UnmanagedPointer;
//	unmanaged.hitActorForce = UV(managed->HitActorForce);
//	unmanaged.hitActorForcePosition = UV(managed->HitActorForcePosition);
//
//	return unmanaged;
//}