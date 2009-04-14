#pragma once

#include "Controller Description.h"
#include "Enums.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public ref class CapsuleControllerDescription : ControllerDescription
		{
			public:
				CapsuleControllerDescription( float radius, float height );
				~CapsuleControllerDescription();
			protected:
				!CapsuleControllerDescription();
				
			public:
				/// <summary>The radius of the capsule</summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary>The height of the controller</summary>
				property float Height
				{
					float get();
					void set( float value );
				}
				
				/// <summary>The climbing mode</summary>
				property CapsuleClimbingMode ClimbingMode
				{
					CapsuleClimbingMode get();
					void set( CapsuleClimbingMode value );
				}
			
			internal:
				property NxCapsuleControllerDesc* UnmanagedPointer
				{
					NxCapsuleControllerDesc* get() new;
				}
		};
	};
};