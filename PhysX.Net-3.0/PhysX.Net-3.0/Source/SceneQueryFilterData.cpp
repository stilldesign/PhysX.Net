#include "StdAfx.h"
#include "SceneQueryFilterData.h"

SceneQueryFilterData::SceneQueryFilterData(SceneQueryFilterFlag flags)
{
	Flags = flags;
}
SceneQueryFilterData::SceneQueryFilterData(FilterData data, SceneQueryFilterFlag flags)
{
	Data = data;
	Flags = flags;
}

PxSceneQueryFilterData SceneQueryFilterData::ToUnmanaged(SceneQueryFilterData data)
{
	PxSceneQueryFilterData d;
		d.data = FilterData::ToUnmanaged(data.Data);
		d.flags = ToUnmanagedEnum2(PxSceneQueryFilterFlags, data.Flags);

	return d;
}