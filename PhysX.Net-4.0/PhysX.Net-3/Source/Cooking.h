#pragma once

#include "CookingEnum.h"
#include "CookingParams.h"

namespace PhysX
{
	ref class Foundation;
	ref class TriangleMeshDesc;
	ref class ConvexMeshDesc;
	ref class ClothMeshDesc;
	ref class HeightFieldDesc;

	public ref class Cooking : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxCooking* _cooking;

		internal:
			Cooking(PxCooking* cooking, PhysX::Foundation^ owner);
		public:
			~Cooking();
		protected:
			!Cooking();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			bool CookHeightField(HeightFieldDesc^ desc, System::IO::Stream^ stream);

			/// <summary>
			/// Cooks a triangle mesh. The results are written to the stream.
			/// To create a triangle mesh object it is necessary to first 'cook' the mesh data into a form which allows the
			/// SDK to perform efficient collision detection.
			/// CookTriangleMesh() allows a mesh description to be cooked into a binary stream suitable for loading and
			/// performing collision detection at runtime.
			/// </summary>
			/// <param name="desc">The triangle mesh descriptor to read the mesh from.</param>
			/// <param name="stream">User stream to output the cooked data.</param>
			TriangleMeshCookingResult CookTriangleMesh(TriangleMeshDesc^ desc, System::IO::Stream^ stream);

			/// <summary>
			/// Cooks a convex mesh. The results are written to the stream.
			/// To create a triangle mesh object it is necessary to first 'cook' the mesh data into a form which allows the
			/// SDK to perform efficient collision detection.
			/// CookConvexMesh() allows a mesh description to be cooked into a binary stream suitable for loading and
			/// performing collision detection at runtime.
			/// </summary>
			/// <param name="desc">The convex mesh descriptor to read the mesh from.</param>
			/// <param name="stream">User stream to output the cooked data.</param>
			ConvexMeshCookingResult CookConvexMesh(ConvexMeshDesc^ desc, System::IO::Stream^ stream);

			//

			/// <summary>
			/// Gets or sets options for controlling the operation.
			/// </summary>
			property CookingParams^ Parameters
			{
				CookingParams^ get();
				void set(CookingParams^ value);
			}

			property bool PlatformMismatch
			{
				bool get();
			}

		internal:
			property PxCooking* UnmanagedPointer
			{
				PxCooking* get();
			}
	};
};