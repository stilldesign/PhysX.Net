#include "StdAfx.h"

#include "Constraint Dominance.h"

using namespace StillDesign::PhysX;

ConstraintDominance::ConstraintDominance( float a, float b )
{
	_a = a;
	_b = b;
}

ConstraintDominance::operator NxConstraintDominance( ConstraintDominance dominance )
{
	return NxConstraintDominance( dominance.Dominance0, dominance.Dominance1 );
}
ConstraintDominance::operator ConstraintDominance( NxConstraintDominance dominance )
{
	return ConstraintDominance( dominance.dominance0, dominance.dominance1 );
}

float ConstraintDominance::Dominance0::get()
{
	return _a;
}
void ConstraintDominance::Dominance0::set( float value )
{
	_a = value;
}
float ConstraintDominance::Dominance1::get()
{
	return _b;
}
void ConstraintDominance::Dominance1::set( float value )
{
	_b = value;
}