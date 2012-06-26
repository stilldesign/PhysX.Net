#pragma once

#include <PxClothFabricTypes.h>
#include <PxClothTypes.h> 
#include <PxClothMeshDesc.h>

namespace PhysX
{
	public enum class ClothFabricPhaseType
	{
		Invalid = PxClothFabricPhaseType::eINVALID,  //!< invalid type 
		Stretching = PxClothFabricPhaseType::eSTRETCHING,  //!< resists stretching or compression, usually along the gravity
		StretchingHorizontal = PxClothFabricPhaseType::eSTRETCHING_HORIZONTAL,  //!< resists stretching or compression, perpendicular to the gravity
		Bending = PxClothFabricPhaseType::eBENDING,  //!< resists out-of-plane bending 
		Shearing = PxClothFabricPhaseType::eSHEARING,  //!< resists in-plane shearing along (typically) diagonal edges,
		ZeroStretch = PxClothFabricPhaseType::eZEROSTRETCH, //!< avoid stretch (exactly) from a set of constrained positions
		BendingAngle = PxClothFabricPhaseType::eBENDING_ANGLE  //!< resists out-of-plane bending in angle-based formulation
	};

	public enum class ClothPhaseSolverType
	{
		Invalid = PxClothPhaseSolverConfig::eINVALID, 
		Fast = PxClothPhaseSolverConfig::eFAST, 
		Stiff = PxClothPhaseSolverConfig::eSTIFF, 
		Bending = PxClothPhaseSolverConfig::eBENDING, 
		ZeroStreching = PxClothPhaseSolverConfig::eZEROSTRETCH, 
		Shearing = PxClothPhaseSolverConfig::eSHEARING
	};

	public enum class ClothFlag
	{
		SweptContact = PxClothFlag::eSWEPT_CONTACT,
		GPU = PxClothFlag::eGPU
	};

	public enum class ClothMeshEdgeFlag
	{
		/// <summary>
		/// The edge was only added to convert a quad into triangles (marking these edges allows to reconstruct quads).
		/// </summary>
		QuadDiagonal = PxClothMeshEdgeFlag::eQUAD_DIAGONAL
	};

	public enum class ClothMeshVertexFlag
	{
		/// <summary>
		/// The vertex is attached, so the cooker should take the constraint into account.
		/// </summary>
		Attached = PxClothMeshVertFlag::eVF_ATTACHED
	};
};