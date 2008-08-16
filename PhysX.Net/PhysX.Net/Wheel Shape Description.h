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
				
			public:
				property UserWheelContactModify^ WheelContactModify
				{
					UserWheelContactModify^ get();
					void set( UserWheelContactModify^ value );
				}
				
				property float Radius
				{
					float get();
					void set( float value );
				}
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