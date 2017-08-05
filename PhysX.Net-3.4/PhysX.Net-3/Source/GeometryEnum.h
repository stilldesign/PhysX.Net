#pragma once


namespace PhysX
{
	/// <summary>
	/// A geometry type.
	/// Used to distinguish the type of a PxGeometry object.
	/// </summary>
	public enum class GeometryType
	{
		Sphere = PxGeometryType::eSPHERE, 
		Plane = PxGeometryType::ePLANE, 
		Capsule = PxGeometryType::eCAPSULE, 
		Box = PxGeometryType::eBOX, 
		ConvexMesh = PxGeometryType::eCONVEXMESH, 
		TriangleMesh = PxGeometryType::eTRIANGLEMESH, 
		Heightfield = PxGeometryType::eHEIGHTFIELD
	};

	/// <summary>
	/// Some flags to control the simulated behavior of the mesh geometry.
	/// </summary>
	[Flags]
	public enum class MeshGeometryFlag
	{
		/// <summary>
		/// The mesh is double-sided. This is currently only used for raycasting.
		/// </summary>
		DoubleSided = PxMeshGeometryFlag::eDOUBLE_SIDED
	};
};