using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX;

namespace StillDesign.PhysX.Samples
{
	public partial class VehicleSample
	{
		private Actor _vehicleBodyActor;

		public VehicleSample(Scene scene)
		{
			LoadVehiclePhysics(scene);
		}

		public void Accelerate(float additionalMotorTorque)
		{
			this.LeftRear.MotorTorque += additionalMotorTorque;
			this.RightRear.MotorTorque += additionalMotorTorque;

			_vehicleBodyActor.WakeUp();
		}
		public void Turn(float additionalSteeringAngle)
		{
			// Both wheels will have the same steering angle
			float currentAngle = this.LeftFront.SteeringAngle;

			// About 34 degrees of max steering lock
			float newAngle = Mathematics.Clamp(currentAngle + additionalSteeringAngle, -0.6f, 0.6f);

			this.LeftFront.SteeringAngle = this.RightFront.SteeringAngle = newAngle;
		}

		public WheelShape LeftFront { get; private set; }
		public WheelShape LeftRear { get; private set; }
		public WheelShape RightFront { get; private set; }
		public WheelShape RightRear { get; private set; }
	}
}