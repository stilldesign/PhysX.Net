#pragma once

#include <PxVehicleUtils.h>

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class Vehicle4WSimpleSetup
	{
		internal:
			static PxVehicle4WSimpleSetup ToUnmanaged(Vehicle4WSimpleSetup^ setup);

		public:
			property Vector3 ChassisDims;
			property Vector3 ChassisCMOffset;
			property float ChassisMass;
			property Vector3 ChassisMOI;
			property array<Vector3>^ WheelCentreCMOffsets;
			property float FrontWheelWidth;
			property float FrontWheelRadius;
			property float FrontWheelMass;
			property float FrontWheelBrakeTorque;
			property float FrontWheelMaxSteer;
			property float FrontWheelToeAngle;
			property float FrontWheelDampingRate;
			property float RearWheelWidth;
			property float RearWheelRadius;
			property float RearWheelMass;
			property float RearWheelBrakeTorque;
			property float RearWheelHandbrakeTorque;
			property float RearWheelToeAngle;
			property float RearWheelDampingRate;
			property Vector3 FrontSuspensionTravelDir;
			property float FrontSuspensionMaxCompression;
			property float FrontSuspensionMaxDroop;
			property float FrontSuspensionSpringStrength;
			property float FrontSuspensionSpringDampingRate;
			property Vector3 RearSuspensionTravelDir;
			property float RearSuspensionMaxCompression;
			property float RearSuspensionMaxDroop;
			property float RearSuspensionSpringStrength;
			property float RearSuspensionSpringDampingRate;
			property float FrontTyreLatStiffX;
			property float FrontTyreLatStiffY;
			property float FrontTyreLongitudinalStiffness;
			property float FrontTyreCamberStiffness;
			property array<array<float>^>^ FrontTyreFrictionVsSlipGraph;
			property int FrontTyreType;
			property float RearTyreLatStiffX;
			property float RearTyreLatStiffY;
			property float RearTyreLongitudinalStiffness;
			property float RearTyreCamberStiffness;
			property array<array<float>^>^ RearTyreFrictionVsSlipGraph;
			property int RearTyreType;
			property float TyreLoadFilterMinNormalisedLoad;
			property float TyreLoadFilterMaxNormalisedLoad;
			property float TyreLoadFilterMaxFilteredNormalisedLoad;
			property float FrontSuspForceAppPointVerticalCMOffset;
			property float RearSuspForceAppPointVerticalCMOffset;
			property float FrontTyreForceAppPointVerticalCMOffset;
			property float RearTyreForceAppPointVerticalCMOffset;
			property float DiffFrontRearSplit;
			property float DiffCentreBias;
			property float DiffFrontBias;
			property float DiffRearBias;
			property int DiffType;
			property float EnginePeakTorque;
			property float EngineMaxOmega;
			property float EngineEngagedClutchDampingRate;
			property float EngineDisengagedClutchDampingRate;
			property int NumGearRatios;
			property array<float>^ GearRatios;
			property float GearFinalRatio;
			property float GearSwitchTime;
			property array<float>^ AutoBoxUpRatios;
			property array<float>^ AutoBoxDownRatios;
			property float ClutchStrength;
			property float AckermannAccuracy;
	};
};