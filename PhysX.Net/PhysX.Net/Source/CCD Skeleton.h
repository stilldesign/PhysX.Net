#pragma once

#include "IDisposable.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class SimpleTriangleMesh;
		ref class Core;

		public ref class CCDSkeleton : IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxCCDSkeleton* _skeleton;
				
				StillDesign::PhysX::Core^ _core;
				
				String^ _name;
				
			internal:
				CCDSkeleton( NxCCDSkeleton* skeleton, StillDesign::PhysX::Core^ core );
			public:
				~CCDSkeleton();
			protected:
				!CCDSkeleton();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary>Saves out CCDSkeleton data</summary>
				array<Byte>^ Save();
				
				/// <summary>Gets the core the skeleton was owned by</summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}

				/// <summary>Gets or Sets the name of the skeleton</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the reference count for shared meshes</summary>
				property int ReferencedCount
				{
					int get();
				}
				
				property int DataSize
				{
					int get();
				}
			
			internal:
				property NxCCDSkeleton* UnmanagedPointer
				{
					NxCCDSkeleton* get();
				}
		};
	};
};