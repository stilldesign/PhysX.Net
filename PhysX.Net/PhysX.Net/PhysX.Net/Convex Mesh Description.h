#pragma once

#include "Enums.h"
#include "IDisposable.h"

using namespace System;

UsingFrameworkNamespace
UsingGraphicsNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class ConvexMesh;
		ref class Scene;
		ref class PhysicsStream;
		
		public ref class ConvexMeshDescription : IDisposable
		{
			public:
				virtual event EventHandler^ onDisposing;
				virtual event EventHandler^ onDisposed;
			
			private:
				NxConvexMeshDesc* _desc;
				
				PhysicsStream^ _pointsStream;
				PhysicsStream^ _trianglesStream;
				
			public:
				ConvexMeshDescription();
			internal:
				ConvexMeshDescription( NxConvexMeshDesc* convexMeshDescription );
			public:
				~ConvexMeshDescription();
			protected:
				!ConvexMeshDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
			
			public:
				/// <summary>Is the convex mesh description valid</summary>
				bool IsValid();
				/// <summary>Sets the description to default</summary>
				void SetToDefault();
				
				/// <summary>Allocates memory for the points</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each point</summary>
				PhysicsStream^ AllocatePoints( int size, int strideSize );
				/// <summary>Allocates memory for the points</summary>
				/// <param name="numberOfPoints">Number of points to allocate</param>
				/// <typeparam name="T">The type of each point</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocatePoints( int numberOfPoints );
				
				/// <summary>Allocates memory for the triangles</summary>
				/// <param name="size">The nmber of bytes to allocate</summary>
				/// <param name="strideSize">The number of bytes betweeb each triangle</param>
				PhysicsStream^ AllocateTriangles( int size, int strideSize );
				/// <summary>Allocates memory for the triangles</summary>
				/// <param name="numberOfTriangles">Number of triangles to allocate</param>
				/// <typeparam name="T">The type of each index</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateTriangles( int numberOfTriangles );
				
				/// <summary></summary>
				property int PointCount
				{
					int get();
					void set( int value );
				}
				/// <summary></summary>
				property int TriangleCount
				{
					int get();
					void set( int value );
				}
				/// <summary></summary>
				property int PointStrideSize
				{
					int get();
				}
				/// <summary></summary>
				property int TriangleStrideSize
				{
					int get();
				}
				
				/// <summary></summary>
				property PhysicsStream^ PointsStream
				{
					PhysicsStream^ get();
				}
				/// <summary></summary>
				property PhysicsStream^ TriangleStream
				{
					PhysicsStream^ get();
				}
				
				/// <summary></summary>
				property ConvexFlag Flags
				{
					ConvexFlag get();
					void set( ConvexFlag value );
				}
				
			internal:
				property NxConvexMeshDesc* UnmanagedPointer
				{
					NxConvexMeshDesc* get();
				}
		};
	};
};