/*
	HACK
	This file is needed because inside getWorldBounds, it somewhere defines ALIGN and you can't
	compile managed methods with byte aligned attributes.
	You get a C4793 warning, which then causes the linker to absolutely explode, it says
	that PxUnionCast<PxGeometry, char> is already defined - absolutely meaningless.
	This file is explicitly set to compile with-out the /clr flag. We then call this from our managed code.
*/

#include <foundation\PxBounds3.h> 
#include <PxShape.h>
#include <PxRigidActor.h>
#include <extensions\PxShapeExt.h>
#include "ShapeUtil.h"

using namespace physx;

PxBounds3 ShapeUtil::GetWorldBoundsUnmanaged(PxShape* shape, PxRigidActor* actor)
{
	return PxShapeExt::getWorldBounds(*shape, *actor);
}