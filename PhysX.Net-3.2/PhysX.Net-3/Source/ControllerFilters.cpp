#include "StdAfx.h"
#include "ControllerFilters.h"
#include "FilterData.h"

PxControllerFilters ControllerFilters::ToUnmanaged(ControllerFilters^ filters)
{
	PxFilterData* fd = NULL;
	if (filters->FilterData.HasValue)
	{
		fd = new PxFilterData();
		*fd = PhysX::FilterData::ToUnmanaged(filters->FilterData.Value);
	}

	PxControllerFilters f;
		f.mActiveGroups = filters->ActiveGroups;
		f.mFilterData = fd;
		f.mFilterFlags = ToUnmanagedEnum(PxSceneQueryFilterFlag, filters->FilterFlags);

	return f;
}