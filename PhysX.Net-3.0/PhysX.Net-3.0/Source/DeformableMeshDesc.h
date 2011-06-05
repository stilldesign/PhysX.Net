#pragma once

#include "DeformableEnum.h"

namespace PhysX
{
	/// <summary>
	/// Descriptor class for deformable mesh.
	/// </summary>
	public ref class DeformableMeshDesc
	{
		private:
			Array^ _primitives;
			bool _is16BitPrimitives;

		public:
			DeformableMeshDesc();

		internal:
			static PxDeformableMeshDesc ToUnmanaged(DeformableMeshDesc^ desc);
			static DeformableMeshDesc^ ToManaged(PxDeformableMeshDesc desc);

		public:
			void SetToDefault();
			bool IsValid();

			/// <summary>
			/// Pointer to the first primitive vertex index tuple.
			/// </summary>
			generic<typename T> where T : value class
			array<T>^ GetPrimitives();
			/// <summary>
			/// 
			/// </summary>
			generic<typename T> where T : value class
			void SetPrimitives(array<T>^ primitives);
		
			property bool Is16BitPrimitives
			{
				bool get();
			}

			/// <summary>
			/// The type of primitives the mesh is composed of.
			/// </summary>
			property DeformablePrimitiveType PrimitiveType;

			/// <summary>
			/// Number of vertices.
			/// </summary>
			property int NumberOfVertices;
			
			/// <summary>
			/// Number of primitives.
			/// </summary>
			property int NumberOfPrimitives;
			
			/// <summary>
			/// Pointer to first vertex point.
			/// </summary>
			property array<Vector3>^ Vertices;
			
			/// <summary>
			/// Pointer to first vertex mass.
			/// </summary>
			property array<float>^ VertexMasses;
			
			/// <summary>
			/// Pointer to first vertex flag. Flags are of type DeformableVertexFlag.
			/// </summary>
			property array<DeformableVertexFlag>^ VertexFlags;
			
			/// <summary>
			/// For welding close vertices.
			/// </summary>
			property float WeldingDistance;
			
			/// <summary>
			/// Specifies the number of additional mesh levels to be employed by the hierarchical solver.
			/// </summary>
			property int MaximumHierarchyLevels;

			/// <summary>
			/// Flag bits, combined from values of the enum DeformableVertexFlag
			/// </summary>
			property DeformableVertexFlag Flags;
	};
};