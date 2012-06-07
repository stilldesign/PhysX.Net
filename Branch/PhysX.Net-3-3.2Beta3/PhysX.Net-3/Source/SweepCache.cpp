#include "StdAfx.h"
#include "SweepCache.h"
#include "BoxGeometry.h"

SweepCache::SweepCache(PxSweepCache* sweepCache)
{
	if (sweepCache == NULL)
		throw gcnew ArgumentNullException("sweepCache");

	_sweepCache = sweepCache;
}
SweepCache::~SweepCache()
{
	this->!SweepCache();
}
SweepCache::!SweepCache()
{
	if (_sweepCache == NULL)
		return;

	_sweepCache->release();
	_sweepCache = NULL;
}

void SweepCache::SetVolume(BoxGeometry^ box, Matrix transform)
{
	PxBoxGeometry* b = (PxBoxGeometry*)box->ToUnmanaged();

	_sweepCache->setVolume(*b, MathUtil::MatrixToPxTransform(transform));

	delete b;
}

PxSweepCache* SweepCache::UnmanagedPointer::get()
{
	return _sweepCache;
}