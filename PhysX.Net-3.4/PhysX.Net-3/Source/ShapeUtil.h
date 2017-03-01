#pragma once

class ShapeUtil
{
public:
	static physx::PxBounds3 GetWorldBoundsUnmanaged(physx::PxShape* shape, physx::PxRigidActor* actor);
};