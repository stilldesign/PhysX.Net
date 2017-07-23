#include "StdAfx.h"
#include "VolumeCache.h"
#include "BoxGeometry.h"
#include "Actor.h"
#include "Shape.h"
#include "ActorShape.h"
#include "GeometryHolder.h"

InternalShapeIterator::InternalShapeIterator(gcroot<Action<array<ActorShape^>^>^> action)
{
	_action = action;
}
void InternalShapeIterator::processShapes(PxU32 count, const PxActorShape* actorShapePairs)
{
	auto as = gcnew array<ActorShape^>(count);

	for (unsigned int i = 0; i < count; i++)
	{
		PxActorShape x = actorShapePairs[i];

		auto actor = ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)x.actor);
		auto shape = ObjectTable::Instance->GetObject<Shape^>((intptr_t)x.shape);

		as[i] = gcnew ActorShape(actor, shape);
	}

	_action->Invoke(as);
}

VolumeCache::VolumeCache(PxVolumeCache* volumeCache)
{
	if (volumeCache == NULL)
		throw gcnew ArgumentNullException("volumeCache");

	_volumeCache = volumeCache;
}
VolumeCache::~VolumeCache()
{
	this->!VolumeCache();
}
VolumeCache::!VolumeCache()
{
	if (_volumeCache == NULL)
		return;

	_volumeCache->release();
	_volumeCache = NULL;
}

VolumeCacheFillStatus VolumeCache::Fill(Geometry^ cacheVolume, Matrix pose)
{
	PxGeometry* cv = cacheVolume->ToUnmanaged();
	PxTransform p = MathUtil::MatrixToPxTransform(pose);

	auto f = _volumeCache->fill(*cv, p);

	return ToManagedEnum(VolumeCacheFillStatus, f);
}

bool VolumeCache::IsValid()
{
	return _volumeCache->isValid();
}

void VolumeCache::Invalidate()
{
	_volumeCache->invalidate();
}

CacheVolumeResult^ VolumeCache::GetCacheVolume()
{
	// Initalize this as a pointer otherwise the compiler complains that it can't be used
	// in a managed method. This is because PxGeometryHolder is PX_ALIGN_PREFIX(4)
	PxGeometryHolder* gh = new PxGeometryHolder();
	PxTransform pose;

	try
	{
		bool success = _volumeCache->getCacheVolume(*gh, pose);

		if (!success)
			return nullptr;

		auto result = gcnew CacheVolumeResult();
			result->Geometry = nullptr;// GeometryHolder::GetGeometryFromUnmanaged(gh);
			result->Transform = MathUtil::PxTransformToMatrix(&pose);

		return result;
	}
	finally
	{
		delete gh;
	}
}

void VolumeCache::Foreach(Action<array<ActorShape^>^>^ action)
{
	ThrowIfNull(action, "action");

	InternalShapeIterator i(action);

	_volumeCache->forEach(i);
}

void VolumeCache::Release()
{
	_volumeCache->release();
}

int VolumeCache::NumberOfCachedShapes::get()
{
	return _volumeCache->getNbCachedShapes();
}

int VolumeCache::MaximumNumberOfStaticShapes::get()
{
	return _volumeCache->getMaxNbStaticShapes();
}
void VolumeCache::MaximumNumberOfStaticShapes::set(int value)
{
	_volumeCache->setMaxNbStaticShapes(value);
}

int VolumeCache::MaximumNumberOfDynamicShapes::get()
{
	return _volumeCache->getMaxNbDynamicShapes();
}
void VolumeCache::MaximumNumberOfDynamicShapes::set(int value)
{
	_volumeCache->setMaxNbDynamicShapes(value);
}

PxVolumeCache* VolumeCache::UnmanagedPointer::get()
{
	return _volumeCache;
}