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
				
				/// <summary></summary>
				virtual DescriptorValidity^ IsValid() override;
				/// <summary></summary>
				virtual void SetToDefault() override;
				
				/// <summary></summary>
				PhysicsStream^ AllocateMaterialIndices( int size, int strideSize );
				
				/// <summary></summary>
				property PhysicsStream^ MaterialIndicesStream
				{
					PhysicsStream^ get();
				}
				/// <summary></summary>
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