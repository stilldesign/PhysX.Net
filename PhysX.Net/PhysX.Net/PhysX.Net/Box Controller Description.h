#pragma once

#include "Controller Description.h"

using namespace System;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public ref class BoxControllerDescription : ControllerDescription
		{
			public:
				BoxControllerDescription( float sizeX, float sizeY, float sizeZ );
				BoxControllerDescription( Vector3 size );
				BoxControllerDescription( Vector3 size, Vector3 position );
				~BoxControllerDescription();
			protected:
				!BoxControllerDescription();
			
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
				
			internal:
				/// <summary>Gets a Pointer to the Unmanaged Box Controller Description</summary>
				property NxBoxControllerDesc* UnmanagedPointer
				{
					NxBoxControllerDesc* get() new;
				}
		};
	};
};