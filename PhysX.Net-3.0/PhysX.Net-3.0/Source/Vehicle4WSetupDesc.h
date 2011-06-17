#pragma once

#include "FilterData.h"

namespace PhysX
{
	ref class Vehicle4WSimulationData;
	ref class RigidDynamic;
	ref class Geometry;
	ref class Material;
	ref class Vehicle4WSetupDescGeometry;
	ref class Physics;

	public ref class Vehicle4WSetupDesc
	{
		public:
			property PhysX::Physics^ Physics;

			property Vehicle4WSimulationData^ SimulationData;

			property FilterData VehicleQueryFilterData;

			property RigidDynamic^ VehicleActor;

			property Geometry^ FrontLeftWheelGeometry;
			property Geometry^ FrontRightWheelGeometry;
			property Geometry^ RearLeftWheelGeometry;
			property Geometry^ RearRightWheelGeometry;

			property Material^ WheelMaterial;

			property FilterData WheelCollisionFilterData;

			property array<Vehicle4WSetupDescGeometry^>^ Geometries;

			property PhysX::Material^ ChassisMaterial;

			property FilterData ChassisCollisionFilterData;
	};

	public ref class Vehicle4WSetupDescGeometry
	{
		public:
			property Geometry^ ChassisGeometry;
			property Matrix ChassisLocalPose;
	};
};