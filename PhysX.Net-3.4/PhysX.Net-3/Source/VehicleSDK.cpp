#include "StdAfx.h"
#include "VehicleSDK.h"
#include "Physics.h"
#include "VehicleSDKNotInitializedException.h"
#include "VehicleWheelsSimData.h"
#include "VehicleDriveSimData4W.h"
#include "VehicleWheels.h"
#include "RaycastQueryResult.h"
#include "BatchQuery.h"
#include "VehicleWheelsDynData.h"
#include "VehicleConcurrentUpdateData.h"

VehicleSDK::VehicleSDK(PhysX::Physics^ physics)
{
	ThrowIfNullOrDisposed(physics, "physics");

	_physics = physics;

	ObjectTable::Instance->AddObjectOwner(this, physics);
}
VehicleSDK::~VehicleSDK()
{
	this->!VehicleSDK();
}
VehicleSDK::!VehicleSDK()
{
	if (this->Disposed)
		return;

	Close();

	_physics = nullptr;
}
bool VehicleSDK::Disposed::get()
{
	return (_physics == nullptr);
}

void VehicleSDK::EnsureInitalized()
{
	if (!_initalized)
		throw gcnew VehicleSDKNotInitializedException("The vehicle SDK has not been initalized. Call Physics::VehicleSDK::Initalize() before any vehicle related methods.");
}

bool VehicleSDK::Initalize()
{
	bool initalized = PxInitVehicleSDK(*_physics->UnmanagedPointer);

	if (initalized)
		_initalized = true;

	return initalized;
}
void VehicleSDK::Close()
{
	if (_initalized)
		PxCloseVehicleSDK();
}

void VehicleSDK::Vehicle4WEnable3WDeltaMode(VehicleWheelsSimData^ suspensionWheelTireData, VehicleWheelsDynData^ wheelsDynData, VehicleDriveSimData4W^ coreData)
{
	throw gcnew NotImplementedException();
	//PxVehicle4WEnable3WDeltaMode(
	//	*suspensionWheelTireData->UnmanagedPointer, 
	//	*coreData->UnmanagedPointer);
}

void VehicleSDK::Vehicle4WEnable3WTadpoleMode(VehicleWheelsSimData^ suspWheelTireData, VehicleWheelsDynData^ wheelsDynData, VehicleDriveSimData4W^ coreData)
{
	throw gcnew NotImplementedException();
	//PxVehicle4WEnable3WTadpoleMode(*suspWheelTireData->UnmanagedPointer, wheelsDynData, *coreData->UnmanagedPointer);
}

void VehicleSDK::VehicleComputeTireForceDefault(float tireFriction, float longSlip, float latSlip, float camber,
	float wheelOmega, float wheelRadius, float recipWheelRadius, float restTireLoad, float normalisedTireLoad,
	float tireLoad, float gravity, float recipGravity, float wheelTorque, float tireLongForceMag,
	float tireLatForceMag, float tireAlignMoment)
{
	throw gcnew NotImplementedException();
}

void VehicleSDK::VehicleSetBasisVectors(Vector3 up, Vector3 forward)
{
	PxVehicleSetBasisVectors(UV(up), UV(forward));
}

void VehicleSDK::VehicleSuspensionRaycasts(BatchQuery^ batchQuery, array<VehicleWheels^>^ vehicles, array<RaycastQueryResult^>^ sceneQueryResults)
{
	ThrowIfNull(batchQuery, "batchQuery");
	ThrowIfNull(vehicles, "vehicles");
	ThrowIfNull(sceneQueryResults, "sceneQueryResults");

	PxVehicleWheels** v = new PxVehicleWheels*[vehicles->Length];
	for (int i = 0; i < vehicles->Length; i++)
	{
		v[i] = vehicles[i]->UnmanagedPointer;
	}

	PxRaycastQueryResult* r = new PxRaycastQueryResult[sceneQueryResults->Length];
	for (int i = 0; i < sceneQueryResults->Length; i++)
	{
		PxRaycastQueryResult result = RaycastQueryResult::ToUnmanaged(sceneQueryResults[i]);

		r[i] = result;
	}

	PxVehicleSuspensionRaycasts(batchQuery->UnmanagedPointer, vehicles->Length, v, sceneQueryResults->Length, r);

	//

	for (int i = 0; i < sceneQueryResults->Length; i++)
	{
		delete r[i].touches;
	}

	delete[] r;
	delete[] v;
}

//void VehicleSDK::VehiclePostUpdates(VehicleConcurrentUpdateData^ concurrentUpdateData, array<VehicleWheels^>^ vehicles)
//{
//
//}

VehicleWheels^ VehicleSDK::VehicleUpdateCMassLocalPose(Matrix oldCMassLocalPose, Matrix newCMassLocalPose, VehicleGravityDirection gravityDirection, VehicleWheels^ vehicle)
{
	ThrowIfNullOrDisposed(vehicle, "vehicle");

	PxVehicleWheels* w = vehicle->UnmanagedPointer;

	PxVehicleUpdateCMassLocalPose
	(
		MathUtil::MatrixToPxTransform(oldCMassLocalPose),
		MathUtil::MatrixToPxTransform(newCMassLocalPose),
		(int)gravityDirection,
		w
	);

	// The fourth parameter is [in, out], se we'll find the managed object it represents
	auto outWheel = ObjectTable::Instance->GetObject<VehicleWheels^>((intptr_t)w);

	return outWheel;
}

//

PhysX::Physics^ VehicleSDK::Physics::get()
{
	return _physics;
}