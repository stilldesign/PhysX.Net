#include "StdAfx.h"
#include "BatchQuery.h"
#include "SceneQueryFilterData.h"

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

void BatchQuery::RaycastAny(Vector3 origin, Vector3 unitDir)
{
	_batchQuery->raycastAny(UV(origin), UV(unitDir));
}
void BatchQuery::RaycastAny(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::RaycastSingle(Vector3 origin, Vector3 unitDir, float distance)
{

}
void BatchQuery::RaycastSingle(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData^ filterData, SceneQueryFlags outputFlags, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::RaycastMultiple(Vector3 origin, Vector3 unitDir)
{

}
void BatchQuery::RaycastMultiple(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData filterData, SceneQueryFlags outputFlags, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::OverlapMultiple(Geometry^ geometry, Matrix pose)
{

}
void BatchQuery::OverlapMultiple(Geometry^ geometry, Matrix pose, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache, int maxShapes)
{

}

void BatchQuery::OverlapAny(Geometry^ geometry, Matrix pose)
{

}
void BatchQuery::OverlapAny(Geometry^ geometry, Matrix pose, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::SweepSingle(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance)
{

}
void BatchQuery::SweepSingle(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance, SceneQueryFlags outputFlags, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::LinearCompoundGeometrySweepSingle(array<Geometry^>^ geometries, array<Matrix>^ poseList, array<FilterData>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, SceneQueryFlags outputFlags)
{

}
void BatchQuery::LinearCompoundGeometrySweepSingle(array<Geometry^>^ geometries, array<Matrix>^ poseList, array<FilterData>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, SceneQueryFlags outputFlags, Object^ userData, SweepCache^ cache)
{

}

void BatchQuery::SweepMultiple(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance)
{

}
void BatchQuery::SweepMultiple(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance, SceneQueryFlags outputFlags, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache)
{

}

void BatchQuery::LinearCompoundGeometrySweepMultiple(array<Geometry^>^ geometryList, array<Matrix>^ poseList, array<FilterData^>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, PxSceneQueryFlags outputFlags)
{

}
void BatchQuery::LinearCompoundGeometrySweepMultiple(array<Geometry^>^ geometryList, array<Matrix>^ poseList, array<FilterData^>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, PxSceneQueryFlags outputFlags, Object^ userData, SweepCache^ cache)
{

}
		
int BatchQuery::FilterShaderDataSize::get()
{
	return _batchQuery->getFilterShaderDataSize();
}

int BatchQuery::OwnerClient::get()
{
	return _batchQuery->getOwnerClient();
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