#pragma once


namespace PhysX
{
	/// <summary>
	/// Describes the format of height field samples.
	/// </summary>
	public enum class HeightFieldFormat
	{
		/// <summary>
		/// Height field height data is 16 bit signed integers, followed by triangle materials.
		/// </summary>
		Signed16BitIntegersWithTriangleMaterials = PxHeightFieldFormat::eS16_TM
	};

	/// <summary>
	/// Enum with flag values to be used in PxHeightFieldDesc.flags.
	/// </summary>
	public enum class HeightFieldFlag
	{
		/// <summary>
		/// Disable collisions with height field with boundary edges.
		/// Raise this flag if several terrain patches are going to be placed adjacent
		/// to each other, to avoid a bump when sliding across.
		/// This flag is ignored in contact generation with sphere and capsule shapes.
		/// </summary>
		NoBoundaryEdges = PxHeightFieldFlag::eNO_BOUNDARY_EDGES
	};

	/// <summary>
	/// Special material index values for height field samples.
	/// </summary>
	public enum class HeightFieldMaterial
	{
		/// <summary>
		/// A material indicating that the triangle should be treated as a hole in the mesh.
		/// </summary>
		Hole = PxHeightFieldMaterial::eHOLE
	};

	/// <summary>
	/// Determines the tessellation of height field cells.
	/// </summary>
	public enum class HeightFieldTessFlag
	{
		/// <summary>
		/// This flag determines which way each quad cell is subdivided.
		/// </summary>
		ZeroVertexShared = PxHeightFieldTessFlag::e0TH_VERTEX_SHARED
	};
};