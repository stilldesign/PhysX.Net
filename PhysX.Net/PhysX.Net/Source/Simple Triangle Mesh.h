#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Description.h"

using namespace System;
using namespace System::Collections::Generic;

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class SimpleTriangleMesh abstract : Description, StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			protected:
				NxSimpleTriangleMesh* _triMesh;
				
				PhysicsStream^ _verticesStream;
				PhysicsStream^ _triangleStream;
			
				SimpleTriangleMesh( NxSimpleTriangleMesh* simpleTriangleMesh );
			public:
				~SimpleTriangleMesh();
			protected:
				!SimpleTriangleMesh();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
				/// <summary>Is the Simple Triangle Mesh Valid</summary>
				virtual bool IsValid();
				virtual int CheckValid() override;
				/// <summary>Sets the Simple Triangle Mesh to its Default Values</summary>
				/// <remarks>Does Not Delete Allocated Memory</remarks>
				virtual void SetToDefault();
				
				/// <summary>Allocates memory for vertices</summary>
				/// <param name="numberOfVertices">The number of vertices to allocate</param>
				/// <typeparam name="T">The type of each vertex</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertices( int numberOfVertices );
				/// <summary>Allocates memory for vertices</summary>
				/// <param name="size">The size (in bytes) of the memory to allocate</param>
				/// <param name="strideSize">The size (int bytes) between each vertex</param>
				PhysicsStream^ AllocateVertices( int size, int strideSize );
				/// <summary>Allocates memory for vertices</summary>
				/// <param name="numberOfVertices">The number of triangles to allocate</param>
				/// <typeparam name="T">The type of each index</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateTriangles( int numberOfTriangles );
				/// <summary>Allocates Memory for Triangles</summary>
				/// <param name="size">The Size (in Bytes) of the Memory to Allocate</param>
				/// <param name="strideSize">The Size (int Bytes) Between Each Triangle</param>
				PhysicsStream^ AllocateTriangles( int size, int strideSize );
				
				/// <summary>Gets a Stream to the Vertices</summary>
				property PhysicsStream^ VerticesStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets a Stream to the Triangles</summary>
				property PhysicsStream^ TriangleStream
				{
					PhysicsStream^ get();
				}
				
				/// <summary>Gets the Number of Vertices</summary>
				property int VertexCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets the Number of Triangles</summary>
				property int TriangleCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets the Number of Indices</summary>
				/// <remarks>Index Count is 3 Times the Number of Triangles</remarks>
				property int IndexCount
				{
					int get();
				}
				
				/// <summary>Gets the number of bytes to the between each vertex</summary>
				property int VertexStrideSize
				{
					int get();
				}
				/// <summary>Gets the Number of Bytes to the Next Triangle/3 Indices</summary>
				property int TriangleStrideSize
				{
					int get();
				}
				
				/// <summary>Gets Associated Mesh Flags</summary>
				property MeshFlag Flags
				{
					MeshFlag get();
					void set( MeshFlag value );
				}
			
			internal:
				property NxSimpleTriangleMesh* UnmanagedPointer
				{
					NxSimpleTriangleMesh* get();
				}
		};
	};
};