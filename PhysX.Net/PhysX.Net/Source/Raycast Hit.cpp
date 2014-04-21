#include "StdAfx.h"

#include "Raycast Hit.h"
#include "Scene.h"
#include "Shape.h"

using namespace StillDesign::PhysX;

RaycastHit::operator NxRaycastHit( RaycastHit^ rayCastHit )
{
	NxRaycastHit hit;
		if( rayCastHit->Shape != nullptr )
			hit.shape = rayCastHit->Shape->UnmanagedPointer;
		hit.distance = rayCastHit->Distance;
		hit.faceID = rayCastHit->FaceID;
		hit.flags = (NxU32)rayCastHit->Flags;
		hit.internalFaceID = rayCastHit->InternalFaceID;
		hit.materialIndex = rayCastHit->MaterialIndex;
		hit.u = rayCastHit->U;
		hit.v = rayCastHit->V;
		hit.worldImpact = Math::Vector3ToNxVec3( rayCastHit->WorldImpact );
		hit.worldNormal = Math::Vector3ToNxVec3( rayCastHit->WorldNormal );
	
	return hit;
}
RaycastHit::operator RaycastHit^( NxRaycastHit hit )
{
	RaycastHit^ managedHit = gcnew RaycastHit();
		if( hit.shape != NULL )
			managedHit->_shape = ObjectTable::GetObject<StillDesign::PhysX::Shape^>( (intptr_t)hit.shape );
		managedHit->_distance = hit.distance;
		managedHit->_faceID = hit.faceID;
		managedHit->_flags = (RaycastBit)hit.flags;
		managedHit->_internalFaceID = hit.internalFaceID;
		managedHit->_materialID = hit.materialIndex;
		managedHit->_u = hit.u;
		managedHit->_v = hit.v;
		managedHit->_worldImpact = Math::NxVec3ToVector3( hit.worldImpact );
		managedHit->_worldNormal = Math::NxVec3ToVector3( hit.worldNormal );
	
	return managedHit;
}

StillDesign::PhysX::Shape^ RaycastHit::Shape::get()
{
	return _shape;
}
void RaycastHit::Shape::set( StillDesign::PhysX::Shape^ value )
{
	_shape = value;
}

Vector3 RaycastHit::WorldImpact::get()
{
	return _worldImpact;
}
void RaycastHit::WorldImpact::set( Vector3 value )
{
	_worldImpact = value;
}

Vector3 RaycastHit::WorldNormal::get()
{
	return _worldNormal;
}
void RaycastHit::WorldNormal::set( Vector3 value )
{
	_worldNormal = value;
}

int RaycastHit::FaceID::get()
{
	return _faceID;
}
void RaycastHit::FaceID::set( int value )
{
	_faceID = value;
}

int RaycastHit::InternalFaceID::get()
{
	return _internalFaceID;
}
void RaycastHit::InternalFaceID::set( int value )
{
	_internalFaceID = value;
}

float RaycastHit::Distance::get()
{
	return _distance;
}
void RaycastHit::Distance::set( float value )
{
	_distance = value;
}

float RaycastHit::U::get()
{
	return _u;
}
void RaycastHit::U::set( float value )
{
	_u = value;
}

float RaycastHit::V::get()
{
	return _v;
}
void RaycastHit::V::set( float value )
{
	_v = value;
}

short RaycastHit::MaterialIndex::get()
{
	return _materialID;
}
void RaycastHit::MaterialIndex::set( short value )
{
	_materialID = value;
}

RaycastBit RaycastHit::Flags::get()
{
	return _flags;
}
void RaycastHit::Flags::set( RaycastBit value )
{
	_flags = value;
}