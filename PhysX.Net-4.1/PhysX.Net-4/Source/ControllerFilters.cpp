#include "StdAfx.h"
#include "ControllerFilters.h"
#include "FilterData.h"

PxControllerFilters ControllerFilters::ToUnmanaged(ControllerFilters^ filters)
{
	if (filters == nullptr)
		throw gcnew ArgumentNullException("filters");

	PxFilterData* fd = NULL;
	if (filters->FilterData.HasValue)
	{
		fd = new PxFilterData();
		*fd = PhysX::FilterData::ToUnmanaged(filters->FilterData.Value);
	}

	PxControllerFilters f;
		f.mFilterData = fd;
		f.mFilterFlags = ToUnmanagedEnum(PxQueryFlag, filters->FilterFlags);

	return f;
}