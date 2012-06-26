#pragma once

namespace PhysX
{
	public enum class ConcreteType
	{
		Undefined = PxConcreteType::eUNDEFINED, 
		Heightfield = PxConcreteType::eHEIGHTFIELD, 
		ConvexMesh = PxConcreteType::eCONVEX_MESH, 
		TriangleMesh = PxConcreteType::eTRIANGLE_MESH, 
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
		UserSphericalJoint = PxConcreteType::eUSER_SPHERICAL_JOINT, 
		UserRevoluteJoint = PxConcreteType::eUSER_REVOLUTE_JOINT, 
		UserPrismaticJoint = PxConcreteType::eUSER_PRISMATIC_JOINT, 
		UserFixedJoin = PxConcreteType::eUSER_FIXED_JOINT, 
		UserDistanceJoint = PxConcreteType::eUSER_DISTANCE_JOINT, 
		UserD6Joint = PxConcreteType::eUSER_D6_JOINT, 
		UserObserver = PxConcreteType::eUSER_OBSERVER
	};
};