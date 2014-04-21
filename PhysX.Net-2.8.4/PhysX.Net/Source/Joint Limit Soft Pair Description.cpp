#include "StdAfx.h"

#include "Joint Limit Soft Pair Description.h"
#include "Joint Limit Soft Description.h"

#include <NxJointLimitSoftPairDesc.h> 

using namespace StillDesign::PhysX;

JointLimitSoftPairDescription JointLimitSoftPairDescription::FromUnmanaged( NxJointLimitSoftPairDesc jointLimitSoftPairDescription )
{
	JointLimitSoftPairDescription desc;
		desc.Low = JointLimitSoftDescription::FromUnmanaged( jointLimitSoftPairDescription.low );
		desc.High = JointLimitSoftDescription::FromUnmanaged( jointLimitSoftPairDescription.high );
	
	return desc;
}
NxJointLimitSoftPairDesc JointLimitSoftPairDescription::ToUnmanaged( JointLimitSoftPairDescription jointLimitSoftPairDescription )
{
	NxJointLimitSoftPairDesc desc;
		desc.low = JointLimitSoftDescription::ToUnmanaged( jointLimitSoftPairDescription.Low );
		desc.high = JointLimitSoftDescription::ToUnmanaged( jointLimitSoftPairDescription.High );
	
	return desc;
}

JointLimitSoftDescription JointLimitSoftPairDescription::Low::get()
{
	return _low;
}
void JointLimitSoftPairDescription::Low::set( JointLimitSoftDescription value )
{
	_low = value;
}

JointLimitSoftDescription JointLimitSoftPairDescription::High::get()
{
	return _high;
}
void JointLimitSoftPairDescription::High::set( JointLimitSoftDescription value )
{
	_high = value;
}