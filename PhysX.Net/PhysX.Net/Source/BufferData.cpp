#include "StdAfx.h"
#include "BufferData.h"

using namespace StillDesign::PhysX;

BufferData::BufferData( bool objectOwner, bool dataOwner )
{
	this->ObjectOwner = false;
	this->DataOwner = false;
}