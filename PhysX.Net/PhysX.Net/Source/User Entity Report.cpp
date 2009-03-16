#include "StdAfx.h"

#include "User Entity Report.h"
#include "Scene.h"
#include "Shape.h"
#include "Sweep Query Hit.h"
#include "Actor.h"

using namespace StillDesign::PhysX;

UserEntityShapeReport::UserEntityShapeReport()
{
	_entityReport = new EntityShapeReport( this );
}
UserEntityShapeReport::~UserEntityShapeReport()
{
	this->!UserEntityShapeReport();
}
UserEntityShapeReport::!UserEntityShapeReport()
{
	SAFE_DELETE( _entityReport );
}

EntityShapeReport* UserEntityShapeReport::UnmanagedPointer::get()
{
	return _entityReport;
}

EntityShapeReport::EntityShapeReport( UserEntityShapeReport^ userEntityShapeReport )
{
	_userEntityShapeReport = userEntityShapeReport;
}
EntityShapeReport::~EntityShapeReport()
{
	_userEntityShapeReport = nullptr;
}

bool EntityShapeReport::onEvent( NxU32 nbEntities, NxShape** entities )
{
	array<Shape^>^ shapes = gcnew array<Shape^>( nbEntities );
	for( unsigned int x = 0; x < nbEntities; x++ )
	{
		shapes[ x ] = ObjectTable::GetObject<Shape^>( (intptr_t)entities[ x ] );
	}
	
	return _userEntityShapeReport->OnEvent( shapes );
}

////////////////////////////////

UserEntitySweepQueryHitReport::UserEntitySweepQueryHitReport()
{
	_entityReport = new EntitySweepQueryHitReport( this );
}
UserEntitySweepQueryHitReport::~UserEntitySweepQueryHitReport()
{
	this->!UserEntitySweepQueryHitReport();
}
UserEntitySweepQueryHitReport::!UserEntitySweepQueryHitReport()
{
	SAFE_DELETE( _entityReport );
	
	_scene = nullptr;
}

EntitySweepQueryHitReport* UserEntitySweepQueryHitReport::UnmanagedPointer::get()
{
	return _entityReport;
}

EntitySweepQueryHitReport::EntitySweepQueryHitReport( UserEntitySweepQueryHitReport^ userEntitySweepQueryHitReport )
{
	_userEntitySweepQueryHitReport = userEntitySweepQueryHitReport;
}
EntitySweepQueryHitReport::~EntitySweepQueryHitReport()
{
	_userEntitySweepQueryHitReport = nullptr;
}

bool EntitySweepQueryHitReport::onEvent( NxU32 nbEntities, NxSweepQueryHit* entities )
{
	array<SweepQueryHit^>^ hits = gcnew array<SweepQueryHit^>( nbEntities );
	
	for( unsigned int x = 0; x < nbEntities; x++ )
	{
		NxSweepQueryHit* hit = new NxSweepQueryHit( entities[ x ] );
		
		hits[ x ] = gcnew SweepQueryHit( hit, nullptr );
	}
	
	return _userEntitySweepQueryHitReport->OnEvent( hits );
}