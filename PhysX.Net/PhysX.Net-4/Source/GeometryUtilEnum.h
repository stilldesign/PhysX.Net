#pragma once


namespace PhysX
{
	[Flags]
	public enum class MeshFlag
	{
		/// <summary>
		/// Specifies if the SDK should flip normals.
		/// The Nx libraries assume that the face normal of a triangle with vertices [a,b,c] can be
		/// computed as: edge1 = b-a edge2 = c-a face_normal = edge1 x edge2.
		/// Note: This is the same as a counterclockwise winding in a right handed coordinate system or alternatively
		/// a clockwise winding order in a left handed coordinate system.
		/// If this does not match the winding order for your triangles, raise the below flag.
		/// </summary>
		FlipNormals = PxMeshFlag::eFLIPNORMALS,
		Indices16Bit = PxMeshFlag::e16_BIT_INDICES
	};
};