#pragma once

namespace physx
{
	class RaycastCCDManager;
}

namespace PhysX
{
	ref class RigidDynamic;
	ref class Shape;
	ref class Scene;

	public ref class RaycastCCDManager
	{
	private:
		physx::RaycastCCDManager* _manager;

	public:
		RaycastCCDManager(Scene^ scene);
		~RaycastCCDManager();
	protected:
		!RaycastCCDManager();

	public:
		bool RegisterRaycastCCDObject(RigidDynamic^ actor, Shape^ shape);

		void DoRaycastCCD(bool doDynamicDynamicCCD);
	};
}