using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	partial class VehicleSample
	{
		private void LoadVehiclePhysics(Scene scene)
		{
			// Create a 2 ton car with 4 wheels
			BodyDescription bodyDesc = new BodyDescription()
			{
				Mass = 2000
			};
			//bodyDesc.MassLocalPose = Matrix.CreateTranslation( 0, -1.5f, 0 ); // Seems not to be working

			ActorDescription actorDesc = new ActorDescription()
			{
				BodyDescription = bodyDesc,
				Shapes = { new BoxShapeDescription(5, 3, 7) },
				GlobalPose = Matrix.Translation(-50, 5, -70)
			};

			_vehicleBodyActor = scene.CreateActor(actorDesc);
			_vehicleBodyActor.SetCenterOfMassOffsetLocalPosition(new Vector3(0, -1.5f, 0)); // Move the COM to the bottom of the vehicle to stop it flipping over so much

			//

			WheelShapeDescription leftFrontDesc = new WheelShapeDescription()
			{
				Radius = 0.8f,
				SuspensionTravel = 1,
				LocalPosition = new Vector3(-2.5f, -1, 3)
			};

			WheelShapeDescription leftRearDesc = new WheelShapeDescription()
			{
				Radius = 0.8f,
				SuspensionTravel = 1,
				LocalPosition = new Vector3(-2.5f, -1, -3),
			};

			WheelShapeDescription rightFrontDesc = new WheelShapeDescription()
			{
				Radius = 0.8f,
				SuspensionTravel = 1,
				LocalPosition = new Vector3(2.5f, -1, 3)
			};

			WheelShapeDescription rightRearDesc = new WheelShapeDescription()
			{
				Radius = 0.8f,
				SuspensionTravel = 1,
				LocalPosition = new Vector3(2.5f, -1, -3)
			};

			this.LeftFront = _vehicleBodyActor.CreateShape(leftFrontDesc) as WheelShape;
			this.LeftRear = _vehicleBodyActor.CreateShape(leftRearDesc) as WheelShape;
			this.RightFront = _vehicleBodyActor.CreateShape(rightFrontDesc) as WheelShape;
			this.RightRear = _vehicleBodyActor.CreateShape(rightRearDesc) as WheelShape;
		}
	}
}