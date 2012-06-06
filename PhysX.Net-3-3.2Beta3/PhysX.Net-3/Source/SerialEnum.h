#pragma once

namespace PhysX
{
	public enum class SerialOrder
	{
		Convex = PxSerialOrder::eCONVEX,
		TriangleMesh = PxSerialOrder::eTRIMESH,
		Heightfield = PxSerialOrder::eHEIGHTFIELD,
		DefMesh = PxSerialOrder::eDEFMESH,
		ClothMesh = PxSerialOrder::eCLOTHMESH,
		Material = PxSerialOrder::eMATERIAL,
		Shape = PxSerialOrder::eSHAPE,
		Static = PxSerialOrder::eSTATIC,
		Dynamic = PxSerialOrder::eDYNAMIC,
		Default = PxSerialOrder::eDEFAULT,
		Articulation = PxSerialOrder::eARTICULATION,
		Joint = PxSerialOrder::eJOINT,
		Constraint = PxSerialOrder::eCONSTRAINT,
		Aggregate = PxSerialOrder::eAGGREGATE
	};
};