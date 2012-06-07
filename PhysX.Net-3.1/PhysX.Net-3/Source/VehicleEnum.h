#pragma once

#include <PxVehicle.h>

namespace PhysX
{
	public enum class VehicleDifferentialType
	{
		LS4WheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_4WD,
		LSFrontWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_FRONTWD,
		LSRearWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_LS_REARWD,
		Open4WheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_4WD,
		OpenFrontWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_FRONTWD,
		OpenRearWheelDrive = PxVehicleDifferential4WData::eDIFF_TYPE_OPEN_REARWD
	};						 

	public enum class VehicleAnalogInput
	{
		Acceleration = PxVehicleControlInputs::eVEHICLE_ANALOG_INPUT_ACCEL,
		Brake = PxVehicleControlInputs::eVEHICLE_ANALOG_INPUT_BRAKE,
		HandBrake = PxVehicleControlInputs::eVEHICLE_ANALOG_INPUT_HANDBRAKE,
		SteerLeft = PxVehicleControlInputs::eVEHICLE_ANALOG_INPUT_STEER_LEFT,
		SteerRight = PxVehicleControlInputs::eVEHICLE_ANALOG_INPUT_STEER_RIGHT
	};

	public enum class VehicleDigitalInput
	{
		GearUp = PxVehicleControlInputs::eVEHICLE_DIGITAL_INPUT_GEAR_UP,
		GearDown = PxVehicleControlInputs::eVEHICLE_DIGITAL_INPUT_GEAR_DOWN
	};

	public enum class VehicleDrivableSurfaceType
	{
		Unknown = PxVehicleDrivableSurfaceType::eSURFACE_TYPE_UNKNOWN
	};

	public enum class VehicleGears
	{
		Reverse = PxVehicleGearsData::eREVERSE,
		Neutral = PxVehicleGearsData::eNEUTRAL,
		First = PxVehicleGearsData::eFIRST,
		Second = PxVehicleGearsData::eSECOND,
		Third = PxVehicleGearsData::eTHIRD,
		Fourth = PxVehicleGearsData::eFOURTH,
		Fifth = PxVehicleGearsData::eFIFTH,
		Sixth = PxVehicleGearsData::eSIXTH
	};
};