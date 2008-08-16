#pragma once

#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class MeshData;
		
		public ref class ImplicitScreenMeshDescription : IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxImplicitScreenMeshDesc* _implicitScreenMesh;
				
				StillDesign::PhysX::MeshData^ _meshData;
				
				Object^ _userData;
			
			public:
				ImplicitScreenMeshDescription();
				~ImplicitScreenMeshDescription();
			protected:
				!ImplicitScreenMeshDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				void SetToDefault();
				bool IsValid();
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				property float ScreenSpacing
				{
					float get();
					void set( float value );
				}
				property int HierarchyLevels
				{
					int get();
					void set( int value );
				}
				property float ParticleRadius
				{
					float get();
					void set( float value );
				}
				property float Threshold
				{
					float get();
					void set( float value );
				}
				property int DepthSmoothing
				{
					int get();
					void set( int value );
				}
				property int SilhouetteSmoothing
				{
					int get();
					void set( int value );
				}
				property int Width
				{
					int get();
					void set( int value );
				}
				property int Height
				{
					int get();
					void set( int value );
				}
				property Matrix ViewProjectionMatrix
				{
					Matrix get();
					void set( Matrix value );
				}
				property Byte TriangleWindingPositive
				{
					Byte get();
					void set( Byte value );
				}
				property StillDesign::PhysX::MeshData^ MeshData
				{
					StillDesign::PhysX::MeshData^ get();
					void set( StillDesign::PhysX::MeshData^ value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxImplicitScreenMeshDesc* UnmanagedPointer
				{
					NxImplicitScreenMeshDesc* get();
				}
		};
	};
};