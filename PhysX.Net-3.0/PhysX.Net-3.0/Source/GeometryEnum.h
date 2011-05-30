#pragma once

#include <PxGeometry.h>
#include <PxTriangleMeshGeometry.h> 

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
		Heightfield = PxGeometryType::eHEIGHTFIELD,
	};

	/// <summary>
	/// Some flags to control the simulated behavior of the mesh geometry.
	/// </summary>
	public enum class MeshGeometryFlag
	{
		/// <summary>
		/// Select between "normal" or "smooth" sphere-mesh/raycastcapsule-mesh contact generation routines.
		/// The 'normal' algorithm assumes that the mesh is composed from flat triangles.
		/// When a ball rolls or a raycast capsule slides along the mesh surface, it will experience small,
		/// sudden changes in velocity as it rolls from one triangle to the next. The smooth algorithm, on
		/// the other hand, assumes that the triangles are just an approximation of a surface that is smooth.
		/// It uses the Gouraud algorithm to smooth the triangles' vertex normals (which in this case are
		/// particularly important). This way the rolling sphere's/capsule's velocity will change smoothly
		/// over time, instead of suddenly. We recommend this algorithm for simulating car wheels on a terrain.
		/// </summary>
		SmoothSphereCollisions = PxMeshGeometryFlag::eSMOOTH_SPHERE_COLLISIONS,
		/// <summary>
		/// The mesh is double-sided. This is currently only used for raycasting.
		/// </summary>
		DoubleSided = PxMeshGeometryFlag::eDOUBLE_SIDED
	};
};