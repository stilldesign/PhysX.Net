#pragma once

#include "Wheel Shape Description.h"
#include "Tire Function Description.h"
#include "Wheel Contact Data.h"

#include "Shape.h"
#include "Shape Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class UserWheelContactModify;
		ref class Actor;
		
		public ref class WheelShape : Shape
		{
			private:
				UserWheelContactModify^ _wheelContactModify;
			
			internal:
				WheelShape( NxWheelShape* wheelShape );
				
			public:	
				WheelShapeDescription^ SaveToDescription();
				
				/// <summary>Return contact information for the wheel</summary>
				WheelContactData^ GetContactData();
				
				/// <summary>Gets or Sets the callback function used for wheel contact modification on the WheelShape</summary>
				property UserWheelContactModify^ WheelContactModify
				{
					UserWheelContactModify^ get();
					void set( UserWheelContactModify^ value );
				}
				
				/// <summary>Gets or Sets the Distance From the Wheel Axle to a Point on the Contact Surface</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the Maximum Extension Distance of Suspension Along Shape's -Y Axis. The Minimum Extension is Always 0.0</summary>
				property float SuspensionTravel
				{
					float get();
					void set( float value );
				}
				property SpringDescription Suspension
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				property TireFunctionDescription LongitudalTireForceFunction
				{
					TireFunctionDescription get();
					void set( TireFunctionDescription value );
				}
				property TireFunctionDescription LateralTireForceFunction
				{
					TireFunctionDescription get();
					void set( TireFunctionDescription value );
				}
				property float InverseWheelMass
				{
					float get();
					void set( float value );
				}
				property WheelShapeFlag Flags
				{
					WheelShapeFlag get();
					void set( WheelShapeFlag value );
				}
				property float MotorTorque
				{
					float get();
					void set( float value );
				}
				property float BrakeTorque
				{
					float get();
					void set( float value );
				}
				property float SteeringAngle
				{
					float get();
					void set( float value );
				}
				
				/// <summary>Gets or Sets Current Axle Rotation Speed</summary>
				/// <remarks>WheelShapeFlags.AxleSpeedOverride Flag Must be Set For This to Have Effect</remarks>
				property float AxleSpeed
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxWheelShape* UnmanagedPointer
				{
					NxWheelShape* get() new;
				}
		};
	};
};