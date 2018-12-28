#include "StdAfx.h"
#include "RigidActorExt.h"
#include "RigidActor.h"
#include "Geometry.h"
#include "Material.h"
#include "Shape.h"

using namespace PhysX;

Shape^ RigidActorExt::CreateExclusiveShape(
	RigidActor^ actor,
	Geometry^ geometry,
	Material^ material,
	Nullable<ShapeFlag> shapeFlags)
{
	return RigidActorExt::CreateExclusiveShape(
		actor,
		geometry,
		gcnew array<Material^> { material },
		shapeFlags
	);
}

Shape^ RigidActorExt::CreateExclusiveShape(
	RigidActor^ actor,
	Geometry^ geometry,
	array<Material^>^ materials,
	Nullable<ShapeFlag> shapeFlags)
{
	ThrowIfNullOrDisposed(actor, "actor");
	ThrowIfNull(geometry, "geometry");
	ThrowIfNull(materials, "materials");
	for (int i = 0; i < materials->Length; i++)
	{
		ThrowIfNullOrDisposed(materials[i], "materials");
	}

	//

	PxGeometry* g = geometry->ToUnmanaged();

	PxMaterial** m = new PxMaterial*[materials->Length];
	for (int i = 0; i < materials->Length; i++)
	{
		m[i] = materials[i]->UnmanagedPointer;
	}

	PxShape* s = PxRigidActorExt::createExclusiveShape(
		*actor->UnmanagedPointer,
		*g,
		m,
		(PxU16)materials->Length,
		ToUnmanagedEnum2(PxShapeFlags, shapeFlags.GetValueOrDefault(ShapeFlag::Visualization | ShapeFlag::SceneQueryShape | ShapeFlag::SimulationShape))
	);

	delete g;
	delete[] m;

	return gcnew Shape(s, actor);
}