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
	/// the flags field (see SceneQueryFilterFlags). If neither SceneQueryFilterFlag.Prefilter or SceneQueryFilterFlag.PostFilter
	/// is set, the hit is assumed to be of type SceneQueryHitType.Block for single hit queries and of type SceneQueryHitType.Touch
	/// for multi hit queries. 
	/// </remarks>
	public value class SceneQueryFilterData
	{
		public:
			SceneQueryFilterData(SceneQueryFilterFlag flags);
			SceneQueryFilterData(FilterData data, SceneQueryFilterFlag flags);

		internal:
			static PxSceneQueryFilterData ToUnmanaged(SceneQueryFilterData data);

		public:
			/// <summary>
			/// Filter data associated with the scene query.
			/// </summary>
			property FilterData Data;
			/// <summary>
			/// Filter flags (see <see cref="SceneQueryFilterFlag" />).
			/// </summary>
			property SceneQueryFilterFlag Flags;

	};
};