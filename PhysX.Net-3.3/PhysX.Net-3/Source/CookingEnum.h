#pragma once

//#include <PxCooking.h>
//#include <PxConvexMeshDesc.h> 

 namespace PhysX
 {
	public enum class Platform
	{
		PC = PxPlatform::ePC,
		Xenon = PxPlatform::eXENON,
		PlayStation3 = PxPlatform::ePLAYSTATION3,
		ARM = PxPlatform::eARM,
		WiiU = PxPlatform::eWIIU
	};

	public enum class ConvexFlag
	{
		/// <summary>
		/// Used to flip the normals if the winding order is reversed.
		/// The Nx libraries assume that the face normal of a triangle with vertices [a,b,c] can be computed as: edge1 = b-a edge2 = c-a face_normal = edge1 x edge2.
		/// Note: this is the same as counterclockwise winding in a right handed graphics coordinate system.
		/// If this does not match the winding order for your triangles, raise the below flag.
		/// </summary>
		FlipNormals = PxConvexFlag::eFLIPNORMALS,

		/// <summary>
		/// Denotes the use of 16-bit vertex indices in PxConvexMeshDesc::triangles. (otherwise, 32-bit indices are assumed).
		/// </summary>
		Indices16Bit = PxConvexFlag::e16_BIT_INDICES,

		/// <summary>
		/// Automatically recomputes the hull from the vertices. If this flag is not set, you must provide the entire geometry manually.
		/// </summary>
		ComputeConvex = PxConvexFlag::eCOMPUTE_CONVEX,

		/// <summary>
		/// Inflates the convex object according to skin width.
		/// Note: This flag is only used in combination with ComputeConvex.
		/// </summary>
		InflateConvex = PxConvexFlag::eINFLATE_CONVEX
	};
 };