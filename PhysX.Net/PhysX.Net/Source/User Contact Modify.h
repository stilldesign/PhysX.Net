#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		class InternalUserContactModify;
		ref class Shape;
		
		public ref class UserContactModify abstract
		{
			public:
				ref class ContactCallbackData;
				
				enum class NxContactConstraintChange
				{
					None = NxUserContactModify::NX_CCC_NONE,
					MinimumImpulse = NxUserContactModify::NX_CCC_MINIMPULSE,
					MaximumImpulse = NxUserContactModify::NX_CCC_MAXIMPULSE,
					Error = NxUserContactModify::NX_CCC_ERROR,
					Target = NxUserContactModify::NX_CCC_TARGET,
					LocalPosition0 = NxUserContactModify::NX_CCC_LOCALPOSITION0,
					LocalPosition1 = NxUserContactModify::NX_CCC_LOCALPOSITION1,
					LocalOrientation0 = NxUserContactModify::NX_CCC_LOCALORIENTATION0,
					LocalOrientation1 = NxUserContactModify::NX_CCC_LOCALORIENTATION1,
					StaticFriction0 = NxUserContactModify::NX_CCC_STATICFRICTION0,
					StaticFriction1 = NxUserContactModify::NX_CCC_STATICFRICTION1,
					DynamicFriction0 = NxUserContactModify::NX_CCC_DYNAMICFRICTION0,
					DynamicFriction1 = NxUserContactModify::NX_CCC_DYNAMICFRICTION1,
					Restitution = NxUserContactModify::NX_CCC_RESTITUTION
				};
			
			private:
				InternalUserContactModify* _internalUserContactModify;
				
			protected:
				UserContactModify();
			public:
				~UserContactModify();
			protected:
				!UserContactModify();
			
			public:
				virtual bool OnContactConstraint( unsigned int changeFlags, Shape^ shape0, Shape^ shape1, int featureIndex0, int featureIndex1, UserContactModify::ContactCallbackData^ data ) abstract;
				
			internal:
				property InternalUserContactModify* UnmanagedPointer
				{
					InternalUserContactModify* get();
				}
				
				//
				
			public:
				ref class ContactCallbackData
				{
					private:
						NxUserContactModify::NxContactCallbackData* _contactCallbackData;
					
					public:
						ContactCallbackData();
						~ContactCallbackData();
					protected:
						!ContactCallbackData();
					
					public:
						static explicit operator ContactCallbackData^( NxUserContactModify::NxContactCallbackData &data );
						static explicit operator NxUserContactModify::NxContactCallbackData( UserContactModify::ContactCallbackData^ data );
						
						property float MinimumImpulse
						{
							float get();
							void set( float value );
						}
						property float MaximumImpulse
						{
							float get();
							void set( float value );
						}
						property Vector3 Error
						{
							Vector3 get();
							void set( Vector3 value );
						}
						property Vector3 Target
						{
							Vector3 get();
							void set( Vector3 value );
						}
						property Vector3 LocalPosition0
						{
							Vector3 get();
							void set( Vector3 value );
						}
						property Vector3 LocalPosition1
						{
							Vector3 get();
							void set( Vector3 value );
						}
						property Quaternion LocalOrientation0
						{
							Quaternion get();
							void set( Quaternion value );
						}
						property Quaternion LocalOrientation1
						{
							Quaternion get();
							void set( Quaternion value );
						}
						property float StaticFriction0
						{
							float get();
							void set( float value );
						}
						property float StaticFriction1
						{
							float get();
							void set( float value );
						}
						property float DynamicFriction0
						{
							float get();
							void set( float value );
						}
						property float DynamicFriction1
						{
							float get();
							void set( float value );
						}
						property float Restitution
						{
							float get();
							void set( float value );
						}
				};
		};
		
		class InternalUserContactModify : public NxUserContactModify
		{
			private:
				gcroot<UserContactModify^> _userContactModify;
			
			public:
				InternalUserContactModify( gcroot<UserContactModify^> userContactModify );
				
				virtual bool onContactConstraint( NxU32 &changeFlags, const NxShape *shape0, const NxShape *shape1, const NxU32 featureIndex0, const NxU32 featureIndex1, NxUserContactModify::NxContactCallbackData &data );
		};
	};
};