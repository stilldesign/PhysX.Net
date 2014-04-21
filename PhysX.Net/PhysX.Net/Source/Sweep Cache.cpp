#include "StdAfx.h"

#include "Sweep Cache.h"
#include "Box.h"
#include "Scene.h"

#include <NxActor.h> 

using namespace StillDesign::PhysX;

SweepCache::SweepCache( NxSweepCache* sweepCache, StillDesign::PhysX::Scene^ scene )
{
	Debug::Assert( sweepCache != NULL );
	Debug::Assert( scene != nullptr );
	
	ObjectTable::Add( (intptr_t)_sweepCache, this );
	
	_sweepCache = sweepCache;
	_scene = scene;
}
SweepCache::~SweepCache()
{
	this->!SweepCache();
}
SweepCache::!SweepCache()
{
	if( this->IsDisposed )
		return;
	
	OnDisposing( this, nullptr );
	
	_scene->UnmanagedPointer->releaseSweepCache( _sweepCache );
	
	_sweepCache = NULL;
	_scene = nullptr;
	
	OnDisposed( this, nullptr );
}
bool SweepCache::IsDisposed::get()
{
	return ( _sweepCache == NULL );
}

StillDesign::PhysX::Scene^ SweepCache::Scene::get()
{
	return _scene;
}

void SweepCache::SetVolume( Box volume )
{
	_sweepCache->setVolume( (NxBox)volume );
}

NxSweepCache* SweepCache::UnmanagedPointer::get()
{
	return _sweepCache;
}