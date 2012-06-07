#include "StdAfx.h"
#include "Vehicle4W.h"
#include "Physics.h"
#include "Vehicle4WSetupDesc.h"
#include "Geometry.h"
#include "RigidDynamic.h"
#include "Vehicle4WSimulationData.h"
#include "Material.h"
#include "VehicleSuspensionRaycastResult.h"

Vehicle4W::Vehicle4W(PxVehicle4W* vehicle, PhysX::Physics^ owner)
{
	if (vehicle == NULL)
		throw gcnew ArgumentNullException("vehicle");
	ThrowIfNullOrDisposed(owner, "owner");

	_vehicle = vehicle;
	_physics = owner;

	ObjectTable::Add((intptr_t)_vehicle, this, owner);
}
Vehicle4W::~Vehicle4W()
{
	this->!Vehicle4W();
}
Vehicle4W::!Vehicle4W()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_vehicle = NULL;
	_physics = nullptr;

	OnDisposed(this, nullptr);
}

bool Vehicle4W::Disposed::get()
{
	return _vehicle == NULL;
}

PhysX::Physics^ Vehicle4W::Physics::get()
{
	return _physics;
}

void Vehicle4W::Initalize(PhysX::Physics^ physics)
{
	ThrowIfNullOrDisposed(physics, "physics");

	PxInitVehicles(*physics->UnmanagedPointer);
}
Vehicle4W^ Vehicle4W::Setup(Vehicle4WSetupDesc^ description)
{
	ThrowIfNull(description, "description");

	auto simData = Vehicle4WSimulationData::ToUnmanaged(description->SimulationData);
	auto qryFilterData = FilterData::ToUnmanaged(description->VehicleQueryFilterData);
	auto wheelCollFilterData = FilterData::ToUnmanaged(description->WheelCollisionFilterData);

	PxGeometry** geometries = new PxGeometry*[description->Geometries->Length];
	PxTransform* transforms = new PxTransform[description->Geometries->Length];
	for (int i = 0; i < description->Geometries->Length; i++)
	{
		geometries[i] = description->Geometries[i]->ChassisGeometry->ToUnmanaged();
		transforms[i] = MathUtil::MatrixToPxTransform(description->Geometries[i]->ChassisLocalPose);
	}
	
	PxGeometry& fl = *description->FrontLeftWheelGeometry->ToUnmanaged();
	PxGeometry& fr = *description->FrontRightWheelGeometry->ToUnmanaged();
	PxGeometry& rl = *description->RearLeftWheelGeometry->ToUnmanaged();
	PxGeometry& rr = *description->RearRightWheelGeometry->ToUnmanaged();

	auto vehActor = GetPointerOrNull(description->VehicleActor);

	auto wheelMat = description->WheelMaterial->UnmanagedPointer;
	auto chasMat = description->ChassisMaterial->UnmanagedPointer;
	auto chasCollFilterData = FilterData::ToUnmanaged(description->ChassisCollisionFilterData);

	//

	PxVehicle4W* vehicle = NULL;
	
	PxVehicle4WSetup
	(
		simData,
		qryFilterData,
		vehActor,
		fl, fr, rl, rr,
		wheelMat,
		wheelCollFilterData,
		(PxGeometry* const*)geometries,
		transforms,
		description->Geometries->Length,
		chasMat,
		chasCollFilterData,
		description->Physics->UnmanagedPointer,
		vehicle
	);

	delete &fl;
	delete &fr;
	delete &rl;
	delete &rr;

	return gcnew Vehicle4W(vehicle, description->Physics);
}

FilterData Vehicle4W::SetupVehicleShapeQueryFilterData(int vehicleIndex)
{
	PxFilterData fd;
	PxSetupVehicleShapeQueryFilterData(vehicleIndex, &fd);

	return FilterData::ToManaged(fd);
}

void Vehicle4W::SetAnalogInputs(float acceleration, float brake, float handbrake, float steer, bool gearup, bool geardown)
{
	PxVehicle4WSetAnalogInputs(acceleration, brake, handbrake, steer, gearup, geardown, *_vehicle);
}

void Vehicle4W::StartGearChange(int targetGear)
{
	PxVehicle4WStartGearChange(targetGear, *_vehicle);
}

void Vehicle4W::ForceGearChange(int targetGear)
{
	PxVehicle4WForceGearChange(targetGear, *_vehicle);
}

float Vehicle4W::ComputeForwardSpeed()
{
	return PxVehicle4WComputeForwardSpeed(*_vehicle);
}

float Vehicle4W::ComputeSidewaysSpeed()
{
	return PxVehicle4WComputeSidewaysSpeed(*_vehicle);
}

void Vehicle4W::SetToRestState()
{
	PxVehicle4WSetToRestState(*_vehicle);
}

array<Shape^>^ Vehicle4W::GetChassisShapes()
{
	int numOfShapes = PxVehicle4WGetNumChassisShapes(*_vehicle);

	PxShape** chassisShapes = new PxShape*[numOfShapes];
	PxVehicle4WGetChassisShapes(*_vehicle, chassisShapes, numOfShapes);

	array<Shape^>^ cs = gcnew array<Shape^>(numOfShapes);
	for (int i = 0; i < numOfShapes; i++)
	{
		cs[i] = ObjectTable::GetObject<Shape^>((intptr_t)chassisShapes[i]);
	}

	return cs;
}

float Vehicle4W::GetWheelRotationSpeed(int wheelIndex)
{
	return PxVehicle4WGetWheelRotationSpeed(*_vehicle, wheelIndex);
}

float Vehicle4W::GetWheelRotationAngle(int wheelIndex)
{
return PxVehicle4WGetWheelRotationAngle(*_vehicle, wheelIndex);
}

float Vehicle4W::GetSuspensionJounce(int suspensionIndex)
{
	return PxVehicle4WGetSuspJounce(*_vehicle, suspensionIndex);
}

float Vehicle4W::GetTyreLongSlip(int tyreIndex)
{
	return PxVehicle4WGetTyreLongSlip(*_vehicle, tyreIndex);
}

float Vehicle4W::GetTyreLaterialSlip(int tyreIndex)
{
	return PxVehicle4WGetTyreLatSlip(*_vehicle, tyreIndex);
}

float Vehicle4W::GetTyreFriction(int tyreIndex)
{
	return PxVehicle4WGetTyreFriction(*_vehicle, tyreIndex);
}

int Vehicle4W::GetTyreDrivableSurfaceType(int tyreIndex)
{
	return PxVehicle4WGetTyreDrivableSurfaceType(*_vehicle, tyreIndex);
}

VehicleSuspensionRaycastResult^ Vehicle4W::GetSuspensionRaycast(int suspensionIndex)
{
	PxVec3 start;
	PxVec3 dir;
	float length;

	PxVehicle4WGetSuspRaycast(*_vehicle, suspensionIndex, start, dir, length);

	auto result = gcnew VehicleSuspensionRaycastResult();
		result->Start = MathUtil::PxVec3ToVector3(start);
		result->Direction = MathUtil::PxVec3ToVector3(dir);
		result->Length = length;

	return result;
}

//

bool Vehicle4W::UseAutoGears::get()
{
	return _vehicle->mUseAutoGears;
}
void Vehicle4W::UseAutoGears::set(bool value)
{
	_vehicle->mUseAutoGears = value;
}

bool Vehicle4W::GearUpPressed::get()
{
	return _vehicle->mGearUpPressed;
}
void Vehicle4W::GearUpPressed::set(bool value)
{
	_vehicle->mGearUpPressed = value;
}

bool Vehicle4W::GearDownPressed::get()
{
	return _vehicle->mGearDownPressed;
}
void Vehicle4W::GearDownPressed::set(bool value)
{
	_vehicle->mGearDownPressed = value;
}

int Vehicle4W::CurrentGear::get()
{
	return _vehicle->mCurrentGear;
}
void Vehicle4W::CurrentGear::set(int value)
{
	_vehicle->mCurrentGear = value;
}

int Vehicle4W::TargetGear::get()
{
	return _vehicle->mTargetGear;
}
void Vehicle4W::TargetGear::set(int value)
{
	_vehicle->mTargetGear = value;
}

array<float>^ Vehicle4W::InternalDynamics::get()
{
	return Util::AsManagedArray<float>(_vehicle->mInternalDynamics, PxVehicle4WSimulationData::eNUM_WHEELS + 1);
}
void Vehicle4W::InternalDynamics::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mInternalDynamics, PxVehicle4WSimulationData::eNUM_WHEELS + 1);
}

array<float>^ Vehicle4W::TyreLowForwardSpeedTimers::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mTyreLowForwardSpeedTimers, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TyreLowForwardSpeedTimers::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreLowForwardSpeedTimers, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::WheelRotationAngles::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mWheelRotationAngles, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::WheelRotationAngles::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mWheelRotationAngles, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::SuspensionJounces::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mSuspJounces, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionJounces::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspJounces, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::LongitudinalSlips::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mLongSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::LongitudinalSlips::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mLongSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::LaterialSlips::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mLatSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::LaterialSlips::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mLatSlips, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::TypeFrictions::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mTyreFrictions, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TypeFrictions::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreFrictions, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<int>^ Vehicle4W::TyreSurfaceTypes::get()
{
	return Util::AsManagedArray<int>(&_vehicle->mTyreSurfaceTypes, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::TyreSurfaceTypes::set(array<int>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mTyreSurfaceTypes, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<Vector3>^ Vehicle4W::SuspensionLineStarts::get()
{
	return Util::AsManagedArray<Vector3>(&_vehicle->mSuspLineStarts, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineStarts::set(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineStarts, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<Vector3>^ Vehicle4W::SuspensionLineDirections::get()
{
	return Util::AsManagedArray<Vector3>(&_vehicle->mSuspLineDirs, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineDirections::set(array<Vector3>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineDirs, PxVehicle4WSimulationData::eNUM_WHEELS);
}

array<float>^ Vehicle4W::SuspensionLineLengths::get()
{
	return Util::AsManagedArray<float>(&_vehicle->mSuspLineLengths, PxVehicle4WSimulationData::eNUM_WHEELS);
}
void Vehicle4W::SuspensionLineLengths::set(array<float>^ value)
{
	Util::AsUnmanagedArray(value, _vehicle->mSuspLineLengths, PxVehicle4WSimulationData::eNUM_WHEELS);
}

float Vehicle4W::GearSwitchTime::get()
{
	return _vehicle->mGearSwitchTime;
}
void Vehicle4W::GearSwitchTime::set(float value)
{
	_vehicle->mGearSwitchTime = value;
}

float Vehicle4W::AutoBoxSwitchTime::get()
{
	return _vehicle->mAutoBoxSwitchTime;
}
void Vehicle4W::AutoBoxSwitchTime::set(float value)
{
	_vehicle->mAutoBoxSwitchTime = value;
}

float Vehicle4W::AppliedAcceleration::get()
{
	return PxVehicle4WGetAppliedAccel(*_vehicle);
}

float Vehicle4W::AppliedBrake::get()
{
	return PxVehicle4WGetAppliedBrake(*_vehicle);
}

float Vehicle4W::AppliedHandbrake::get()
{
	return PxVehicle4WGetAppliedHandbrake(*_vehicle);
}

float Vehicle4W::AppliedSteer::get()
{
	return PxVehicle4WGetAppliedSteer(*_vehicle);
}

bool Vehicle4W::AppliedGearup::get()
{
	return PxVehicle4WGetAppliedGearup(*_vehicle);
}

bool Vehicle4W::AppliedGeardown::get()
{
	return PxVehicle4WGetAppliedGeardown(*_vehicle);
}

bool Vehicle4W::IsInAir::get()
{
	return PxVehicle4WIsInAir(*_vehicle);
}

Shape^ Vehicle4W::FrontLeftWheelShape::get()
{
	PxShape* shape = PxVehicle4WGetFrontLeftWheelShape(*_vehicle);

	return ObjectTable::GetObject<Shape^>((intptr_t)shape);
}

Shape^ Vehicle4W::FrontRightWheelShape::get()
{
	PxShape* shape = PxVehicle4WGetFrontRightWheelShape(*_vehicle);

	return ObjectTable::GetObject<Shape^>((intptr_t)shape);
}

Shape^ Vehicle4W::RearLeftWheelShape::get()
{
	PxShape* shape = PxVehicle4WGetRearLeftWheelShape(*_vehicle);

	return ObjectTable::GetObject<Shape^>((intptr_t)shape);
}

Shape^ Vehicle4W::RearRightWheelShape::get()
{
	PxShape* shape = PxVehicle4WGetRearRightWheelShape(*_vehicle);

	return ObjectTable::GetObject<Shape^>((intptr_t)shape);
}

int Vehicle4W::NumberOfChassisShapes::get()
{
	return PxVehicle4WGetNumChassisShapes(*_vehicle);
}

float Vehicle4W::EngineRotationSpeed::get()
{
	return PxVehicle4WGetEngineRotationSpeed(*_vehicle);
}

PxVehicle4W* Vehicle4W::UnmanagedPointer::get()
{
	return _vehicle;
}