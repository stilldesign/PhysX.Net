#pragma once

#include "Controller.h"
#include "Enums.h"

using namespace System;

UsingFrameworkNamespace

class NxCapsuleController;

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class CapsuleControllerDescription;
		
		public ref class CapsuleController : Controller
		{
			internal:
				CapsuleController( NxCapsuleController* capsuleController, ControllerManager^ manager );
				
			public:
				/// <summary></summary>
				void SetStepOffset( float stepOffset );
				
				/// <summary>Gets the Radius of the Capsule Controller</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets the Height of the Capsule Controller</summary>
				property float Height
				{
					float get();
					void set( float value );
				}
				
				/// <summary></summary>
				property CapsuleClimbingMode ClimbingMode
				{
					CapsuleClimbingMode get();
					void set( CapsuleClimbingMode value );
				}
			
			internal:
				property NxCapsuleController* UnmanagedPointer
				{
					NxCapsuleController* get() new;
				}
		};
	};
};