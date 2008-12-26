#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		class InternalWheelContactModify;
		ref class UserWheelContactModifyData;
		ref class WheelShape;
		ref class Shape;
		ref class Scene;
		ref class Material;
		
		public ref class UserWheelContactModify abstract
		{
			private:
				InternalWheelContactModify* _internalWheelContactModify;
				
			protected:
				UserWheelContactModify();
			
			public:	
				virtual bool OnWheelContact( UserWheelContactModifyData^ data ) abstract;
				
			internal:
				property InternalWheelContactModify* UnmanagedPointer
				{
					InternalWheelContactModify* get();
				}
		};
		
		//
		
		public ref class UserWheelContactModifyData
		{
			private:
				WheelShape^ _wheelShape;
				Shape^ _otherShape;
				
				Vector3 _contactPoint;
				Vector3 _contactNormal;
				float _contactPosition;
				float _normalForce;
				Material^ _otherShapeMaterial;
				int _otherShapeFeatureIndex;
			
			public:
				UserWheelContactModifyData( StillDesign::PhysX::WheelShape^ wheelShape, Shape^ otherShape );
				
				property StillDesign::PhysX::WheelShape^ WheelShape
				{
					StillDesign::PhysX::WheelShape^ get();
				}
				property StillDesign::PhysX::Shape^ OtherShape
				{
					StillDesign::PhysX::Shape^ get();
				}
				
				property Vector3 ContactPoint
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property Vector3 ContactNormal
				{
					Vector3 get();
					void set( Vector3 value );
				}
				property float ContactPosition
				{
					float get();
					void set( float value );
				}
				property float NormalForce
				{
					float get();
					void set( float value );
				}
				property Material^ OtherShapeMaterial
				{
					Material^ get();
					void set( Material^ value );
				}
				property int OtherShapeFeatureIndex
				{
					int get();
					void set( int value );
				}
		};
		
		//
		
		class InternalWheelContactModify : public NxUserWheelContactModify
		{
			private:
				gcroot<UserWheelContactModify^> _wheelContactModify;
			
			public:
				InternalWheelContactModify( UserWheelContactModify^ wheelContactModify );
				
				virtual bool onWheelContact( NxWheelShape* wheelShape, NxVec3& contactPoint, NxVec3& contactNormal, NxReal& contactPosition, NxReal& normalForce, NxShape* otherShape, NxMaterialIndex& otherShapeMaterialIndex, NxU32 otherShapeFeatureIndex );
		};
	};
};