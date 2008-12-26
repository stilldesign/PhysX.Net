#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Shape;
		
		public ref class WheelContactData
		{
			private:
				NxWheelContactData* _contactData;
				
				Shape^ _shape;
			
			protected:
				WheelContactData();
			internal:
				WheelContactData( NxWheelContactData* contactData, Shape^ shape );
			public:
				~WheelContactData();
			protected:
				!WheelContactData();
				
			public:
				/// <summary>Gets the contact shape</summary>
				property Shape^ ContactShape
				{
					Shape^ get();
				}
				
				/// <summary>Gets the point of contact between the wheel shape and the ground</summary>
				property Vector3 ContactPoint
				{
					Vector3 get();
				}
				/// <summary>Gets normal at the point of contact</summary>
				property Vector3 ContactNormal
				{
					Vector3 get();
				}
				/// <summary>Gets the direction the wheel is pointing in</summary>
				property Vector3 LongitudalDirection
				{
					Vector3 get();
				}
				/// <summary>Gets the sideways direction for the wheel(at right angles to the longitudinal direction)</summary>
				property Vector3 LateralDirection
				{
					Vector3 get();
				}
				/// <summary>Gets the magnitude of the force being applied for the contact</summary>
				property float ContactForce
				{
					float get();
				}
				property float LongitudalSlip
				{
					float get();
				}
				property float LateralSlip
				{
					float get();
				}
				/// <summary>Gets the clipped impulses applied at the wheel</summary>
				property float LongitudalImpulse
				{
					float get();
				}
				property float LateralImpulse
				{
					float get();
				}
				/// <summary>Gets the material index of the shape in contact with the wheel</summary>
				property unsigned int OtherShapeMaterialIndex
				{
					unsigned int get();
				}
				/// <summary>Gets the distance on the spring travel distance where the wheel would end up if it was resting on the contact point</summary>
				property float ContactPosition
				{
					float get();
				}
				
				property WheelContactData^ Empty
				{
					static WheelContactData^ get();
				}
		};
	};
};