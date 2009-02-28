#pragma once

#include "Simple Triangle Mesh.h"

using namespace System;
UsingFrameworkNamespace

class NxClothMeshDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ClothMeshDescription : SimpleTriangleMesh
		{
			private:
				String^ _name;
				
				PhysicsStream^ _vertexMasses;
				PhysicsStream^ _vertexFlags;
				
			public:
				ClothMeshDescription();
			internal:
				ClothMeshDescription( NxClothMeshDesc* clothMeshDescription );
			public:
				~ClothMeshDescription();
			protected:
				!ClothMeshDescription();
				
			public:	
				/// <summary>Resets the structure to the default</summary>
				virtual void SetToDefault() override;
				/// <summary>Returns true if the current settings are valid</summary>
				virtual bool IsValid() override;
				
				/// <summary>Allocates memory for the vertex masses</summary>
				/// <param name="numberOfVertices">Number of vertices to allocate</param>
				/// <typeparam name="T">The type of each vertex mass</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertexMasses( int numberOfVertices );
				/// <summary>Allocates memory for the mass of each vertex to be stored</summary>
				/// <param name="size">The amount of memory in bytes to allocate</param>
				/// <param name="strideSize">The number of bytes that separate each vertex mass</param>
				PhysicsStream^ AllocateVertexMasses( int size, int strideSize );
				/// <summary>Allocates memory for the vertex flags</summary>
				/// <param name="numberOfVertices">Number of vertices to allocate</param>
				/// <typeparam name="T">The type of each vertex flag</typeparam>
				generic<typename T> where T : ValueType PhysicsStream^ AllocateVertexFlags( int numberOfVertices );
				/// <summary>Allocates memory for a flag of each vertex to be stored</summary>
				/// <param name="size">The amount of memory in bytes to allocate</param>
				/// <param name="strideSize">The number of bytes that separate each vertex flag</param>
				PhysicsStream^ AllocateVertexFlags( int size, int strideSize );
				
				/// <summary>Gets or Sets the Name of the Cloth Mesh Description</summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				property PhysicsStream^ VertexMassesStream
				{
					PhysicsStream^ get();
				}
				property PhysicsStream^ VertexFlagsStream
				{
					PhysicsStream^ get();
				}
				
				/// <summary>Gets or Sets welding value for close vertices</summary>
				property float WeldingDistance
				{
					float get();
					void set( float value );
				}
				
			internal:
				property NxClothMeshDesc* UnmanagedPointer
				{
					NxClothMeshDesc* get() new;
				}
		};
	};
};