#pragma once

#include "Tire Function Description.h"
#include "Shape Description.h"
#include "Spring Description.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class WheelShape;
		value class TireFunctionDescription;
		ref class Scene;
		ref class UserWheelContactModify;
		
		public ref class WheelShapeDescription : ShapeDescription
		{
			private:
				UserWheelContactModify^ _wheelContactModify;
			
			public:
				WheelShapeDescription();
				
				/// <summary>Returns true if the current settings are valid</summary>
				virtual bool IsValid() override;
				/// <summary>Sets the structure to the default</summary>
				virtual void SetToDefault() override;
				
				/// <summary>Gets or Sets the </summary>
				property UserWheelContactModify^ WheelContactModify
				{
					UserWheelContactModify^ get();
					void set( UserWheelContactModify^ value );
				}
				
				/// <summary>Gets or Sets the distance from wheel axle to a point on the contact surface</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the maximum extension distance of suspension along shape's -Y axis</summary>
				property float SuspensionTravel
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the data intended for car wheel suspension effects</summary>
				property SpringDescription Suspension
				{
					SpringDescription get();
					void set( SpringDescription value );
				}
				/// <summary>Gets or Sets the cubic hermite spline coefficients describing the longitudal tire force curve</summary>
				property TireFunctionDescription LongitudalTireForceFunction
				{
					TireFunctionDescription get();
					void set( TireFunctionDescription value );
				}
				/// <summary>Gets or Sets the cubic hermite spline coefficients describing the lateral tire force curve</summary>
				property TireFunctionDescription LateralTireForceFunction
				{
					TireFunctionDescription get();
					void set( TireFunctionDescription value );
				}
				/// <summary>Gets or Sets the inverse mass of the wheel</summary>
				property float InverseWheelMass
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets flags from WheelShapeFlags</summary>
				property WheelShapeFlag Flags
				{
					WheelShapeFlag get();
					void set( WheelShapeFlag value );
				}
				/// <summary>Gets or Sets the sum engine torque on the wheel axle</summary>
				property float MotorTorque
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the amount of torque applied for braking</summary>
				property float BrakeTorque
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the steering angle (around the shapes Y axis)</summary>
				property float SteerAngle
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxWheelShapeDesc* UnmanagedPointer
				{
					NxWheelShapeDesc* get();
				}
		};
	};
};