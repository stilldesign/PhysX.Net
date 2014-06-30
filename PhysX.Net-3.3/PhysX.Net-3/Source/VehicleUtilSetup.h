#pragma once

namespace PhysX
{
	public ref class VehicleUtilSetup
	{
	public:
		/**
		\brief Reconfigure a PxVehicle4W instance as a three-wheeled car with tadpole config (2 front wheels, 1 rear wheel)

		\note The rear-left wheel is removed and the rear-right wheel is positioned at the centre of the rear axle.
		The suspension of the rear-right wheel is modified to support the entire mass of the front car while preserving its natural frequency and damping ratio.

		\param[in, out] wheelsSimData is the data describing the wheels/suspensions/tires of the vehicle.
		\param[in, out] wheelsDynData is the data describing the dynamic state of the wheels of the vehicle.
		\param[in, out] driveSimData is the data describing the drive model of the vehicle.
		*/
		//void PxVehicle4WEnable3WTadpoleMode(VehicleWheelsSimData wheelsSimData, PxVehicleWheelsDynData& wheelsDynData, PxVehicleDriveSimData4W& driveSimData);

		/**
		\brief Reconfigure a PxVehicle4W instance as a three-wheeled car with delta config (1 front wheel, 2 rear wheels)

		\note The front-left wheel is removed and the front-right wheel is positioned at the centre of the front axle.
		The suspension of the front-right wheel is modified to support the entire mass of the front car while preserving its natural frequency and damping ratio.

		\param[in, out] wheelsSimData is the data describing the wheels/suspensions/tires of the vehicle.
		\param[in, out] wheelsDynData is the data describing the dynamic state of the wheels of the vehicle.
		\param[in, out] driveSimData is the data describing the drive model of the vehicle.
		*/
		//void PxVehicle4WEnable3WDeltaMode(PxVehicleWheelsSimData& wheelsSimData, PxVehicleWheelsDynData& wheelsDynData, PxVehicleDriveSimData4W& driveSimData);

		/**
		\brief Compute the sprung masses of the suspension springs given given (i) the number of sprung masses,
		(ii) coordinates of the sprung masses, (iii) the center of mass offset of the rigid body, (iv) the
		total mass of the rigid body, and (v) the direction of gravity (0 for x-axis, 1 for y-axis, 2 for z-axis).

		\param[in] nbSprungMasses is the number of sprung masses of the vehicle.  This value corresponds to the number of wheels on the vehicle.
		\param[in] sprungMassCoordinates are the coordinates of the sprung masses relative to the actor. The array sprungMassCoordinates must be of
		length nbSprungMasses or greater.
		\param[in] centreOfMass is the coordinate of the center of mass of the rigid body relative to the actor.  This value corresponds to
		the value set by PxRigidBody::setCMassLocalPose.
		\param[in] totalMass is the total mass of all the sprung masses.  This value corresponds to the value set by PxRigidBody::setMass.
		\param[in] gravityDirection is an integer describing the direction of gravitational acceleration. A value of 0 corresponds to (0,0,-1),
		a value of 1 corresponds to (0,-1,0) and a value of 2 corresponds to (0,0,-1).
		\param[out] sprungMasses are the masses to set in the associated suspension data with PxVehicleSuspensionData::mSprungMass.  The sprungMasses array must be of length
		nbSprungMasses or greater. Each element in the sprungMasses array corresponds to the suspension located at the same array element in sprungMassCoordinates.
		The center of mass of the masses in sprungMasses with the coordinates in sprungMassCoordinates satisfy the specified centerOfMass.
		*/
		static array<float>^ ComputeSprungMasses(array<Vector3>^ sprungMassCoordinates, Vector3 centreOfMass, float totalMass, int gravityDirection);


		/**
		\brief Reconfigure the vehicle to reflect a new center of mass local pose that has been applied to the actor.  The function requires
		(i) the center of mass local pose that was last used to configure the vehicle and the vehicle's actor, (ii) the new center of mass local pose that
		has been applied to the vehicle's actor and will now be applied to the vehicle, and (iii) the direction of gravity (0 for x-axis, 1 for y-axis, 2 for z-axis)

		\param[in] oldCMassLocalPose is the center of mass local pose that was last used to configure the vehicle.
		\param[in] newCMassLocalPose is the center of mass local pose that will be used to configure the vehicle so that it matches the vehicle's actor.
		\param[in] gravityDirection is an integer describing the direction of gravitational acceleration. A value of 0 corresponds to (0,0,-1),
		a value of 1 corresponds to (0,-1,0) and a value of 2 corresponds to (0,0,-1).
		\param[in,out] vehicle is the vehicle to be updated with a new center of mass local pose.

		\note This function does not update the center of mass of the vehicle actor.  That needs to updated separately with PxRigidBody::setCMassLocalPose

		\note The suspension sprung masses are updated so that the natural frequency of the springs are preserved.  This involves altering the stiffness of the
		suspension springs.
		*/
		//void PxVehicleUpdateCMassLocalPose(const PxTransform& oldCMassLocalPose, const PxTransform& newCMassLocalPose, const PxU32 gravityDirection, PxVehicleWheels* vehicle);
	};
};