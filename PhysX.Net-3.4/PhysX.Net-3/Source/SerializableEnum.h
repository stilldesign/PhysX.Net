#pragma once


namespace PhysX
{
	public enum class ConcreteType
	{
		Undefined = PxConcreteType::eUNDEFINED, 
		Heightfield = PxConcreteType::eHEIGHTFIELD, 
		ConvexMesh = PxConcreteType::eCONVEX_MESH, 
		TriangleMeshBVH33 = PxConcreteType::eTRIANGLE_MESH_BVH33,
		TriangleMeshBVH34 = PxConcreteType::eTRIANGLE_MESH_BVH34,
		ClothFabric = PxConcreteType::eCLOTH_FABRIC, 
		RigidDynamic = PxConcreteType::eRIGID_DYNAMIC, 
		RigidStatic = PxConcreteType::eRIGID_STATIC, 
		Shape = PxConcreteType::eSHAPE, 
		Material = PxConcreteType::eMATERIAL, 
		Constraint = PxConcreteType::eCONSTRAINT, 
		Cloth = PxConcreteType::eCLOTH, 
		ParticleSystem = PxConcreteType::ePARTICLE_SYSTEM, 
		ParticleFluid = PxConcreteType::ePARTICLE_FLUID, 
		Aggregate = PxConcreteType::eAGGREGATE, 
		Articulation = PxConcreteType::eARTICULATION, 
		ArticulationLink = PxConcreteType::eARTICULATION_LINK, 
		ArticulationJoin = PxConcreteType::eARTICULATION_JOINT, 
		CoreCount = PxConcreteType::ePHYSX_CORE_COUNT,
		FirstPhysXExtension = PxConcreteType::eFIRST_PHYSX_EXTENSION,
		FirstVehicleExtension = PxConcreteType::eFIRST_VEHICLE_EXTENSION,
		FirstUserExtension = PxConcreteType::eFIRST_USER_EXTENSION
	};
};