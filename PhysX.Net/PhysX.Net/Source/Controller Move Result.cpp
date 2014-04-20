#include "StdAfx.h"

#include "Controller Move Result.h"

using namespace StillDesign::PhysX;

ControllerMoveResult::ControllerMoveResult( ControllerCollisionFlag collision )
{
	_collision = collision;
}

ControllerCollisionFlag ControllerMoveResult::CollisionFlag::get()
{
	return _collision;
}