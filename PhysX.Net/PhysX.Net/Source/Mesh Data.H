#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;
UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class MeshData : IDisposable, ICloneable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
				[Flags]
				enum class Type
				{
					Positions = (1 << 0),
					Normals = (1 << 1),
					ParticleIndices = (1 << 2),
					Indices = (1 << 3),
					DirtyFlags = (1 << 4)
				};
			
			private:
				NxMeshData* _meshData;
				
				PhysicsStream^ _positionsStream;
				PhysicsStream^ _normalsStream;
				PhysicsStream^ _parentIndicesStream;
				PhysicsStream^ _indicesStream;
				PhysicsStream^ _dirtyBufferFlagsStream;
				
			public:
				MeshData();
			internal:
				MeshData( NxMeshData* meshData );
				MeshData( NxMeshData meshData );
			public:
				~MeshData();
			protected:
				!MeshData();
			private:
				//void CreateMeshData();
				void CreateMeshData( NxMeshData* meshData );
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			internal:
				static NxMeshData* Clone( NxMeshData meshData );
			
			public:
				virtual Object^ Clone();
				
				/// <summary>Returns true if the current settings are valid</summary>
				bool IsValid();
				/// <summary>(Re)sets the structure to the default</summary>
				void SetToDefault();
				
				generic<typename T> where T : ValueType PhysicsStream^ AllocatePositions( int numberOfPositions );
				PhysicsStream^ AllocatePositions( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateNormals( int numberOfNormals );
				PhysicsStream^ AllocateNormals( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateParentIndices( int numberOfParentIndices );
				PhysicsStream^ AllocateParentIndices( int size, int strideSize );
				generic<typename T> where T : ValueType PhysicsStream^ AllocateIndices( int numberOfIndices );
				PhysicsStream^ AllocateIndices( int size, int strideSize );
				PhysicsStream^ AllocateDirtyBufferFlags( int numberOfDirtyBufferFlags );
				
				static MeshData^ AllocateCommonMeshData( int numberOfPositions, int numberOfTriangles, Type types );
				
				//
				
				/// <summary>Gets or Sets the name</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary>Gets the stream to the vertices</summary>
				property PhysicsStream^ PositionsStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the normals</summary>
				property PhysicsStream^ NormalsStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the parent indices</summary>
				property PhysicsStream^ ParentIndicesStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the indices</summary>
				property PhysicsStream^ IndicesStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the dirty buffer flags</summary>
				property PhysicsStream^ DirtyBufferFlagsStream
				{
					PhysicsStream^ get();
				}
				
				/// <summary>Gets the maximal number of vertices which can be stored in the user vertex buffers</summary>
				property int MaximumVertices
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets the maximal number of indices which can be stored in the user index buffer</summary>
				property int MaximumIndices
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets the maximal number of parent indices which can be stored in the user parent index buffer</summary>
				property int MaximumParentIndices
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets the number of vertices</summary>
				property Nullable<int> NumberOfVertices
				{
					Nullable<int> get();
					void set( Nullable<int> value );
				}
				/// <summary>Gets the number of indices</summary>
				property Nullable<int> NumberOfIndices
				{
					Nullable<int> get();
					void set( Nullable<int> value );
				}
				/// <summary>Gets the the number of parent indices</summary>
				property Nullable<int> NumberOfParentIndices
				{
					Nullable<int> get();
					void set( Nullable<int> value );
				}
				
				/// <summary>Gets the number of bytes between each vertex</summary>
				property int PositionStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each index</summary>
				property int IndexStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each normal</summary>
				property int NormalStrideSize
				{
					int get();
				}
				/// <summary>Gets the number of byte between each parent index</summary>
				property int ParentIndicesStrideSize
				{
					int get();
				}
				
				/// <summary>Gets or Sets the flags</summary>
				property MeshDataFlag Flags
				{
					MeshDataFlag get();
					void set( MeshDataFlag value );
				}
			
			internal:
				property NxMeshData* UnmanagedPointer
				{
					NxMeshData* get();
				}
		};
	};
};