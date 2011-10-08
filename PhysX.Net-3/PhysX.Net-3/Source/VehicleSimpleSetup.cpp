#include "StdAfx.h"
#include "VehicleSimpleSetup.h"
#include "Vehicle4WSimulationData.h"

VehicleSimpleSetup::VehicleSimpleSetup()
{
	PxVehicle4WSimpleSetup d = PxVehicle4WSimpleSetup();

	// Initalize from a default struct
	PopulateFromUnmanaged(d);
}

PxVehicle4WSimpleSetup VehicleSimpleSetup::ToUnmanaged(VehicleSimpleSetup^ setup)
{
	// TODO: Complete the few remaining properties

	PxVehicle4WSimpleSetup s;
		s.mAckermannAccuracy = setup->AckermannAccuracy;
		Util::AsUnmanagedArray(setup->AutoBoxDownRatios, &s.mAutoBoxDownRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		Util::AsUnmanagedArray(setup->AutoBoxUpRatios, &s.mAutoBoxUpRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		s.mChassisCMOffset = MathUtil::Vector3ToPxVec3(setup->ChassisCMOffset);
		s.mChassisDims = MathUtil::Vector3ToPxVec3(setup->ChassisDims);
		s.mChassisMass = setup->ChassisMass;
		s.mChassisMOI = MathUtil::Vector3ToPxVec3(setup->ChassisMOI);
		s.mClutchStrength = setup->ClutchStrength;
		s.mDiffCentreBias = setup->DiffCentreBias;
		s.mDiffFrontBias = setup->DiffFrontBias;
		s.mDiffFrontRearSplit = setup->DiffFrontRearSplit;
		s.mDiffRearBias = setup->DiffRearBias;
		s.mDiffType = (PxU32)setup->DiffType;
		s.mEngineDisengagedClutchDampingRate = setup->EngineDisengagedClutchDampingRate;
		s.mEngineEngagedClutchDampingRate = setup->EngineEngagedClutchDampingRate;
		s.mEngineMaxOmega = setup->EngineMaxOmega;
		s.mEnginePeakTorque = setup->EnginePeakTorque;
		//s.mEngineTorqueCurve = setup->EngineTorqueCurve;
		s.mFrontSuspensionMaxCompression = setup->FrontSuspensionMaxCompression;
		s.mFrontSuspensionMaxDroop = setup->FrontSuspensionMaxDroop;
		s.mFrontSuspensionSpringDampingRate = setup->FrontSuspensionSpringDampingRate;
		s.mFrontSuspensionSpringStrength = setup->FrontSuspensionSpringStrength;
		s.mFrontSuspensionTravelDir = MathUtil::Vector3ToPxVec3(setup->FrontSuspensionTravelDir);
		s.mFrontSuspForceAppPointVerticalCMOffset = setup->FrontSuspForceAppPointVerticalCMOffset;
		s.mFrontTyreCamberStiffness = setup->FrontTyreCamberStiffness;
		s.mFrontTyreForceAppPointVerticalCMOffset = setup->FrontTyreForceAppPointVerticalCMOffset;
		//s.mFrontTyreFrictionVsSlipGraph[3][2] = setup->FrontTyreFrictionVsSlipGraph[3][2];
		s.mFrontTyreLatStiffX = setup->FrontTyreLatStiffX;
		s.mFrontTyreLatStiffY = setup->FrontTyreLatStiffY;
		s.mFrontTyreLongitudinalStiffness = setup->FrontTyreLongitudinalStiffness;
		s.mFrontTyreType = setup->FrontTyreType;
		s.mFrontWheelBrakeTorque = setup->FrontWheelBrakeTorque;
		s.mFrontWheelDampingRate = setup->FrontWheelDampingRate;
		s.mFrontWheelMass = setup->FrontWheelMass;
		s.mFrontWheelMaxSteer = setup->FrontWheelMaxSteer;
		s.mFrontWheelRadius = setup->FrontWheelRadius;
		s.mFrontWheelToeAngle = setup->FrontWheelToeAngle;
		s.mFrontWheelWidth = setup->FrontWheelWidth;
		s.mGearFinalRatio = setup->GearFinalRatio;
		Util::AsUnmanagedArray(setup->GearRatios, s.mGearRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
		s.mGearSwitchTime = setup->GearSwitchTime;
		s.mNumGearRatios = setup->NumGearRatios;
		s.mRearSuspensionMaxCompression = setup->RearSuspensionMaxCompression;
		s.mRearSuspensionMaxDroop = setup->RearSuspensionMaxDroop;
		s.mRearSuspensionSpringDampingRate = setup->RearSuspensionSpringDampingRate;
		s.mRearSuspensionSpringStrength = setup->RearSuspensionSpringStrength;
		s.mRearSuspensionTravelDir = MathUtil::Vector3ToPxVec3(setup->RearSuspensionTravelDir);
		s.mRearSuspForceAppPointVerticalCMOffset = setup->RearSuspForceAppPointVerticalCMOffset;
		s.mRearTyreCamberStiffness = setup->RearTyreCamberStiffness;
		s.mRearTyreForceAppPointVerticalCMOffset = setup->RearTyreForceAppPointVerticalCMOffset;
		//Util::AsUnmanagedArray(setup->RearTyreFrictionVsSlipGraph, &s.mRearTyreFrictionVsSlipGraph, 3*2);
		s.mRearTyreLatStiffX = setup->RearTyreLatStiffX;
		s.mRearTyreLatStiffY = setup->RearTyreLatStiffY;
		s.mRearTyreLongitudinalStiffness = setup->RearTyreLongitudinalStiffness;
		s.mRearTyreType = setup->RearTyreType;
		s.mRearWheelBrakeTorque = setup->RearWheelBrakeTorque;
		s.mRearWheelDampingRate = setup->RearWheelDampingRate;
		s.mRearWheelHandbrakeTorque = setup->RearWheelHandbrakeTorque;
		s.mRearWheelMass = setup->RearWheelMass;
		s.mRearWheelRadius = setup->RearWheelRadius;
		s.mRearWheelToeAngle = setup->RearWheelToeAngle;
		s.mRearWheelWidth = setup->RearWheelWidth;
		s.mTyreLoadFilterMaxFilteredNormalisedLoad = setup->TyreLoadFilterMaxFilteredNormalisedLoad;
		s.mTyreLoadFilterMaxNormalisedLoad = setup->TyreLoadFilterMaxNormalisedLoad;
		s.mTyreLoadFilterMinNormalisedLoad = setup->TyreLoadFilterMinNormalisedLoad;
		Util::AsUnmanagedArray(setup->WheelCentreCMOffsets, s.mWheelCentreCMOffsets, PxVehicle4WSimulationData::eNUM_WHEELS);

	return s;
}
VehicleSimpleSetup^ VehicleSimpleSetup::ToManaged(PxVehicle4WSimpleSetup setup)
{
	auto v = gcnew VehicleSimpleSetup();

	v->PopulateFromUnmanaged(setup);

	return v;
}

void VehicleSimpleSetup::PopulateFromUnmanaged(PxVehicle4WSimpleSetup setup)
{
	this->AckermannAccuracy = setup.mAckermannAccuracy;
	this->AutoBoxDownRatios = Util::AsManagedArray<float>(setup.mAutoBoxDownRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
	this->AutoBoxUpRatios = Util::AsManagedArray<float>(setup.mAutoBoxUpRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
	this->ChassisCMOffset = MathUtil::PxVec3ToVector3(setup.mChassisCMOffset);
	this->ChassisDims = MathUtil::PxVec3ToVector3(setup.mChassisDims);
	this->ChassisMass = setup.mChassisMass;
	this->ChassisMOI = MathUtil::PxVec3ToVector3(setup.mChassisMOI);
	this->ClutchStrength = setup.mClutchStrength;
	this->DiffCentreBias = setup.mDiffCentreBias;
	this->DiffFrontBias = setup.mDiffFrontBias;
	this->DiffFrontRearSplit = setup.mDiffFrontRearSplit;
	this->DiffRearBias = setup.mDiffRearBias;
	this->DiffType = (VehicleDifferentialType)setup.mDiffType;
	this->EngineDisengagedClutchDampingRate = setup.mEngineDisengagedClutchDampingRate;
	this->EngineEngagedClutchDampingRate = setup.mEngineEngagedClutchDampingRate;
	this->EngineMaxOmega = setup.mEngineMaxOmega;
	this->EnginePeakTorque = setup.mEnginePeakTorque;
	//this->EngineTorqueCurve = setup.mEngineTorqueCurve;
	this->FrontSuspensionMaxCompression = setup.mFrontSuspensionMaxCompression;
	this->FrontSuspensionMaxDroop = setup.mFrontSuspensionMaxDroop;
	this->FrontSuspensionSpringDampingRate = setup.mFrontSuspensionSpringDampingRate;
	this->FrontSuspensionSpringStrength = setup.mFrontSuspensionSpringStrength;
	this->FrontSuspensionTravelDir = MathUtil::PxVec3ToVector3(setup.mFrontSuspensionTravelDir);
	this->FrontSuspForceAppPointVerticalCMOffset = setup.mFrontSuspForceAppPointVerticalCMOffset;
	this->FrontTyreCamberStiffness = setup.mFrontTyreCamberStiffness;
	this->FrontTyreForceAppPointVerticalCMOffset = setup.mFrontTyreForceAppPointVerticalCMOffset;
	//this->FrontTyreFrictionVsSlipGraph[3][2] = setup.mFrontTyreFrictionVsSlipGraph[3][2];
	this->FrontTyreLatStiffX = setup.mFrontTyreLatStiffX;
	this->FrontTyreLatStiffY = setup.mFrontTyreLatStiffY;
	this->FrontTyreLongitudinalStiffness = setup.mFrontTyreLongitudinalStiffness;
	this->FrontTyreType = setup.mFrontTyreType;
	this->FrontWheelBrakeTorque = setup.mFrontWheelBrakeTorque;
	this->FrontWheelDampingRate = setup.mFrontWheelDampingRate;
	this->FrontWheelMass = setup.mFrontWheelMass;
	this->FrontWheelMaxSteer = setup.mFrontWheelMaxSteer;
	this->FrontWheelRadius = setup.mFrontWheelRadius;
	this->FrontWheelToeAngle = setup.mFrontWheelToeAngle;
	this->FrontWheelWidth = setup.mFrontWheelWidth;
	this->GearFinalRatio = setup.mGearFinalRatio;
	this->GearRatios = Util::AsManagedArray<float>(setup.mGearRatios, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
	this->GearSwitchTime = setup.mGearSwitchTime;
	this->NumGearRatios = setup.mNumGearRatios;
	this->RearSuspensionMaxCompression = setup.mRearSuspensionMaxCompression;
	this->RearSuspensionMaxDroop = setup.mRearSuspensionMaxDroop;
	this->RearSuspensionSpringDampingRate = setup.mRearSuspensionSpringDampingRate;
	this->RearSuspensionSpringStrength = setup.mRearSuspensionSpringStrength;
	this->RearSuspensionTravelDir = MathUtil::PxVec3ToVector3(setup.mRearSuspensionTravelDir);
	this->RearSuspForceAppPointVerticalCMOffset = setup.mRearSuspForceAppPointVerticalCMOffset;
	this->RearTyreCamberStiffness = setup.mRearTyreCamberStiffness;
	this->RearTyreForceAppPointVerticalCMOffset = setup.mRearTyreForceAppPointVerticalCMOffset;
	//Util::AsUnmanagedArray(setup.mRearTyreFrictionVsSlipGraph, &this->RearTyreFrictionVsSlipGraph, 3*2);
	this->RearTyreLatStiffX = setup.mRearTyreLatStiffX;
	this->RearTyreLatStiffY = setup.mRearTyreLatStiffY;
	this->RearTyreLongitudinalStiffness = setup.mRearTyreLongitudinalStiffness;
	this->RearTyreType = setup.mRearTyreType;
	this->RearWheelBrakeTorque = setup.mRearWheelBrakeTorque;
	this->RearWheelDampingRate = setup.mRearWheelDampingRate;
	this->RearWheelHandbrakeTorque = setup.mRearWheelHandbrakeTorque;
	this->RearWheelMass = setup.mRearWheelMass;
	this->RearWheelRadius = setup.mRearWheelRadius;
	this->RearWheelToeAngle = setup.mRearWheelToeAngle;
	this->RearWheelWidth = setup.mRearWheelWidth;
	this->TyreLoadFilterMaxFilteredNormalisedLoad = setup.mTyreLoadFilterMaxFilteredNormalisedLoad;
	this->TyreLoadFilterMaxNormalisedLoad = setup.mTyreLoadFilterMaxNormalisedLoad;
	this->TyreLoadFilterMinNormalisedLoad = setup.mTyreLoadFilterMinNormalisedLoad;
	this->WheelCentreCMOffsets = Util::AsManagedArray<Vector3>(setup.mWheelCentreCMOffsets, PxVehicleGearsData::eMAX_NUM_GEAR_RATIOS);
}

Vehicle4WSimulationData^ VehicleSimpleSetup::ToSimulationData()
{
	PxVehicle4WSimulationData simData = PxCreateVehicle4WSimulationData(ToUnmanaged(this));

	return Vehicle4WSimulationData::ToManaged(simData);
}