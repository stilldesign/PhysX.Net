#include "StdAfx.h"
#include "Vehicle4WSimpleSetup.h"

PxVehicle4WSimpleSetup Vehicle4WSimpleSetup::ToUnmanaged(Vehicle4WSimpleSetup^ setup)
{
	ThrowIfNull(setup, "setup")
	
	PxVehicle4WSimpleSetup s;
		s.mChassisDims = MathUtil::Vector3ToPxVec3(setup->ChassisDims);
		s.mChassisCMOffset = MathUtil::Vector3ToPxVec3(setup->ChassisCMOffset);
		s.mChassisMass = setup->ChassisMass;
		s.mChassisMOI = MathUtil::Vector3ToPxVec3(setup->ChassisMOI);
		Util::AsUnmanagedArray(setup->WheelCentreCMOffsets, &s.mWheelCentreCMOffsets);
		s.mFrontWheelWidth = setup->FrontWheelWidth;
		s.mFrontWheelRadius = setup->FrontWheelRadius;
		s.mFrontWheelMass = setup->FrontWheelMass;
		s.mFrontWheelBrakeTorque = setup->FrontWheelBrakeTorque;
		s.mFrontWheelMaxSteer = setup->FrontWheelMaxSteer;
		s.mFrontWheelToeAngle = setup->FrontWheelToeAngle;
		s.mFrontWheelDampingRate = setup->FrontWheelDampingRate;
		s.mRearWheelWidth = setup->RearWheelWidth;
		s.mRearWheelRadius = setup->RearWheelRadius;
		s.mRearWheelMass = setup->RearWheelMass;
		s.mRearWheelBrakeTorque = setup->RearWheelBrakeTorque;
		s.mRearWheelHandbrakeTorque = setup->RearWheelHandbrakeTorque;
		s.mRearWheelToeAngle = setup->RearWheelToeAngle;
		s.mRearWheelDampingRate = setup->RearWheelDampingRate;
		s.mFrontSuspensionTravelDir = MathUtil::Vector3ToPxVec3(setup->FrontSuspensionTravelDir);
		s.mFrontSuspensionMaxCompression = setup->FrontSuspensionMaxCompression;
		s.mFrontSuspensionMaxDroop = setup->FrontSuspensionMaxDroop;
		s.mFrontSuspensionSpringStrength = setup->FrontSuspensionSpringStrength;
		s.mFrontSuspensionSpringDampingRate = setup->FrontSuspensionSpringDampingRate;
		s.mRearSuspensionTravelDir = MathUtil::Vector3ToPxVec3(setup->RearSuspensionTravelDir);
		s.mRearSuspensionMaxCompression = setup->RearSuspensionMaxCompression;
		s.mRearSuspensionMaxDroop = setup->RearSuspensionMaxDroop;
		s.mRearSuspensionSpringStrength = setup->RearSuspensionSpringStrength;
		s.mRearSuspensionSpringDampingRate = setup->RearSuspensionSpringDampingRate;
		s.mFrontTyreLatStiffX = setup->FrontTyreLatStiffX;
		s.mFrontTyreLatStiffY = setup->FrontTyreLatStiffY;
		s.mFrontTyreLongitudinalStiffness = setup->FrontTyreLongitudinalStiffness;
		s.mFrontTyreCamberStiffness = setup->FrontTyreCamberStiffness;
		//s.mFrontTyreFrictionVsSlipGraph = setup->FrontTyreFrictionVsSlipGraph;
		s.mFrontTyreType = setup->FrontTyreType;
		s.mRearTyreLatStiffX = setup->RearTyreLatStiffX;
		s.mRearTyreLatStiffY = setup->RearTyreLatStiffY;
		s.mRearTyreLongitudinalStiffness = setup->RearTyreLongitudinalStiffness;
		s.mRearTyreCamberStiffness = setup->RearTyreCamberStiffness;
		//s.mRearTyreFrictionVsSlipGraph = setup->RearTyreFrictionVsSlipGraph;
		s.mRearTyreType = setup->RearTyreType;
		s.mTyreLoadFilterMinNormalisedLoad = setup->TyreLoadFilterMinNormalisedLoad;
		s.mTyreLoadFilterMaxNormalisedLoad = setup->TyreLoadFilterMaxNormalisedLoad;
		s.mTyreLoadFilterMaxFilteredNormalisedLoad = setup->TyreLoadFilterMaxFilteredNormalisedLoad;
		s.mFrontSuspForceAppPointVerticalCMOffset = setup->FrontSuspForceAppPointVerticalCMOffset;
		s.mRearSuspForceAppPointVerticalCMOffset = setup->RearSuspForceAppPointVerticalCMOffset;
		s.mFrontTyreForceAppPointVerticalCMOffset = setup->FrontTyreForceAppPointVerticalCMOffset;
		s.mRearTyreForceAppPointVerticalCMOffset = setup->RearTyreForceAppPointVerticalCMOffset;
		s.mDiffFrontRearSplit = setup->DiffFrontRearSplit;
		s.mDiffCentreBias = setup->DiffCentreBias;
		s.mDiffFrontBias = setup->DiffFrontBias;
		s.mDiffRearBias = setup->DiffRearBias;
		s.mDiffType = setup->DiffType;
		s.mEnginePeakTorque = setup->EnginePeakTorque;
		s.mEngineMaxOmega = setup->EngineMaxOmega;
		s.mEngineEngagedClutchDampingRate = setup->EngineEngagedClutchDampingRate;
		s.mEngineDisengagedClutchDampingRate = setup->EngineDisengagedClutchDampingRate;
		s.mNumGearRatios = setup->NumGearRatios;
		Util::AsUnmanagedArray(setup->GearRatios, &s.mGearRatios);
		s.mGearFinalRatio = setup->GearFinalRatio;
		s.mGearSwitchTime = setup->GearSwitchTime;
		Util::AsUnmanagedArray(setup->AutoBoxUpRatios, &s.mAutoBoxUpRatios);
		Util::AsUnmanagedArray(setup->AutoBoxDownRatios, &s.mAutoBoxDownRatios);
		s.mClutchStrength = setup->ClutchStrength;
		s.mAckermannAccuracy = setup->AckermannAccuracy;

	return s;
}