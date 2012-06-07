#pragma once

#include "SceneEnum.h"
#include "FilterData.h"
#include <PxBatchQuery.h> 

namespace PhysX
{
	value class SceneQueryFilterData;
	ref class SceneQueryCache;
	ref class Geometry;
	ref class SweepCache;
	ref class BatchQueryPreFilterShader;
	ref class BatchQueryPostFilterShader;

	/// <summary>
	/// Batched queries object. This is used to perform several queries at the same time.
	/// </summary>
	public ref class BatchQuery : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxBatchQuery* _batchQuery;

		BatchQueryPreFilterShader^ _preFilterShader;
		BatchQueryPostFilterShader^ _postFilterShader;

	internal:
		BatchQuery(PxBatchQuery* batchQuery);
	public:
		~BatchQuery();
	protected:
		!BatchQuery();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

	public:
		void Execute();

		//Object^ GetFilterShaderData();

		void Release();

		void RaycastAny(Vector3 origin, Vector3 unitDir);
		void RaycastAny(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache);
		
		void RaycastSingle(Vector3 origin, Vector3 unitDir, float distance);
		void RaycastSingle(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData^ filterData, SceneQueryFlags outputFlags, Object^ userData, SceneQueryCache^ cache);
 
		void RaycastMultiple(Vector3 origin, Vector3 unitDir);
		void RaycastMultiple(Vector3 origin, Vector3 unitDir, float distance, SceneQueryFilterData filterData, SceneQueryFlags outputFlags, Object^ userData, SceneQueryCache^ cache);

		void OverlapMultiple(Geometry^ geometry, Matrix pose);
		void OverlapMultiple(Geometry^ geometry, Matrix pose, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache, int maxShapes);
		
		void OverlapAny(Geometry^ geometry, Matrix pose);
		void OverlapAny(Geometry^ geometry, Matrix pose, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache);
		
		void SweepSingle(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance);
		void SweepSingle(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance, SceneQueryFlags outputFlags, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache);

		void LinearCompoundGeometrySweepSingle(array<Geometry^>^ geometries, array<Matrix>^ poseList, array<FilterData>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, SceneQueryFlags outputFlags);
		void LinearCompoundGeometrySweepSingle(array<Geometry^>^ geometries, array<Matrix>^ poseList, array<FilterData>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, SceneQueryFlags outputFlags, Object^ userData, SweepCache^ cache);
		
		void SweepMultiple(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance);
		void SweepMultiple(Geometry^ geometry, Matrix pose, Vector3 unitDir, float distance, SceneQueryFlags outputFlags, SceneQueryFilterData^ filterData, Object^ userData, SceneQueryCache^ cache);
		
		void LinearCompoundGeometrySweepMultiple(array<Geometry^>^ geometryList, array<Matrix>^ poseList, array<FilterData^>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, PxSceneQueryFlags outputFlags);
		void LinearCompoundGeometrySweepMultiple(array<Geometry^>^ geometryList, array<Matrix>^ poseList, array<FilterData^>^ filterDataList, Vector3 unitDirection, float distance, SceneQueryFilterFlag filterFlags, PxSceneQueryFlags outputFlags, Object^ userData, SweepCache^ cache);
		
		property int FilterShaderDataSize
		{
			int get();
		}

		property int OwnerClient
		{
			int get();
		}

		property BatchQueryPreFilterShader^ PreFilterShader
		{
			BatchQueryPreFilterShader^ get();
		}
		property BatchQueryPostFilterShader^ PostFilterShader
		{
			BatchQueryPostFilterShader^ get();
		}

		//

	internal:
		property PxBatchQuery* UnmanagedPointer
		{
			PxBatchQuery* get();
		}
	};
};