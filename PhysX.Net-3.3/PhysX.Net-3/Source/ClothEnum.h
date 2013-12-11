#pragma once

//#include <PxClothTypes.h> 
//#include <PxClothMeshDesc.h>
//#include <PxClothFabric.h>

namespace PhysX
{
	public enum class ClothFabricPhaseType
	{
		Invalid = PxClothFabricPhaseType::eINVALID,  //!< invalid type 
		Vertical = PxClothFabricPhaseType::eVERTICAL,  //!< resists stretching or compression, usually along the gravity
		Horizontal = PxClothFabricPhaseType::eHORIZONTAL,  //!< resists stretching or compression, perpendicular to the gravity
		Bending = PxClothFabricPhaseType::eBENDING,  //!< resists out-of-plane bending in angle-based formulation
		Shearing = PxClothFabricPhaseType::eSHEARING  //!< resists in-plane shearing along (typically) diagonal edges,
	};

	//public enum class ClothPhaseSolverType
	//{
	//	Invalid = PxClothPhaseSolverConfig::eINVALID, 
	//	Fast = PxClothPhaseSolverConfig::eFAST, 
	//	Stiff = PxClothPhaseSolverConfig::eSTIFF, 
	//	Bending = PxClothPhaseSolverConfig::eBENDING, 
	//	ZeroStreching = PxClothPhaseSolverConfig::eZEROSTRETCH, 
	//	Shearing = PxClothPhaseSolverConfig::eSHEARING
	//};

	public enum class ClothFlag
	{
		SweptContact = PxClothFlag::eSWEPT_CONTACT,
		GPU = PxClothFlag::eGPU
	};
};