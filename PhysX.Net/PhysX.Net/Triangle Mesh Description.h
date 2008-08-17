#pragma once

#include "Enums.h"
#include "Simple Triangle Mesh.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		public ref class TriangleMeshDescription : SimpleTriangleMesh
		{
			private:
				PhysicsStream^ _materialIndicesStream;
			
			internal:
				TriangleMeshDescription( NxTriangleMeshDesc* triangleMeshDesc );
			public:
				TriangleMeshDescription();
				
				generic<typename T, typename V>
				where T : ValueType
				where V : ValueType
				static TriangleMeshDescription^ Create( array<T>^ triangleIndices, array<V>^ vertices );
				
				/// <summary>Returns true if the descriptor is valid</summary>
				virtual DescriptorValidity^ IsValid() override;
				/// <summary>Sets the structure to the default</summary>
				virtual void SetToDefault() override;
				
				/// <summary>Allocates memory for material indices</summary>
				/// <typeparam name="T">The type of each material index</typeparam>
				generic<class T> where T : ValueType
				PhysicsStream^ AllocateMaterialIndices( int numberOfMaterialIndices );
				/// <summary>Allocates memory for material indices</summary>
				/// <param name="size">The amount (in bytes) of memory to allocate</param>
				/// <param name="strideSize">The amount (in bytes) between each material index</param>
				PhysicsStream^ AllocateMaterialIndices( int size, int strideSize );
				
				/// <summary>Gets the stream to the material indices</summary>
				property PhysicsStream^ MaterialIndicesStream
				{
					PhysicsStream^ get();
				}
				/// <summary>Tolerance for the convex edge detector</summary>
				property Axis HeightFieldVerticalAxis
				{
					Axis get();
					void set( Axis value );
				}
				/// <summary></summary>
				property float HeightFieldVerticalExtent
				{
					float get();
					void set( float value );
				}
				/// <summary></summary>
				property float ConvexEdgeThreshold
				{
					float get();
					void set( float value );
				}
			
			internal:
				property NxTriangleMeshDesc* UnmanagedPointer
				{
					NxTriangleMeshDesc* get() new;
				}
		};
	};
};