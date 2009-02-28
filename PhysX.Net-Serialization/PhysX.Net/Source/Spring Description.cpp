#include "StdAfx.h"
#include "Spring Description.h"

using namespace StillDesign::PhysX;

SpringDescription::SpringDescription( float springCoefficient, float damperCoefficient, float targetValue )
{
	_spring = springCoefficient;
	_damper = damperCoefficient;
	_targetValue = targetValue;
}

SpringDescription::operator NxSpringDesc( SpringDescription springDesc )
{
	return NxSpringDesc( springDesc.SpringCoefficient, springDesc.DamperCoefficient, springDesc.TargetValue );
}
SpringDescription::operator SpringDescription( NxSpringDesc springDesc )
{
	return SpringDescription( springDesc.spring, springDesc.damper, springDesc.targetValue );
}

float SpringDescription::SpringCoefficient::get()
{
	return _spring;
}
void SpringDescription::SpringCoefficient::set( float value )
{
	_spring = value;
}

float SpringDescription::DamperCoefficient::get()
{
	return _damper;
}
void SpringDescription::DamperCoefficient::set( float value )
{
	_damper = value;
}

float SpringDescription::TargetValue::get()
{
	return _targetValue;
}
void SpringDescription::TargetValue::set( float value )
{
	_targetValue = value;
}