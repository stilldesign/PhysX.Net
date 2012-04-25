#pragma once

#include "VehicleEnum.h"
#include <PxVehicleUtils.h> 

namespace PhysX
{
	ref class FixedSizeLookupTable;
	ref class Vehicle4WSimulationData;

	public ref class VehicleSimpleSetup
	{
		public:
			VehicleSimpleSetup();

		internal:
			static PxVehicle4WSimpleSetup ToUnmanaged(VehicleSimpleSetup^ setup);
			static VehicleSimpleSetup^ ToManaged(PxVehicle4WSimpleSetup setup);

			void PopulateFromUnmanaged(PxVehicle4WSimpleSetup setup);

		public:
			Vehicle4WSimulationData^ ToSimulationData();

			/// <summary>
			/// Full extents of chassis aabb (must be set, default value zero).
			/// </summary>
			property Vector3 ChassisDims;

			/// <summary>
			/// Offset from actor centre to centre of mass of chassis rigid body (must be set, default value zero).
			/// </summary>
			property Vector3 ChassisCMOffset;

			/// <summary>
			///	Total mass of chassis rigid body (kg).
			/// </summary>
			property float ChassisMass;

			/// <summary>
			/// Moment of inertia of chassis rigid body (kg m^2) (must be set, default value zero).
			/// </summary>
			property Vector3 ChassisMOI;
			

			/// <summary>
			/// Offset from rigid body centre of mass to wheel centres at rest (must be set, default value zero).
			/// </summary>
			property array<Vector3>^ WheelCentreCMOffsets;

			/// <summary>
			/// Front wheel width (must be set, default value zero).
			/// </summary>
			property float FrontWheelWidth;

			/// <summary>
			/// Front wheel radius (must be set, default value zero).
			/// </summary>
			property float FrontWheelRadius;

			/// <summary>
			/// Front wheel mass.
			/// </summary>
			property float FrontWheelMass;

			/// <summary>
			/// Front wheel brake torque.
			/// </summary>
			property float FrontWheelBrakeTorque;

			/// <summary>
			/// Front wheel maximum steer.
			/// </summary>
			property float FrontWheelMaxSteer;

			/// <summary>
			/// Front wheel toe angle.
			/// </summary>
			property float FrontWheelToeAngle;

			/// <summary>
			/// Front wheel damping rate.
			/// </summary>
			property float FrontWheelDampingRate;

			/// <summary>
			/// Rear wheel width (must be set, default value zero).
			/// </summary>
			property float RearWheelWidth;

			/// <summary>
			/// Rear wheel radius (must be set, default value zero).
			/// </summary>
			property float RearWheelRadius;

			/// <summary>
			/// Rear wheel mass.
			/// </summary>
			property float RearWheelMass;

			/// <summary>
			/// Rear wheel brake torque.
			/// </summary>
			property float RearWheelBrakeTorque;

			/// <summary>
			/// Rear wheel handbrake torque.
			/// </summary>
			property float RearWheelHandbrakeTorque;

			/// <summary>
			/// Rear wheel toe angle.
			/// </summary>
			property float RearWheelToeAngle;

			/// <summary>
			/// Front wheel damping rate.
			/// </summary>
			property float RearWheelDampingRate;

			/// <summary>
			/// Front suspension travel direction as unit vector pointing downwards (must be set, default value zero).
			/// </summary>
			property Vector3  FrontSuspensionTravelDir;

			/// <summary>
			/// Front suspension max compression.
			/// </summary>
			property float FrontSuspensionMaxCompression;

			/// <summary>
			/// Front suspension max droop.
			/// </summary>
			property float FrontSuspensionMaxDroop;

			/// <summary>
			/// Front suspension max droop. 
			/// </summary>
			property float FrontSuspensionSpringStrength;

			/// <summary>
			/// Front suspension spring damping rate. 
			/// </summary>
			property float FrontSuspensionSpringDampingRate;

			/// <summary>
			/// Rear suspension travel direction as unit vector pointing downwards (must be set, default value zero). 
			/// </summary>
			property Vector3 RearSuspensionTravelDir;

			/// <summary>
			/// Rear suspension spring max compression. 
			/// </summary>
			property float RearSuspensionMaxCompression;

			/// <summary>
			/// Rear suspension spring max droop. 
			/// </summary>
			property float RearSuspensionMaxDroop;

			/// <summary>
			/// Rear suspension spring strength.
			/// </summary>
			property float RearSuspensionSpringStrength;

			/// <summary>
			/// Rear suspension spring damping rate.
			/// </summary>
			property float RearSuspensionSpringDampingRate;

			/// <summary>
			/// Minimum normalised load (load/restLoad) that gives a flat lateral stiffness response. 
			/// </summary>
			property float FrontTyreLatStiffX;

			/// <summary>
			/// Maximum possible lateral stiffness divided by the rest tyre load.
			/// </summary>
			property float FrontTyreLatStiffY;

			/// <summary>
			/// Tyre longitudinal stiffness.
			/// </summary>
			property float FrontTyreLongitudinalStiffness;
			
			/// <summary>
			/// Tyre camber stiffness.
			/// </summary>
			property float FrontTyreCamberStiffness;

			/// <summary>
			/// Friction vs longitudinal slip graph.
			/// </summary>
			property array<array<float>^>^ FrontTyreFrictionVsSlipGraph;

			/// <summary>
			/// Front tyre type.
			/// </summary>
			property int FrontTyreType;

			/// <summary>
			/// Minimum normalised load (load/restLoad) that gives a flat lateral stiffness response.
			/// </summary>
			property float RearTyreLatStiffX;

			/// <summary>
			/// Maximum possible lateral stiffness divided by the rest tyre load.
			/// </summary>
			property float RearTyreLatStiffY;

			/// <summary>
			/// Tyre longitudinal stiffness.
			/// </summary>
			property float RearTyreLongitudinalStiffness;

			/// <summary>
			/// Tyre camber stiffness.
			/// </summary>
			property float RearTyreCamberStiffness;

			/// <summary>
			/// Friction vs longitudinal slip graph.
			/// </summary>
			property array<array<float>^>^ RearTyreFrictionVsSlipGraph;

			/// <summary>
			/// Front tyre type.
			/// </summary>
			property int  RearTyreType;

			/// <summary>
			/// Graph point of normalised tyre load filter. 
			/// </summary>
			property float TyreLoadFilterMinNormalisedLoad;

			/// <summary>
			/// Graph point of normalised tyre load filter.
			/// </summary>
			property float TyreLoadFilterMaxNormalisedLoad;

			/// <summary>
			/// Graph point of normalised tyre load filter.
			/// </summary>
			property float TyreLoadFilterMaxFilteredNormalisedLoad;

			/// <summary>
			/// Offset that specifies the application point of rear suspension forces.
			/// </summary>
			property float FrontSuspForceAppPointVerticalCMOffset;

			/// <summary>
			/// Offset that specifies the application point of front suspension forces. 
			/// </summary>
			property float RearSuspForceAppPointVerticalCMOffset;

			/// <summary>
			/// Offset that specifies the application point of front tyre forces. 
			/// </summary>
			property float FrontTyreForceAppPointVerticalCMOffset;

			/// <summary>
			/// Offset that specifies the application point of rear tyre forces. 
			/// </summary>
			property float RearTyreForceAppPointVerticalCMOffset;
			
			/// <summary>
			/// Differential torque between front and rear. 
			/// </summary>
			property float DiffFrontRearSplit;

			/// <summary>
			/// Permitted ration of front and rear wheel rotational speed.
			/// </summary>
			property float DiffCentreBias;

			/// <summary>
			/// Permitted ration of front left and front right wheel rotational speed.
			/// </summary>
			property float DiffFrontBias;

			/// <summary>
			/// Permitted ration of rear left and ear right wheel rotational speed.
			/// </summary>
			property float DiffRearBias;

			/// <summary>
			/// Type of differential.
			/// </summary>
			property VehicleDifferentialType DiffType;

			/// <summary>
			/// Maximum torque delivered by engine.
			/// </summary>
			property float EnginePeakTorque;

			/// <summary>
			/// Graph of torque against normalised revs (revs/max revs).
			/// </summary>
			property FixedSizeLookupTable^ EngineTorqueCurve;

			/// <summary>
			/// Maximum engine rotational speed.
			/// </summary>
			property float EngineMaxOmega;

			/// <summary>
			/// Damping rate of engine when clutch is engaged. 
			/// </summary>
			property float EngineEngagedClutchDampingRate;

			/// <summary>
			/// Damping rate of engine when clutch is disengaged. 
			/// </summary>
			property float EngineDisengagedClutchDampingRate;
			
			/// <summary>
			/// Number of gears. 
			/// </summary>
			property int  NumGearRatios;

			/// <summary>
			/// Ratio of each gear. 
			/// </summary>
			property array<float>^ GearRatios;

			/// <summary>
			/// Final gear ratio. 
			/// </summary>
			property float GearFinalRatio;
			
			/// <summary>
			/// Time taken to complete gear change.
			/// </summary>
			property float GearSwitchTime;

			/// <summary>
			/// Value of revs/maxRevs required to trigger a gearup change. 
			/// </summary>
			property array<float>^ AutoBoxUpRatios;

			/// <summary>
			/// Value of revs/maxRevs required to trigger a geardown change.
			/// </summary>
			property array<float>^ AutoBoxDownRatios;

			/// <summary>
			/// Strength of clutch.
			/// </summary>
			property float ClutchStrength;

			/// <summary>
			/// Ackermann accuracy (1.0f achieves perfect ackermann angle, 0.0f uses raw input steer).
			/// </summary>
			property float AckermannAccuracy;
	};
};