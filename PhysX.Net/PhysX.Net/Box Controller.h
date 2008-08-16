#pragma once

#include <NxBoxController.h> 
#include "Controller.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		
		ref class BoxControllerDescription;
		
		public ref class BoxController : Controller
		{
			internal:
				BoxController( NxBoxController* boxController, ControllerManager^ manager );
				
			public:
				/// <summary>Gets or Sets the extents of box</summary>
				property Vector3 Extents
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary>Gets or Sets the size of box</summary>
				property Vector3 Size
				{
					Vector3 get();
					void set( Vector3 value );
				}
				/// <summary></summary>
				property float StepOffset
				{
					void set( float value );
				}
			
			internal:
				property NxBoxController* UnmanagedPointer
				{
					NxBoxController* get() new;
				}
		};
	};
};