#pragma once

#include "SceneEnum.h"
#include "FilterData.h"
#include "QueryFilterData.h"

namespace PhysX
{
	value class QueryFilterData;
	ref class QueryCache;
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

		void Raycast(
			Vector3 origin,
			Vector3 unitDirection,
			[Optional] Nullable<float> distance,
			[Optional] Nullable<int> maximumTouchHits,
			[Optional] Nullable<HitFlag> hitFlags,
			[Optional] Nullable<QueryFilterData> filterData,
			/*[Optional] Object^ userData,*/ // TODO: This poses an interesting problem. Perhaps another Dictionary of Object^-to-intptr_t?
			[Optional] QueryCache^ cache);

		property int FilterShaderDataSize
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