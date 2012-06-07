#pragma once

#include "SceneEnum.h"
#include "FilterData.h"
#include <PxController.h> 

namespace PhysX
{
	// TODO: Add PxSceneQueryFilterCallback
	public ref class ControllerFilters
	{
	internal:
		static PxControllerFilters ToUnmanaged(ControllerFilters^ filters);

	public:
		/// <summary>
		/// Gets or sets a filtering mask for collision groups. If a bit is set, corresponding group is active.
		/// </summary>
		property int ActiveGroups;

		/// <summary>
		/// Gets or sets an alternative filter data used to filter shapes.
		/// </summary>
		property Nullable<PhysX::FilterData> FilterData;

		/// <summary>
		/// Gets or sets filter flags.
		/// </summary>
		property SceneQueryFilterFlag FilterFlags;
	};
};