
#pragma once

#include "Actor.h"



namespace StillDesign
{
	namespace PhysX
	{

		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class BodyFlagsWrapper
		{
		public:
			#define WRAPPER_PROPERTY( name ) \
				property bool name { \
					bool get() { return _actor->ReadBodyFlag( BodyFlag::name ); } \
					void set( bool value ) { \
						if ( value ) \
							_actor->RaiseBodyFlag( BodyFlag::name ); \
						else \
							_actor->ClearBodyFlag( BodyFlag::name ); \
					} \
				}

			WRAPPER_PROPERTY( DisableGravity )
			WRAPPER_PROPERTY( FrozenPositionX )
			WRAPPER_PROPERTY( FrozenPositionY )
			WRAPPER_PROPERTY( FrozenPositionZ )
			WRAPPER_PROPERTY( FrozenRotationX )
			WRAPPER_PROPERTY( FrozenRotationY )
			WRAPPER_PROPERTY( FrozenRotationZ )
			WRAPPER_PROPERTY( FrozenPosition )
			WRAPPER_PROPERTY( FrozenRotation )
			WRAPPER_PROPERTY( Frozen )
			WRAPPER_PROPERTY( Kinematic )
			WRAPPER_PROPERTY( Visualization )
			//WRAPPER_PROPERTY( PoseSleepTest )
			WRAPPER_PROPERTY( FilterSleepVelocity )
			WRAPPER_PROPERTY( EnergySleepTest )

			#undef WRAPPER_PROPERTY

		internal:
			BodyFlagsWrapper( Actor^ actor)
				: _actor( actor )
			{
				if ( actor == nullptr )
					throw gcnew System::ArgumentNullException( "actor" );
			}

		private:
			Actor^ _actor;
		};

	}
}