#include "StdAfx.h"
#include "SceneDesc.h"
#include "TolerancesScale.h"
#include <PxSceneDesc.h>

using namespace PhysX;
using namespace PhysX::MathPrimitives;

SceneDesc::SceneDesc()
{
	PxTolerancesScale scale;

	_sceneDesc = new PxSceneDesc(scale);
}
SceneDesc::SceneDesc(TolerancesScale tolerancesScale)
{
	_sceneDesc = new PxSceneDesc(TolerancesScale::ToUnmanaged(tolerancesScale));
}
SceneDesc::~SceneDesc()
{
	this->!SceneDesc();
}
SceneDesc::!SceneDesc()
{
	
}
bool SceneDesc::Disposed::get()
{
	return _sceneDesc == NULL;
}

Vector3 SceneDesc::Gravity::get()
{
	return MathUtil::PxVec3ToVector3(_sceneDesc->gravity);
}
void SceneDesc::Gravity::set(Vector3 value)
{
	_sceneDesc->gravity = MathUtil::Vector3ToPxVec3(value);
}

PxSceneDesc* SceneDesc::UnmanagedPointer::get()
{
	return _sceneDesc;
}