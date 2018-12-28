#include "StdAfx.h"
#include "BatchQuery.h"
#include "QueryFilterData.h"
#include "QueryCache.h"
#include "BatchQueryPreFilterShader.h"
#include "BatchQueryPostFilterShader.h"

BatchQuery::BatchQuery(PxBatchQuery* batchQuery)
{
	if (batchQuery == NULL)
		throw gcnew ArgumentNullException("batchQuery");

	_batchQuery = batchQuery;
}
BatchQuery::~BatchQuery()
{
	this->!BatchQuery();
}
BatchQuery::!BatchQuery()
{
	if (!Disposed)
		return;

	_batchQuery->release();
	_batchQuery = NULL;
}

bool BatchQuery::Disposed::get()
{
	return (_batchQuery == NULL);
}

void BatchQuery::Execute()
{
	_batchQuery->execute();
}

//Object^ BatchQuery::GetFilterShaderData()
//{
//
//}

void BatchQuery::Release()
{
	_batchQuery->release();
}

void BatchQuery::Raycast(
	Vector3 origin,
	Vector3 unitDirection,
	[Optional] Nullable<float> distance,
	[Optional] Nullable<int> maximumTouchHits,
	[Optional] Nullable<HitFlag> hitFlags,
	[Optional] Nullable<QueryFilterData> filterData,
	/*[Optional] Object^ userData,*/
	[Optional] QueryCache^ cache)
{
	PxVec3 o = UV(origin);
	PxVec3 d = UV(unitDirection);
	float dis = distance.GetValueOrDefault(PX_MAX_F32);
	PxU16 max = (PxU16)maximumTouchHits.GetValueOrDefault(0);
	PxHitFlags hf = ToUnmanagedEnum2(PxHitFlags, hitFlags.GetValueOrDefault(HitFlag::Default));
	PxQueryFilterData qfd = QueryFilterData::ToUnmanaged(filterData.GetValueOrDefault(QueryFilterData()));
	PxQueryCache* qc = cache == nullptr ? NULL : &QueryCache::ToUnmanaged(cache);

	_batchQuery->raycast(o, d, dis, max, hf, qfd, NULL, qc);
}
		
int BatchQuery::FilterShaderDataSize::get()
{
	return _batchQuery->getFilterShaderDataSize();
}

BatchQueryPreFilterShader^ BatchQuery::PreFilterShader::get()
{
	return _preFilterShader;
}
BatchQueryPostFilterShader^ BatchQuery::PostFilterShader::get()
{
	return _postFilterShader;
}

PxBatchQuery* BatchQuery::UnmanagedPointer::get()
{
	return _batchQuery;
}