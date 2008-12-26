#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		class InternalFluidUserNotify;
		ref class Actor;
		ref class Fluid;
		ref class FluidEmitter;
		
		public ref class FluidUserNotify abstract
		{
			private:
				InternalFluidUserNotify* _fluidUserNotify;
				
			protected:
				FluidUserNotify();
			public:
				~FluidUserNotify();
			protected:
				!FluidUserNotify();
			
			public:
				virtual bool OnEmitterEvent( FluidEmitter^ emitter, FluidEmitterEventType eventType ) abstract;
				virtual bool OnEvent( Fluid^ fluid, FluidEventType eventType ) abstract;
				
			internal:
				property InternalFluidUserNotify* UnmanagedPointer
				{
					InternalFluidUserNotify* get();
				}
		};
		
		class InternalFluidUserNotify : public NxFluidUserNotify
		{
			private:
				gcroot<FluidUserNotify^> _fluidUserNotify;
			
			public:
				InternalFluidUserNotify( gcroot<FluidUserNotify^> FluidUserNotify );
				
				virtual bool onEmitterEvent( NxFluidEmitter &emitter, NxFluidEmitterEventType eventType );
				virtual bool onEvent( NxFluid &fluid, NxFluidEventType eventType );
		};
	};
};