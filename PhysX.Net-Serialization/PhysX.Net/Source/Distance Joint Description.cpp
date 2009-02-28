#include "StdAfx.h"

#include "Distance Joint Description.h"
#include "Spring Description.h"
#include "Distance Joint.h"

#include <NxDistanceJointDesc.h> 

using namespace StillDesign::PhysX;

DistanceJointDescription::DistanceJointDescription() : JointDescription( new NxDistanceJointDesc() )
{
	
}
DistanceJointDescription::DistanceJointDescription( NxDistanceJointDesc* desc ) : JointDescription( desc )
{
	
}


float DistanceJointDescription::MinimumDistance::get()
{
	return this->UnmanagedPointer->minDistance;
}
void DistanceJointDescription::MinimumDistance::set( float value )
{
	this->UnmanagedPointer->minDistance = value;
}

float DistanceJointDescription::MaximumDistance::get()
{
	return this->UnmanagedPointer->maxDistance;
}
void DistanceJointDescription::MaximumDistance::set( float value )
{
	this->UnmanagedPointer->maxDistance = value;
}

SpringDescription DistanceJointDescription::Spring::get()
{
	return (SpringDescription)this->UnmanagedPointer->spring;
}
void DistanceJointDescription::Spring::set( SpringDescription value )
{
	this->UnmanagedPointer->spring = (NxSpringDesc)value;
}

DistanceJointFlag DistanceJointDescription::Flags::get()
{
	return (DistanceJointFlag)this->UnmanagedPointer->flags;
}
void DistanceJointDescription::Flags::set( DistanceJointFlag value )
{
	this->UnmanagedPointer->flags = (NxDistanceJointFlag)value;
}

NxDistanceJointDesc* DistanceJointDescription::UnmanagedPointer::get()
{
	return (NxDistanceJointDesc*)JointDescription::UnmanagedPointer;
}