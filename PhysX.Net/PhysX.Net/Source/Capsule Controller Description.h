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
				/// <summary></summary>
				property float Radius
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
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
				property NxCapsuleControllerDesc* UnmanagedPointer
				{
					NxCapsuleControllerDesc* get() new;
				}
		};
	};
};