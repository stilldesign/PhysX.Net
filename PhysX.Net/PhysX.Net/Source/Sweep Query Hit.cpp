#include "StdAfx.h"

#include "Sweep Query Hit.h"

using namespace StillDesign::PhysX;

SweepQueryHit::SweepQueryHit()
{
	
}
SweepQueryHit::~SweepQueryHit()
{
	this->!SweepQueryHit();
}
SweepQueryHit::!SweepQueryHit()
{
	SAFE_DELETE( _hit );
}
SweepQueryHit::SweepQueryHit( NxSweepQueryHit* hit, Object^ userData )
{
	Debug::Assert( hit != NULL );
	
	_hit = hit;
	
	if( hit->hitShape != NULL )
		_hitShape = ObjectTable::GetObject<Shape^>( (intptr_t)hit->hitShape );
		
	if( hit->sweepShape != NULL )
		_sweepShape = ObjectTable::GetObject<Shape^>( (intptr_t)hit->sweepShape );
		
	_userData = userData;
}

float SweepQueryHit::T::get()
{
	return _hit->t;
}
Shape^ SweepQueryHit::HitShape::get()
{
	return _hitShape;
}
Shape^ SweepQueryHit::SweepShape::get()
{
	return _sweepShape;
}
Object^ SweepQueryHit::UserData::get()
{
	return _userData;
}
int SweepQueryHit::InternalFaceID::get()
{
	return _hit->internalFaceID;
}
int SweepQueryHit::FaceID::get()
{
	return _hit->faceID;
}
Vector3 SweepQueryHit::Point::get()
{
	return Math::NxVec3ToVector3( _hit->point );
}
Vector3 SweepQueryHit::Normal::get()
{
	return Math::NxVec3ToVector3( _hit->normal );
}