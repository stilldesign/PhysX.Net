#pragma once


namespace PhysX
{
	ref class Actor;
	ref class Shape;
	ref class Material;

	/// <summary>
	/// Structure containing data describing the non-persistent state of each suspension/wheel/tire unit. This structure is filled out in PxVehicleUpdates and PxVehicleUpdateSingleVehicleAndStoreTelemetryData.
	/// </summary>
	public ref class VehicleWheelQueryResult
	{
	internal:
		static VehicleWheelQueryResult^ ToManaged(PxWheelQueryResult* unmanaged);

	public:
		/// <summary>
		/// Start point of suspension line raycast used in raycast completed immediately before PxVehicleUpdates.
		/// </summary>
		property Vector3 SuspensionLineStart;

		/// <summary>
		/// Directions of suspension line raycast used in raycast completed immediately before PxVehicleUpdates.
		/// </summary>
		property Vector3 SuspensionLineDirection;

		/// <summary>
		/// Lengths of suspension line raycast used in raycast completed immediately before PxVehicleUpdates.
		/// </summary>
		property float SuspensionLineLength;

		/// <summary>
		/// If suspension travel limits forbid the wheel from touching the drivable surface then isInAir is true. 
		/// </summary>
		property bool IsInAir;

		/// <summary>
		/// Actor instance of the driving surface under the corresponding vehicle wheel.
		/// </summary>
		property Actor^ TireContactActor;

		/// <summary>
		/// Shape instance of the driving surface under the corresponding vehicle wheel.
		/// </summary>
		property Shape^ TireContactShape;

		/// <summary>
		/// Material instance of the driving surface under the corresponding vehicle wheel.
		/// </summary>
		property Material^ TireSurfaceMaterial;

		/// <summary>
		/// Surface type integer that corresponds to the mapping between tireSurfaceMaterial and integer as described in PxVehicleDrivableSurfaceToTireFrictionPairs.
		/// </summary>
		property int TireSurfaceType;

		/// <summary>
		/// Point on the drivable surface hit by the most recent suspension raycast.
		/// </summary>
		property Vector3 TireContactPoint;

		/// <summary>
		/// Normal on the drivable surface at the hit point of the most recent suspension raycast.
		/// </summary>
		property Vector3 TireContactNormal;
 
		/// <summary>
		/// Friction experienced by the tire for the combination of tire type and surface type after accounting for the friction vs slip graph.
		/// </summary>
		property float TireFriction;

		/// <summary>
		/// Compression of the suspension spring.
		/// </summary>
		property float SuspensionJounce;
		
		/// <summary>
		/// Magnitude of force applied by the suspension spring along the direction of suspension travel.
		/// </summary>
		property float SuspensionSpringForce;

		/// <summary>
		/// Forward direction of the wheel/tire accounting for steer/toe/camber angle projected on to the contact plane of the drivable surface.
		/// </summary>
		property Vector3 TireLongitudinalDirection;

		/// <summary>
		/// Lateral direction of the wheel/tire accounting for steer/toe/camber angle projected on to the contact plan of the drivable surface.
		/// </summary>
		property Vector3 TireLateralDirection;

		/// <summary>
		/// Longitudinal slip of the tire.
		/// </summary>
		property float LongitudinalSlip;

		/// <summary>
		/// Lateral slip of the tire.
		/// </summary>
		property float LateralSlip;

		/// <summary>
		/// Steer angle of the wheel about the "up" vector accounting for input steer and toe and, if applicable, Ackermann steer correction.
		/// </summary>
		property float SteerAngle;

		/// <summary>
		/// Local pose of the wheel.
		/// </summary>
		property Matrix LocalPose;
	};
}