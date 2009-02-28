#pragma once

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Controller;
		
		public ref class ControllersHit
		{
			private:
				NxControllersHit* _controllersHit;
				
				Controller^ _controller;
				Controller^ _other;
			
			public:
				ControllersHit();
			internal:
				ControllersHit( const NxControllersHit controllersHit );
			public:
				~ControllersHit();
			protected:
				!ControllersHit();
				
			public:
				/// <summary>Gets the current controller</summary>
				property StillDesign::PhysX::Controller^ Controller
				{
					StillDesign::PhysX::Controller^ get();
				}
				/// <summary>Gets the touched controller</summary>
				property StillDesign::PhysX::Controller^ Other
				{
					StillDesign::PhysX::Controller^ get();
				}
				
			internal:
				property NxControllersHit* UnmanagedPointer
				{
					NxControllersHit* get();
				}
		};
	};
};