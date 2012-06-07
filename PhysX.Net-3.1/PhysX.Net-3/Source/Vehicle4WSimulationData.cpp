#include "StdAfx.h"
#include "Vehicle4WSimulationData.h"
#include "VehicleAutoBoxData.h"
#include "VehicleDifferential4WData.h"
#include "VehicleChassisData.h"
#include "VehicleEngineData.h"
#include "VehicleClutchData.h"
#include "VehicleGearsData.h"
#include "VehicleSuspensionData.h"
#include "VehicleWheelData.h"
#include "VehicleTyreData.h"
#include "VehicleTyreLoadFilterData.h"

Vehicle4WSimulationData::Vehicle4WSimulationData()
{
	this->SuspensionData = gcnew VehicleWheelValues<VehicleSuspensionData^>();
	this->WheelData = gcnew VehicleWheelValues<VehicleWheelData^>();
	this->TyreData = gcnew VehicleWheelValues<VehicleTyreData^>();
	this->SuspensionTravelDirections = gcnew VehicleWheelValues<Vector3>();
	this->SuspensionForceApplicationPointOffsets = gcnew VehicleWheelValues<Vector3>();
	this->TyreForceApplicationPointOffsets = gcnew VehicleWheelValues<Vector3>();
	this->WheelCentreOffsets = gcnew VehicleWheelValues<Vector3>();
	this->TyreRestLoads = gcnew VehicleWheelValues<float>();
	this->ReciprocalTyreRestLoads = gcnew VehicleWheelValues<float>();
}

PxVehicle4WSimulationData Vehicle4WSimulationData::ToUnmanaged(Vehicle4WSimulationData^ data)
{
	PxVehicle4WSimulationData d;
		d.setChassisData(VehicleChassisData::ToUnmanaged(data->ChassisData));
		d.setEngineData(VehicleEngineData::ToUnmanaged(data->EngineData));
		d.setGearsData(VehicleGearsData::ToUnmanaged(data->GearsData));
		d.setClutchData(VehicleClutchData::ToUnmanaged(data->ClutchData));
		d.setAutoBoxData(VehicleAutoBoxData::ToUnmanaged(data->AutoBoxData));
		d.setDiffData(VehicleDifferential4WData::ToUnmanaged(data->DifferentialData));

		for (int i = 0; i < PxVehicle4WSimulationData::eNUM_WHEELS; i++)
		{
			d.setSuspensionData(VehicleSuspensionData::ToUnmanaged(data->SuspensionData[i]), i);
			d.setWheelData(VehicleWheelData::ToUnmanaged(data->WheelData[i]), i);
			d.setTyreData(VehicleTyreData::ToUnmanaged(data->TyreData[i]), i);
			d.setSuspTravelDirection(MathUtil::Vector3ToPxVec3(data->SuspensionTravelDirections[i]), i);
			d.setSuspForceAppPointOffset(MathUtil::Vector3ToPxVec3(data->SuspensionForceApplicationPointOffsets[i]), i);
			d.setTyreForceAppPointOffset(MathUtil::Vector3ToPxVec3(data->TyreForceApplicationPointOffsets[i]), i);
		}

		d.setWheelCentreOffsets(
			MathUtil::Vector3ToPxVec3(data->WheelCentreOffsets->FrontLeftWheel),
			MathUtil::Vector3ToPxVec3(data->WheelCentreOffsets->FrontRightWheel),
			MathUtil::Vector3ToPxVec3(data->WheelCentreOffsets->RearLeftWheel),
			MathUtil::Vector3ToPxVec3(data->WheelCentreOffsets->RearRightWheel));
		d.setTyreLoadFilterData(VehicleTyreLoadFilterData::ToUnmanaged(data->TyreLoadFilterData));
		d.setAckermannAccuracy(data->AckermannAccuracy);
		
	return d;
}
Vehicle4WSimulationData^ Vehicle4WSimulationData::ToManaged(PxVehicle4WSimulationData data)
{
	Vehicle4WSimulationData^ d = gcnew Vehicle4WSimulationData();
		d->ChassisData = VehicleChassisData::ToManaged(data.getChassisData());
		d->EngineData = VehicleEngineData::ToManaged(data.getEngineData());
		d->GearsData = VehicleGearsData::ToManaged(data.getGearsData());
		d->ClutchData = VehicleClutchData::ToManaged(data.getClutchData());
		d->AutoBoxData = VehicleAutoBoxData::ToManaged(data.getAutoBoxData());
		d->DifferentialData = VehicleDifferential4WData::ToManaged(data.getDiffData());

		for (int i = 0; i < PxVehicle4WSimulationData::eNUM_WHEELS; i++)
		{
			d->SuspensionData[i] = VehicleSuspensionData::ToManaged(data.getSuspensionData(i));
			d->WheelData[i] = VehicleWheelData::ToManaged(data.getWheelData(i));
			d->TyreData[i] = VehicleTyreData::ToManaged(data.getTyreData(i));
			d->SuspensionTravelDirections[i] = MathUtil::PxVec3ToVector3(data.getSuspTravelDirection(i));
			d->SuspensionForceApplicationPointOffsets[i] = MathUtil::PxVec3ToVector3(data.getSuspForceAppPointOffset(i));
			d->TyreForceApplicationPointOffsets[i] = MathUtil::PxVec3ToVector3(data.getTyreForceAppPointOffset(i));
			d->WheelCentreOffsets[i] = MathUtil::PxVec3ToVector3(data.getWheelCentreOffset(i));
			d->TyreRestLoads[i] = data.getTyreRestLoadsArray()[i];
			d->ReciprocalTyreRestLoads[i] = data.getRecipTyreRestLoadsArray()[i];
		}

		d->TyreLoadFilterData = VehicleTyreLoadFilterData::ToManaged(data.getTyreLoadFilterData());
		//d->AckermannAccuracy = data.getAckermannGeometryData().
		
	return d;
}