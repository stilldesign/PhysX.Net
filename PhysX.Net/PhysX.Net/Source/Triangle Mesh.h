#pragma once

#include "Enums.h"
#include "Bounds.h"
#include "IDisposable.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Core;
		ref class TriangleMeshDescription;
		
		public ref class TriangleMesh : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxTriangleMesh* _triangleMesh;
				
				Core^ _core;
				
				String^ _name;
				
			internal:
				TriangleMesh( NxTriangleMesh* triangleMesh, StillDesign::PhysX::Core^ core );
			public:
				~TriangleMesh();
			protected:
				!TriangleMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary></summary>
				TriangleMeshDescription^ SaveToDescription();
				
				/// <summary>Retrieves the number of elements of a given internal array</summary>
				unsigned int ElementCount( unsigned int submeshIndex, InternalArray internalArray );
				/// <summary>Retrieves the format of a given internal array</summary>
				InternalFormat ElementFormat( unsigned int submeshIndex, InternalArray internalArray );
				
				/// <summary>Retrieves the stride value of a given internal array</summary>
				unsigned int StrideSize( unsigned int submeshIndex, InternalArray internalArray );
				/// <summary>Retrieves the number of PhysX processor pages into which a mesh is divided</summary>
				unsigned int PageCount();
				/// <summary>Retrieves the bounding box of a PhysX processor mesh page in the local space of the mesh</summary>
				Bounds3 PageBoundingBox( unsigned int pageIndex );
				
				/// <summary>Load the triangle mesh from a stream</summary>
				bool LoadFromStream( Stream^ stream );
				
				/// <summary>Returns material index of given triangle</summary>
				NxMaterialIndex GetTriangleMaterialIndex( unsigned int triangleID );
				
				/// <summary>The name of the triangle mesh</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the core the owns the triangle mesh</summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				
				/// <summary>Returns the reference count for shared meshes</summary>
				property int ReferencedCount
				{
					int get();
				}
			
			internal:
				property NxTriangleMesh* UnmanagedPointer
				{
					NxTriangleMesh* get();
				}
		};
	};
};