#pragma once

#include "LockedData.h"
#include "DeformablePrimitiveSplitPair.h"

namespace PhysX
{
	public ref class DeformableReadData : LockedData
	{
		protected:
			DeformableReadData(PxDeformableReadData* deformableReadData);

		public:
			/// <summary>
			/// Number of vertices.
			/// </summary>
			property int NumberOfVertices
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Dirty buffer flags.
			/// </summary>
			property int DirtyBufferFlags
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Number of primitive split pairs.
			/// </summary>
			property int NumberOfPrimitiveSplitPairs
			{
				int get();
				void set(int value);
			}

			/// <summary>
			/// Vertex position data.
			/// </summary>
			property array<Vector3>^ PositionBuffer
			{
				array<Vector3>^ get();
				void set(array<Vector3>^ value);
			}

			/// <summary>
			/// Vertex velocity data.
			/// </summary>
			property array<Vector3>^ VelocityBuffer
			{
				array<Vector3>^ get();
				void set(array<Vector3>^ value);
			}

			/// <summary>
			/// Vertex inverse mass data.
			/// </summary>
			property array<float>^ InverseMassBuffer
			{
				array<float>^ get();
				void set(array<float>^ value);
			}

			/// <summary>
			/// Vertex normal data.
			/// </summary>
			property array<Vector3>^ NormalBuffer
			{
				array<Vector3>^ get();
				void set(array<Vector3>^ value);
			}

			/// <summary>
			/// Parent index data.
			/// </summary>
			property array<int>^ ParentIndexBuffer
			{
				array<int>^ get();
				void set(array<int>^ value);
			}

			/// <summary>
			/// Index data. Not strided.
			/// </summary>
			property array<int>^ IndexBuffer
			{
				array<int>^ get();
				void set(array<int>^ value);
			}

			/// <summary>
			/// Split pair data.
			/// </summary>
			property array<DeformablePrimitiveSplitPair>^ PrimitiveSplitPairBuffer
			{
				array<DeformablePrimitiveSplitPair>^ get();
				void set(array<DeformablePrimitiveSplitPair>^ value);
			}

		internal:
			property PxDeformableReadData* UnmanagedPointer
			{
				PxDeformableReadData* get() new;
			}
	};
};