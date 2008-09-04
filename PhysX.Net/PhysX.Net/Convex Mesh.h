#pragma once

#include "Enums.h"
#include "IDisposable.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		ref class Core;
		ref class ConvexMeshDescription;
		value class ConvexMeshMassInformation;
		
		public ref class ConvexMesh : StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxConvexMesh* _convexMesh;
				StillDesign::PhysX::Core^ _core;
				
				String^ _name;
			
			internal:	
				ConvexMesh( NxConvexMesh* convexMesh, StillDesign::PhysX::Core^ core );
			public:
				~ConvexMesh();
			protected:
				!ConvexMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Saves the mesh to a descriptor</summary>
				ConvexMeshDescription^ SaveToDescription();
				/// <summary>Load the contents of this mesh from the provided stream</summary>
				/// <param name="stream">Stream to load this mesh from</param>
				void LoadFromStream( Stream^ stream );
				
				int InternalArrayCount( int submeshIndex, InternalArray interalArray );
				InternalFormat InternalArrayFormat( int submeshIndex, InternalArray internalArray );
				
				/// <summary>Gets the core the convex mesh was created in</summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				
				/// <summary>Gets or Sets the name of the convex mesh</summary>
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
				/// <summary>Gets the mass properties of the mesh</summary>
				property ConvexMeshMassInformation MassInformation
				{
					ConvexMeshMassInformation get();
				}
			
			internal:
				property NxConvexMesh* UnmanagedPointer
				{
					NxConvexMesh* get();
				}
		};
		
		public value class ConvexMeshMassInformation
		{
			private:
				float _mass;
				Matrix _localInertia;
				Vector3 _localCenterOfMass;
			
			public:
				/// <summary>Gets or Sets the mass of the mesh</summary>
				property float Mass
				{
					float get();
					void set( float value );
				}
				/// <summary>Gets or Sets the inertia tensor in mesh local space</summary>
				property Matrix LocalInertia
				{
					Matrix get();
					void set( Matrix value );
				}
				/// <summary>Gets or Sets the position of center of mass in mesh local space</summary>
				property Vector3 LocalCenterOfMass
				{
					Vector3 get();
					void set( Vector3 value );
				}
		};
	};
};