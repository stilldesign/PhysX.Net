#pragma once

#include "IDisposable.h"

class NxSoftBodyMesh;

namespace StillDesign
{
	namespace PhysX
	{
		ref class SoftBodyMeshDescription;
		ref class Core;
		
		public ref class SoftBodyMesh : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxSoftBodyMesh* _softBodyMesh;
				Core^ _core;
				
				String^ _name;
				
			internal:
				SoftBodyMesh( NxSoftBodyMesh* softBodyMesh, StillDesign::PhysX::Core^ core );
			public:
				~SoftBodyMesh();
			protected:
				!SoftBodyMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				SoftBodyMeshDescription^ SaveToDescription();
				
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the Number of Times the SoftBodyMesh is Used in a SoftBody</summary>
				property int ReferencedCount
				{
					int get();
				}
			
			internal:
				property NxSoftBodyMesh* UnmanagedPointer
				{
					NxSoftBodyMesh* get();
				}
		};
	};
};