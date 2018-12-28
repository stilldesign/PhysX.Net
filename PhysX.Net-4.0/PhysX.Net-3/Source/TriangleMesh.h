#pragma once

namespace PhysX
{
	ref class Physics;
	ref class Serializable;

	/// <summary>
	/// A triangle mesh, also called a 'polygon soup'.
	/// </summary>
	public ref class TriangleMesh : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxTriangleMesh* _triangleMesh;
			Physics^ _physics;

		public:
			TriangleMesh(PxTriangleMesh* triangleMesh, PhysX::Physics^ physics);
		public:
			~TriangleMesh();
		protected:
			!TriangleMesh();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			//

			/// <summary>
			/// Gets the owner physics object.
			/// </summary>
			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

			/// <summary>
			/// Returns the vertices.
			/// </summary>
			array<Vector3>^ GetVertices();
			/// <summary>
			/// Returns the number of vertices.
			/// </summary>
			property int NumberOfVertices
			{
				int get();
			}

			/// <summary>
			/// Returns the triangle indices.
			/// </summary>
			array<int>^ GetTriangles();
			/// <summary>
			/// Returns the number of triangles.
			/// </summary>
			property int NumberOfTriangles
			{
				int get();
			}
			/// <summary>
			/// Returns whether the triangle indices are 16 or 32bits.
			/// </summary>
			property bool Has16BitTriangleIndices
			{
				bool get();
			}

			/// <summary>
			/// Returns the triangle remapping table.
			/// The triangles are internally sorted according to various criteria. Hence the internal triangle order does not
			/// always match the original (user-defined) order. The remapping table helps finding the old indices knowing the new ones:
			/// 
			/// remapTable[ internalTriangleIndex ] = originalTriangleIndex
			/// </summary>
			array<int>^ GetTriangleRemap();

			/// <summary>
			/// Returns the reference count for shared meshes.
			/// </summary>
			/// <returns>
			/// The current reference count, not used in any shapes if the count is 0.
			/// </returns>
			property int ReferenceCount
			{
				int get();
			}

			/// <summary>
			/// Returns material table index of given triangle. 
			/// This function takes a post cooking triangle index.
			/// </summary>
			/// <param name="triangleIndex">The internal index of desired triangle</param>
			/// <returns>Material table index, or 0xffff if no per-triangle materials are used.</returns>
			short GetTriangleMaterialIndex(int triangleIndex);

		internal:
			property PxTriangleMesh* UnmanagedPointer
			{
				PxTriangleMesh* get();
			}
	};
};