#include "StdAfx.h"
#include "VehicleRawInputData.h"

VehicleRawInputData::VehicleRawInputData(PxVehicleRawInputData* inputData)
{
	if (inputData == NULL)
		throw gcnew ArgumentNullException("inputData");

	_inputData = inputData;
}
VehicleRawInputData::~VehicleRawInputData()
{
	this->!VehicleRawInputData();
}
VehicleRawInputData::!VehicleRawInputData()
{
	SAFE_DELETE(_inputData);
}

bool VehicleRawInputData::Disposed::get()
{
	return _inputData == NULL;
}

array<bool>^ VehicleRawInputData::GetRawDigitalInputs()
{
	return Util::AsManagedArray<bool>(&_inputData->mRawDigitalInputs, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS+PxVehicleControlInputs::eMAX_NUM_VEHICLE_DIGITAL_INPUTS);
}
void VehicleRawInputData::SetRawDigitalInputs(array<bool>^ value)
{
	Util::AsUnmanagedArray(value, &_inputData->mRawDigitalInputs, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS+PxVehicleControlInputs::eMAX_NUM_VEHICLE_DIGITAL_INPUTS);
}

array<bool>^ VehicleRawInputData::GetRawAnalogInputs()
{
	return Util::AsManagedArray<bool>(&_inputData->mRawAnalogInputs, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
}
void VehicleRawInputData::SetRawAnalogInputs(array<bool>^ value)
{
	Util::AsUnmanagedArray(value, &_inputData->mRawAnalogInputs, PxVehicleControlInputs::eMAX_NUM_VEHICLE_ANALOG_INPUTS);
}

bool VehicleRawInputData::DigitalAccelerationKeyPressed::get()
{
	return _inputData->getDigitalAccel();
}
void VehicleRawInputData::DigitalAccelerationKeyPressed::set(bool value)
{
	_inputData->setDigitalAccel(value);
}

bool VehicleRawInputData::DigitalBrakeKeyPressed::get()
{
	return _inputData->getDigitalBrake();
}
void VehicleRawInputData::DigitalBrakeKeyPressed::set(bool value)
{
	_inputData->setDigitalBrake(value);
}

bool VehicleRawInputData::DigitalHandbrakeKeyPressed::get()
{
	return _inputData->getDigitalHandbrake();
}
void VehicleRawInputData::DigitalHandbrakeKeyPressed::set(bool value)
{
	_inputData->setDigitalHandbrake(value);
}

bool VehicleRawInputData::DigitalSteerLeftKeyPressed::get()
{
	return _inputData->getDigitalSteerLeft();
}
void VehicleRawInputData::DigitalSteerLeftKeyPressed::set(bool value)
{
	_inputData->setDigitalSteerLeft(value);
}

bool VehicleRawInputData::DigitalSteerRightKeyPressed::get()
{
	return _inputData->getDigitalSteerRight();
}
void VehicleRawInputData::DigitalSteerRightKeyPressed::set(bool value)
{
	_inputData->setDigitalSteerRight(value);
}

float VehicleRawInputData::AnalogAcceleration::get()
{
	return _inputData->getAnalogAccel();
}
void VehicleRawInputData::AnalogAcceleration::set(float value)
{
	_inputData->setAnalogAccel(value);
}

float VehicleRawInputData::AnalogBrake::get()
{
	return _inputData->getAnalogBrake();
}
void VehicleRawInputData::AnalogBrake::set(float value)
{
	_inputData->setAnalogBrake(value);
}

float VehicleRawInputData::AnalogHandbrake::get()
{
	return _inputData->getAnalogHandbrake();
}
void VehicleRawInputData::AnalogHandbrake::set(float value)
{
	_inputData->setAnalogHandbrake(value);
}

float VehicleRawInputData::AnalogSteer::get()
{
	return _inputData->getAnalogSteer();
}
void VehicleRawInputData::AnalogSteer::set(float value)
{
	_inputData->setAnalogSteer(value);
}

bool VehicleRawInputData::GearUpKeyPressed::get()
{
	return _inputData->getGearUp();
}
void VehicleRawInputData::GearUpKeyPressed::set(bool value)
{
	_inputData->setGearUp(value);
}

bool VehicleRawInputData::GearDownKeyPressed::get()
{
	return _inputData->getGearDown();
}
void VehicleRawInputData::GearDownKeyPressed::set(bool value)
{
	_inputData->setGearDown(value);
}

PxVehicleRawInputData* VehicleRawInputData::UnmanagedPointer::get()
{
	return _inputData;
}