#pragma once

#include "Fluid Emitter.h"



namespace StillDesign
{
	namespace PhysX
	{

		public ref class FluidEmitterFlagsWrapper sealed
		{
		public:
			#define WRAPPER_PROPERTY( name ) \
				property bool name { \
					bool get() { return _emitter->GetFlag( FluidEmitterFlag::name ); } \
					void set(bool  value) { _emitter->SetFlag( FluidEmitterFlag::name, value); } \
				}

			WRAPPER_PROPERTY( Visualization )
			WRAPPER_PROPERTY( ForceOnBody )
			WRAPPER_PROPERTY( AddBodyVelocity )
			WRAPPER_PROPERTY( Enabled )

			#undef WRAPPER_PROPERTY

		internal:
			FluidEmitterFlagsWrapper( FluidEmitter^ emitter )
				: _emitter( emitter )
			{
				if ( emitter == nullptr )
					throw gcnew ArgumentNullException( "emitter" );
			}

		private:
			FluidEmitter^ _emitter;
		};

	}
}