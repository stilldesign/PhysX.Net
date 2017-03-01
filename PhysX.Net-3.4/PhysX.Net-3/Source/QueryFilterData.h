#pragma once

#include "SceneEnum.h"
#include "FilterData.h"

namespace PhysX
{
	/// <summary>
	/// Scene query filtering data.
	/// </summary>
	/// <remarks>
	/// When the scene graph traversal determines that a shape intersects, filtering is performed.
	/// If the data field is non-zero, and the bitwise-AND value of data AND the shape's queryFilterData is 
	/// zero, the shape is skipped, else the filter callbacks will be get invoked according to the specification in 
	/// the flags field (see QueryFlags). If neither QueryFlag.Prefilter or QueryFlag.PostFilter
	/// is set, the hit is assumed to be of type SceneQueryHitType.Block for single hit queries and of type SceneQueryHitType.Touch
	/// for multi hit queries. 
	/// </remarks>
	public value class QueryFilterData
	{
		public:
			QueryFilterData(QueryFlag flags);
			QueryFilterData(FilterData data, QueryFlag flags);

		internal:
			static PxQueryFilterData ToUnmanaged(QueryFilterData data);

		public:
			/// <summary>
			/// Filter data associated with the scene query.
			/// </summary>
			property FilterData Data;
			/// <summary>
			/// Filter flags (see <see cref="QueryFlag" />).
			/// </summary>
			property QueryFlag Flags;

	};
};