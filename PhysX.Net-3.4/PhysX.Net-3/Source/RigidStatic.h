#pragma once

#include "Actor.h"
#include "RigidActor.h"

namespace PhysX
{
	/// <summary>
	/// RigidStatic represents a static rigid body simulation object in the physics SDK.
	/// RigidStatic objects are static rigid physics entities. They shall be used to define solid objects which are fixed in the world.
	/// </summary>
	public ref class RigidStatic : RigidActor
	{
		internal:
			RigidStatic(PxRigidStatic* rigidStatic, PhysX::IDisposable^ owner);

		public:

		internal:
			property PxRigidStatic* UnmanagedPointer
			{
				PxRigidStatic* get();
			}
	};
};