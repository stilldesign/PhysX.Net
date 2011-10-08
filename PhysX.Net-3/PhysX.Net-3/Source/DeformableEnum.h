#pragma once

#include <PxDeformableReadData.h> 
#include <PxDeformableMeshDesc.h> 
#include <PxDeformableDesc.h>

namespace PhysX
{
	/// <summary>
	/// Collection of flags describing the behavior of a deformable.
	/// </summary>
	public enum class DeformableFlag
	{
		/// <summary>
		/// Enable/disable pressure simulation. Ineffective for soft bodies.
		/// Note: For triangle meshes, pressure only produces meaningful results if the mesh is closed.
		/// </summary>
		Pressure = PxDeformableFlag::ePRESSURE,

		/// <summary>
		/// Makes the deformable static.
		/// </summary>
		Static = PxDeformableFlag::eSTATIC,

		/// <summary>
		/// Enable/disable self-collision handling within a single piece of deformable.
		/// Note: self-collisions are only handled inbetween the deformable's vertices, i.e., vertices do not
		/// collide against the triangles/tetrahedra of the deformable. The user should therefore specify a large enough
		/// selfCollisionOffset to avoid most interpenetrations.
		/// </summary>
		SelfCollision = PxDeformableFlag::eSELFCOLLISION,

		/// <summary>
		/// Enable/disable bending resistance. Ineffective for soft bodies.
		/// Select the bending resistance through DeformableDesc.BendingStiffness.
		/// </summary>
		Bending = PxDeformableFlag::eBENDING,

		/// <summary>
		/// Enable/disable volume conservation. Ineffective for cloth.
		/// Select volume conservation through DeformableDesc.VolumeStiffness.
		/// </summary>
		VolumeConservation = PxDeformableFlag::eVOLUME_CONSERVATION,

		/// <summary>
		/// Enable/disable damping of internal velocities.
		/// Use DeformableDesc.DampingCoefficient to control damping.
		/// </summary>
		Damping = PxDeformableFlag::eDAMPING,

		/// <summary>
		/// Enable/disable deformable surface collision detection.
		/// If SurfaceCollision is not set, only collisions of deformable vertices are detected.
		/// If SurfaceCollision is set, the surface triangles of the deformable are used for collision detection.
		/// For deformables with tetrahedral meshes, the interior tetrahedron faces are not considered.
		/// The flag does not have an impact on self collision behavior.
		/// </summary>
		SurfaceCollision = PxDeformableFlag::eSURFACE_COLLISION,

		/// <summary>
		/// Defines whether the deformable is tearable.
		/// Note: Make sure MeshData.MaximumVertices and the corresponding buffers in MeshData are substantially
		/// larger (e.g. 2x) than the number of original vertices since tearing will generate new vertices.
		/// When the buffer cannot hold the new vertices anymore, tearing stops.
		/// Note: For tearing, make sure you cook the mesh with the flag DeformableMeshFlag.Tearable set in the DeformableMeshDesc.Flags.
		/// </summary>
		Tearable = PxDeformableFlag::eTEARABLE,

		/// <summary>
		/// Enable/disable center of mass damping of internal velocities.
		/// This flag only has an effect if the flag Damping is set.
		/// If set, the global rigid body modes (translation and rotation) are extracted from damping.
		/// This way, the deformable can freely move and rotate even under high damping.
		/// Use PxDeformableDesc.DampingCoefficient to control damping.
		/// </summary>
		CenterOfMassDaming = PxDeformableFlag::eCOMDAMPING,

		/// <summary>
		/// If the flag ValidBounds is set, deformable vertices outside the volume defined by DeformableDesc.ValidBounds
		/// are automatically removed from the simulation. 
		/// </summary>
		ValidBounds = PxDeformableFlag::eVALIDBOUNDS,

		/// <summary>
		/// Enable/disable bulk data double buffering.
		/// Raising this flag will enable reading and writing vertex data while the simulation is running.
		/// Note: This comes along with a considerable memory cost.
		/// All requested vertex read data buffers need to be duplicated.
		/// This flag can only be set in the particle system descriptor at creation time.
		/// Changing the flag later on is not supported. 
		/// </summary>
		BulkDataDoubleBuffering = PxDeformableFlag::eBULK_DATA_DOUBLE_BUFFERING,

		/// <summary>
		/// Enable/disable two way interaction between deformables and rigid bodies.
		/// Raising this flag might have severe implications on performance.
		/// Note: Raising this flag might have severe implications on performance.
		/// DeformableVertexAttachmentFlag.Twoway will have no effect if not set.
		/// DominanceGroup ActorDesc.DominanceGroup and Actor.SetDominanceGroup() will have no effect if not set.
		/// </summary>
		Twoway = PxDeformableFlag::eTWOWAY
	};

	public enum class DeformableReadDataFlag
	{
		PositionBuffer = PxDeformableReadDataFlag::ePOSITION_BUFFER,
		VelocityBuffer = PxDeformableReadDataFlag::eVELOCITY_BUFFER,
		InverseMassBuffer = PxDeformableReadDataFlag::eINVERSE_MASS_BUFFER,
		NormalBuffer = PxDeformableReadDataFlag::eNORMAL_BUFFER,
		ParentIndexBuffer = PxDeformableReadDataFlag::ePARENT_INDEX_BUFFER,
		IndexBuffer = PxDeformableReadDataFlag::eINDEX_BUFFER,
		PrimitiveSplitPairBuffer = PxDeformableReadDataFlag::ePRIMITIVE_SPLIT_PAIR_BUFFER
	};

	public enum class DeformablePrimitiveType
	{
		None = PxDeformablePrimitiveType::eNONE,
		Triangle = PxDeformablePrimitiveType::eTRIANGLE,
		Tetrahedron = PxDeformablePrimitiveType::eTETRAHEDRON
	};

	/// <summary>
	/// Deformable vertex flags.
	/// </summary>
	public enum class DeformableVertexFlag
	{
		/// <summary>
		/// Specifies whether a deformable vertex can be torn.
		/// </summary>
		Tearable = PxDeformableVertexFlag::eTEARABLE,

		/// <summary>
		/// A secondary deformable vertex does not influence regular vertices. Ineffective for cloth.
		/// Interactions between vertices of the same type are treated normally.
		/// In an interaction between vertices of different types, the regular vertex temporarily gets infinite mass (does not move) 
		/// </summary>
		Secondary = PxDeformableVertexFlag::eSECONDARY
	};
};