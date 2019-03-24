#pragma once

#include "HeightFieldEnum.h"

namespace PhysX
{
	ref class Physics;
	ref class Serializable;
	ref class HeightFieldSample;

	/// <summary>
	/// A height field class.
	/// </summary>
	public ref class HeightField : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxHeightField* _heightField;
			PhysX::Physics^ _physics;

		internal:
			HeightField(PxHeightField* heightField, PhysX::Physics^ owner);
		public:
			~HeightField();
		protected:
			!HeightField();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Retrieves the height at the given coordinates in grid space.
			/// </summary>
			float GetHeight(float x, float z);

			/// <summary>
			/// Retrieves the material table index of given triangle. 
			/// </summary>
			short GetTriangleMaterialIndex(int triangleIndex);

			/// <summary>
			/// Returns heightfield sample of given row and column.
			/// </summary>
			/// <param name="row">Given heightfield row.</param>
			/// <param name="column">Given heightfield column.</param>
			/// <returns>Heightfield sample.</returns>
			HeightFieldSample^ GetSample(int row, int column);

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			//

			/// <summary>
			/// Gets the physics.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

			/// <summary>
			/// Gets the number of sample rows in the samples array.
			/// </summary>
			property int NumberOfRows
			{
				int get();
			}

			/// <summary>
			/// Gets the number of sample columns in the samples array.
			/// </summary>
			property int NumberOfColumns
			{
				int get();
			}

			/// <summary>
			/// Gets the format of the sample data.
			/// </summary>
			property HeightFieldFormat Format
			{
				HeightFieldFormat get();
			}

			/// <summary>
			/// Gets the offset in bytes between consecutive samples in the array.
			/// </summary>
			property int SampleStride
			{
				int get();
			}

			/// <summary>
			/// Gets the convex edge threshold.
			/// </summary>
			property float ConvexEdgeThreshold
			{
				float get();
			}

			/// <summary>
			/// Gets the flags bits, combined from values of the enum HeightFieldFlag.
			/// </summary>
			property HeightFieldFlag Flags
			{
				HeightFieldFlag get();
			}

			/// <summary>
			/// Gets number of shapes referencing the mesh.
			/// </summary>
			property int ReferenceCount
			{
				int get();
			}

			/// <summary>
			/// Returns the number of times the heightfield data has been modified.
			/// This method returns the number of times modifySamples has been called on this heightfield, so that code that has retained state that depends on the heightfield can efficiently determine whether it has been modified.
			/// </summary>
			property int Timestamp
			{
				int get();
			}

		internal:
			property PxHeightField* UnmanagedPointer
			{
				PxHeightField* get();
			}
	};
};