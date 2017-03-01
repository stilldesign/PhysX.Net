#include "StdAfx.h"
#include "QueryFilterData.h"

QueryFilterData::QueryFilterData(QueryFlag flags)
{
	Flags = flags;
}
QueryFilterData::QueryFilterData(FilterData data, QueryFlag flags)
{
	Data = data;
	Flags = flags;
}

PxQueryFilterData QueryFilterData::ToUnmanaged(QueryFilterData data)
{
	PxQueryFilterData d;
		d.data = FilterData::ToUnmanaged(data.Data);
		d.flags = ToUnmanagedEnum2(PxQueryFlags, data.Flags);

	return d;
}