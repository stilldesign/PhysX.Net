#pragma once

#include "Enums.h"
#include "IDisposable.h"
#include "Description.h"

class NxSoftBodyMeshDesc;

namespace StillDesign
{
	namespace PhysX
	{
		ref class PhysicsStream;
		
		public ref class SoftBodyMeshDescription : Description, StillDesign::PhysX::IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
			
			private:
				NxSoftBodyMeshDesc* _desc;
				
				PhysicsStream^ _verticesStream;
				PhysicsStream^ _tetrahedraStream;
				PhysicsStream^ _vertexMassesStream;
				PhysicsStream^ _vertexFlagsStream;
			
			public:
				SoftBodyMeshDescription();
			internal:
				SoftBodyMeshDescription( NxSoftBodyMeshDesc* desc );
			public:
				~SoftBodyMeshDescription();
			protected:
				!SoftBodyMeshDescription();
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
				/// <summary>Sets the description to default</summary>
				void SetToDefault();
				/// <summary>Returns 0 if the current settings are valid.</summary>
				virtual int CheckValid() override;
				/// <summary>Is the description valid</summary>
				bool IsValid();
				
				/// <summary>Allocates memory for the vertices</summary>
				/// <param name="numberOfVertices">The number of vertices to allocate</param>
				/// <typeparam name="T">The type of each vertex</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertices( int numberOfVertices );
				/// <summary>Allocates memory for the vertices</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each vertex</param>
				PhysicsStream^ AllocateVertices( int size, int strideSize );
				/// <summary>Allocates memory for the tetrahedra</summary>
				/// <param name="numberOfTetrahedra">The number of tetrahedra to allocate</param>
				/// <typeparam name="T">The type of each tetrahedra point. Note. <typeparamref name="T"/> is for each point</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateTetrahedra( int numberOfTetrahedra );
				/// <summary>Allocates memory for the tetrahedra</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each tetrahedra</param>
				PhysicsStream^ AllocateTetrahedra( int size, int strideSize );
				/// <summary>Allocates memory for the vertex masses</summary>
				/// <param name="numberOfVertices">The number of vertex masses to allocate</param>
				/// <typeparam name="T">The type of each vertex mass</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertexMasses( int numberOfVertices );
				/// <summary>Allocates memory for the vertex masses</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each vertex mass</param>
				PhysicsStream^ AllocateVertexMasses( int size, int strideSize );
				/// <summary>Allocates memory for the vertex flags</summary>
				/// <param name="numberOfVertices">The number of vertex flags to allocate</param>
				/// <typeparam name="T">The type of each vertex flag</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertexFlags( int numberOfVertices );
				/// <summary>Allocates memory for the vertex flags</summary>
				/// <param name="size">The number of bytes to allocate</param>
				/// <param name="strideSize">The number of bytes between each vertex flag</param>
				PhysicsStream^ AllocateVertexFlags( int size, int strideSize );
				
				/// <summary>Gets or Sets the number of vertices</summary>
				property int VertexCount
				{
					int get();
					void set( int value );
				}
				/// <summary>Gets or Sets the number of tetrahedra</summary>
				property int TetrahedraCount
				{
					int get();
					void set( int value );
				}
				
				/// <summary>Gets the number of bytes between each vertex</summary>
				property int VertexStrideBytes
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each tetrahedra</summary>
				property int TetrahedraStrideBytes
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each vertex mass</summary>
				property int VertexMassStrideBytes
				{
					int get();
				}
				/// <summary>Gets the number of bytes between each vertex flag</summary>
				property int VertexFlagStrideBytes
				{
					int get();
				}
				
				/// <summary>Gets or Sets the flags</summary>
				property SoftBodyMeshFlag Flags
				{
					SoftBodyMeshFlag get();
					void set( SoftBodyMeshFlag value );
				}
				
				/// <summary>Gets the stream to the vertices</summary>
				property PhysicsStream^ VertexStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the tetrahedra</summary>
				property PhysicsStream^ TetrahedraStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the vertex masses</summary>
				property PhysicsStream^ VertexMassesStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Gets the stream to the vertex flags</summary>
				property PhysicsStream^ VertexFlagsStream
				{
					PhysicsStream^ get();
				}
			
			internal:
				property NxSoftBodyMeshDesc* UnmanagedPointer
				{
					NxSoftBodyMeshDesc* get();
				}
		};
	};
};