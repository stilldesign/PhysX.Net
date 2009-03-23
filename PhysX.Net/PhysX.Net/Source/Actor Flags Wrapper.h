#pragma once

#include "Actor.h"

namespace StillDesign
{
	namespace PhysX
	{
		[System::ComponentModel::TypeConverter( System::ComponentModel::ExpandableObjectConverter::typeid )]
		public ref class ActorFlagsWrapper
		{
			private:
				Actor^ _actor;
				
			public:
				#define WRAPPER_PROPERTY( name ) \
					property bool name { \
						bool get() { return _actor->ReadActorFlag( ActorFlag::name ); } \
						void set( bool value ) { \
							if ( value ) \
								_actor->RaiseActorFlag( ActorFlag::name ); \
							else \
								_actor->ClearActorFlag( ActorFlag::name ); \
						} \
					}
				
				WRAPPER_PROPERTY( DisableCollision )
				WRAPPER_PROPERTY( DisableResponse )
				WRAPPER_PROPERTY( LockCenterOfMass )
				WRAPPER_PROPERTY( DisableFluidCollision )
				WRAPPER_PROPERTY( ContactModification )
				WRAPPER_PROPERTY( ForceConeFriction )
				WRAPPER_PROPERTY( UserActorPairFiltering )
				
				#undef WRAPPER_PROPERTY
			
			internal:
				ActorFlagsWrapper( Actor^ actor)
				{
					if ( actor == nullptr )
						throw gcnew System::ArgumentNullException( "actor" );
					
					_actor = actor;
			}
		};
	}
}