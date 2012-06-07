#pragma once

#include "DeformableEnum.h"

namespace PhysX
{
	ref class Physics;

	/// <summary>
	/// A deformable mesh.
	/// Deformable meshes are suitable for soft body simulation. They come in two flavors: triangle meshes, suitable for simulating a
	/// thin shell (such as a sheet of rubber), and tetrahedron meshes, suitable for simulating a volume (such as a blob of jelly).
	/// </summary>
	public ref class DeformableMesh : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxDeformableMesh* _deformableMesh;
			PhysX::Physics^ _physics;

		internal:
			DeformableMesh(PxDeformableMesh* deformableMesh, PhysX::Physics^ owner);
		public:
			~DeformableMesh();
		protected:
			!DeformableMesh();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Gets the number of deformable instances referencing this deformable mesh.
			/// </summary>
			property int ReferenceCount
			{
				int get();
			}

			/// <summary>
			/// Gets the type of the primitive.
			/// </summary>
			property DeformablePrimitiveType PrimitiveType
			{
				DeformablePrimitiveType get();
			}

			//

		internal:
			property PxDeformableMesh* UnmanagedPointer
			{
				PxDeformableMesh* get();
			}
	};
};