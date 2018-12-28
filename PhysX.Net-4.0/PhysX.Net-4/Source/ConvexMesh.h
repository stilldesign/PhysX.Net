#pragma once

namespace PhysX
{
	ref class Physics;
	ref class ConvexMeshMassInformation;
	ref class HullPolygon;
	ref class Serializable;

	/// <summary>
	/// A convex mesh.
	/// </summary>
	public ref class ConvexMesh : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxConvexMesh* _convexMesh;
			Physics^ _physics;

		internal:
			ConvexMesh(PxConvexMesh* convexMesh, PhysX::Physics^ physics);
		public:
			~ConvexMesh();
		protected:
			!ConvexMesh();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Returns the index buffer.
			/// </summary>
			array<Byte>^ GetIndexBuffer();

			/// <summary>
			/// Returns the mass properties of the mesh.
			/// </summary>
			ConvexMeshMassInformation^ GetMassInformation();

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
			/// Returns the polygon data.
			/// </summary>
			HullPolygon^ GetPolygonData(int index);
			/// <summary>
			/// Returns the number of polygons.
			/// </summary>
			property int NumberOfPolygons
			{
				int get();
			}

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

		internal:
			property PxConvexMesh* UnmanagedPointer
			{
				PxConvexMesh* get();
			}
	};
};