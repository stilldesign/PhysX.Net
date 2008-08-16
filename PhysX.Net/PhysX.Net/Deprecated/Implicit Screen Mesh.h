#pragma once

#include "Dependency.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class MeshData;
		ref class Scene;
		ref class Fluid;
		
		public ref class ImplicitScreenMesh : Dependency, StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
				
			private:
				NxImplicitScreenMesh* _implicitScreenMesh;
				
				StillDesign::PhysX::Fluid^ _fluid;
				StillDesign::PhysX::MeshData^ _meshData;
				
				float* _projectionMatrix;
				
				Object^ _userData;
			
			protected:
				ImplicitScreenMesh( NxImplicitScreenMesh* implicitScreenMesh, StillDesign::PhysX::Fluid^ fluid );
			public:
				~ImplicitScreenMesh();
			protected:
				!ImplicitScreenMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			internal:
				static ImplicitScreenMesh^ FromUnmanagedPointer( NxImplicitScreenMesh* implicitScreenMesh, StillDesign::PhysX::Fluid^ fluid );
				
			public:
				bool GenerateMesh();
				bool GetMesh();
				bool IsMeshGenerationDone();
				
				property StillDesign::PhysX::Fluid^ Fluid
				{
					StillDesign::PhysX::Fluid^ get();
				}
				
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
				property NxImplicitScreenMesh* UnmanagedPointer
				{
					NxImplicitScreenMesh* get();
				}
		};
	};
};