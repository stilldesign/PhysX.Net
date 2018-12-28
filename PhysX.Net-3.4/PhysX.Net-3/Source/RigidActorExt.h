#pragma once

#include "ShapeFlag.h"

namespace PhysX
{
	ref class RigidActor;
	ref class Shape;
	ref class Material;
	ref class Geometry;

	public ref class RigidActorExt abstract
	{
	public:
		static Shape^ CreateExclusiveShape(
			RigidActor^ actor,
			Geometry^ geometry,
			Material^ material,
			Nullable<ShapeFlag> shapeFlags);

		static Shape^ CreateExclusiveShape(
			RigidActor^ actor,
			Geometry^ geometry,
			array<Material^>^ materials,
			Nullable<ShapeFlag> shapeFlags);
	};
}
