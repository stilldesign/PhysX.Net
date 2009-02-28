#include "StdAfx.h"

#include "Joint Limit Pair Description.h"
#include "Joint Limit Description.h"

#include <NxJointLimitPairDesc.h> 

using namespace StillDesign::PhysX;

JointLimitPairDescription::JointLimitPairDescription( JointLimitDescription low, JointLimitDescription high )
{
	_low = low;
	_high = high;
}

JointLimitPairDescription::operator JointLimitPairDescription( NxJointLimitPairDesc jointLimitPairDesc )
{
	JointLimitPairDescription desc;
		desc.Low = (JointLimitDescription)jointLimitPairDesc.low;
		desc.High = (JointLimitDescription)jointLimitPairDesc.high;
	
	return desc;
}
JointLimitPairDescription::operator NxJointLimitPairDesc( JointLimitPairDescription jointLimitPairDescription )
{
	NxJointLimitPairDesc desc;
		desc.low = (NxJointLimitDesc)jointLimitPairDescription.Low;
		desc.high = (NxJointLimitDesc)jointLimitPairDescription.High;
	
	return desc;
}

JointLimitDescription JointLimitPairDescription::Low::get()
{
	return _low;
}
void JointLimitPairDescription::Low::set( JointLimitDescription value )
{
	_low = value;
}

JointLimitDescription JointLimitPairDescription::High::get()
{
	return _high;
}
void JointLimitPairDescription::High::set( JointLimitDescription value )
{
	_high = value;
}