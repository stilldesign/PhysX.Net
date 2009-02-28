#include "StdAfx.h"

#include "Soft Body Split Pair.h"

#include <NxSoftBodyDesc.h> 

using namespace StillDesign::PhysX;

SoftBodySplitPair::operator NxSoftBodySplitPair( SoftBodySplitPair pair )
{
	NxSoftBodySplitPair p;
		p.faceIndex0 = pair.FaceIndex0;
		p.faceIndex1 = pair.FaceIndex1;
		p.tetrahedronIndex0 = pair.TetrahedronIndex0;
		p.tetrahedronIndex1 = pair.TetrahedronIndex1;
	
	return p;
}
SoftBodySplitPair::operator SoftBodySplitPair( NxSoftBodySplitPair pair )
{
	SoftBodySplitPair p;
		p.FaceIndex0 = pair.faceIndex0;
		p.FaceIndex1 = pair.faceIndex1;
		p.TetrahedronIndex0 = pair.tetrahedronIndex0;
		p.TetrahedronIndex1 = pair.tetrahedronIndex1;
	
	return p;
}

int SoftBodySplitPair::TetrahedronIndex0::get()
{
	return _tetrahedronIndex0;
}
void SoftBodySplitPair::TetrahedronIndex0::set( int value )
{
	_tetrahedronIndex0 = value;
}

int SoftBodySplitPair::TetrahedronIndex1::get()
{
	return _tetrahedronIndex1;
}
void SoftBodySplitPair::TetrahedronIndex1::set( int value )
{
	_tetrahedronIndex1 = value;
}

int SoftBodySplitPair::FaceIndex0::get()
{
	return _faceIndex0;
}
void SoftBodySplitPair::FaceIndex0::set( int value )
{
	_faceIndex0 = value;
}

int SoftBodySplitPair::FaceIndex1::get()
{
	return _faceIndex1;
}
void SoftBodySplitPair::FaceIndex1::set( int value )
{
	_faceIndex1 = value;
}