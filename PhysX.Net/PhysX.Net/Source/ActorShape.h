#pragma once

#include "SceneEnum.h"
#include "Shape.h"

namespace PhysX
{
	ref class RigidActor;

	public ref class ActorShape
	{
	internal:
		void PopulateManaged(PxActorShape unmanaged);
		void PopulateUnmanaged(PxActorShape& unmanaged);

	public:
		ActorShape();
		ActorShape(RigidActor^ actor, PhysX::Shape^ shape);

		property RigidActor^ Actor;
		property PhysX::Shape^ Shape;
	};
};