#pragma once


namespace PhysX
{
	/// <summary>
	/// A class expressing a nonuniform scaling transformation.
	/// The scaling is along arbitrary axes that are specified by MeshScale.Rotation.
	/// 
	/// Note:
	/// Currently only positive scale values are supported.
	/// </summary>
	public value class MeshScale
	{
		public:
			/// <summary>
			/// Constructor to initialize to arbitrary scaling.
			/// </summary>
			MeshScale(Vector3 scale, Quaternion rotation);

		internal:
			static PxMeshScale ToUnmanaged(MeshScale meshScale);
			static MeshScale ToManaged(PxMeshScale meshScale);

		public:
			/// <summary>
			/// Returns the inverse of this scaling transformation.
			/// </summary>
			MeshScale GetInverse();

			/// <summary>
			/// Converts this transformation to a 3x3 matrix representation.
			/// </summary>
			Matrix ToMatrix();

			/// <summary>
			/// Returns the identity scaling transformation.
			/// </summary>
			property MeshScale Identity
			{
				static MeshScale get();
			}

			/// <summary>
			/// Returns true if the scaling is an identity transformation.
			/// </summary>
			property bool IsIdentity
			{
				bool get();
			}

			/// <summary>
			/// A nonuniform scaling.
			/// </summary>
			property Vector3 Scale;
			/// <summary>
			/// The orientation of the scaling axes.
			/// </summary>
			property Quaternion Rotation;
	};
};