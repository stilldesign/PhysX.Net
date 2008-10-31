using System;
using System.Collections.Generic;

using Microsoft.Xna.Framework;

using StillDesign.PhysX;

namespace StillDesign
{
	public class Vehicle
	{
		private Actor _vehicleBodyActor;

		private WheelShape _leftFront;
		private WheelShape _leftRear;
		private WheelShape _rightFront;
		private WheelShape _rightRear;

		public Vehicle( Demo demo )
		{
			// Create a 2 ton car with 4 wheels
			BodyDescription bodyDesc = new BodyDescription();
				bodyDesc.Mass = 2000;
				//bodyDesc.MassLocalPose = Matrix.CreateTranslation( 0, -1.5f, 0 ); // Seems not to be working

			ActorDescription actorDesc = new ActorDescription();
				actorDesc.BodyDescription = bodyDesc;
				actorDesc.Shapes.Add( new BoxShapeDescription( 5, 3, 7 ) );
				actorDesc.GlobalPose = Matrix.CreateTranslation( -50, 5, 70 );

			_vehicleBodyActor = demo.Scene.CreateActor( actorDesc );
				_vehicleBodyActor.SetCenterOfMassOffsetLocalPosition( new Vector3( 0, -1.5f, 0 ) ); // Move the COM to the bottom of the vehicle to stop it flipping over so much

			//

			WheelShapeDescription leftFrontDesc = new WheelShapeDescription();
				leftFrontDesc.Radius = 0.8f;
				leftFrontDesc.SuspensionTravel = 1;
				leftFrontDesc.LocalPosition = new Vector3( -2.5f, -1, 3 );

			WheelShapeDescription leftRearDesc = new WheelShapeDescription();
				leftRearDesc.Radius = 0.8f;
				leftRearDesc.SuspensionTravel = 1;
				leftRearDesc.LocalPosition = new Vector3( -2.5f, -1, -3 );

			WheelShapeDescription rightFrontDesc = new WheelShapeDescription();
				rightFrontDesc.Radius = 0.8f;
				rightFrontDesc.SuspensionTravel = 1;
				rightFrontDesc.LocalPosition = new Vector3( 2.5f, -1, 3 );

			WheelShapeDescription rightRearDesc = new WheelShapeDescription();
				rightRearDesc.Radius = 0.8f;
				rightRearDesc.SuspensionTravel = 1;
				rightRearDesc.LocalPosition = new Vector3( 2.5f, -1, -3 );

			_leftFront = _vehicleBodyActor.CreateShape( leftFrontDesc ) as WheelShape;
			_leftRear = _vehicleBodyActor.CreateShape( leftRearDesc ) as WheelShape;
			_rightFront = _vehicleBodyActor.CreateShape( rightFrontDesc ) as WheelShape;
			_rightRear = _vehicleBodyActor.CreateShape( rightRearDesc ) as WheelShape;
		}

		public void Accelerate( float additionalMotorTorque )
		{
			_leftRear.MotorTorque += additionalMotorTorque;
			_rightRear.MotorTorque += additionalMotorTorque;

			_vehicleBodyActor.WakeUp();
		}
		public void Turn( float additionalSteeringAngle )
		{
			// Both wheels will have the same steering angle
			float currentAngle = _leftFront.SteeringAngle;

			// About 34 degrees of max steering lock
			float newAngle = Clamp( currentAngle + additionalSteeringAngle, -0.6f, 0.6f );

			_leftFront.SteeringAngle = _rightFront.SteeringAngle = newAngle;
		}

		private float Clamp( float value, float min, float max )
		{
			if( value < min )
				return min;
			if( value > max )
				return max;

			return value;
		}

		public WheelShape LeftFront
		{
			get
			{
				return _leftFront;
			}
		}
		public WheelShape LeftRear
		{
			get
			{
				return _leftRear;
			}
		}
		public WheelShape RightFront
		{
			get
			{
				return _rightFront;
			}
		}
		public WheelShape RightRear
		{
			get
			{
				return _rightRear;
			}
		}
	}
}