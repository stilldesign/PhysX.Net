#include "StdAfx.h"

#include "Groups Mask.h"

using namespace StillDesign::PhysX;

GroupsMask::GroupsMask( unsigned int bits0, unsigned int bits1, unsigned int bits2, unsigned int bits3 )
{
	this->Bits0 = bits0;
	this->Bits1 = bits1;
	this->Bits2 = bits2;
	this->Bits3 = bits3;
}

GroupsMask::operator GroupsMask( NxGroupsMask groupsMask )
{
	GroupsMask g;
		g.Bits0 = groupsMask.bits0;
		g.Bits1 = groupsMask.bits1;
		g.Bits2 = groupsMask.bits2;
		g.Bits3 = groupsMask.bits3;
	
	return g;
}
GroupsMask::operator NxGroupsMask( GroupsMask groupsMask )
{
	NxGroupsMask g;
		g.bits0 = groupsMask.Bits0;
		g.bits1 = groupsMask.Bits1;
		g.bits2 = groupsMask.Bits2;
		g.bits3 = groupsMask.Bits3;
	
	return g;
}