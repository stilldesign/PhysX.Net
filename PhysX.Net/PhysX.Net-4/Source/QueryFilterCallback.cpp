#include "StdAfx.h"
#include "QueryFilterCallback.h"

QueryFilterCallback::QueryFilterCallback()
{
	_callback = new UserQueryFilterCallback(this);
}
QueryFilterCallback::~QueryFilterCallback()
{
	this->!QueryFilterCallback();
}
QueryFilterCallback::!QueryFilterCallback()
{
	SAFE_DELETE(_callback);
}

//

UserQueryFilterCallback::UserQueryFilterCallback(QueryFilterCallback^ managed)
{
	_managed = managed;
}

PxQueryHitType::Enum UserQueryFilterCallback::preFilter(const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, PxHitFlags& queryFlags)
{
	auto fd = FilterData::ToManaged(filterData);
	auto s = (shape == NULL ? nullptr : ObjectTable::Instance->GetObject<Shape^>((intptr_t)shape));
	auto a = (actor == NULL ? nullptr : ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)actor));
	auto qf = ToManagedEnum(HitFlag, queryFlags);

	QueryHitType ret = _managed->PreFilter(fd, s, a, qf);

	return ToUnmanagedEnum(PxQueryHitType, ret);
}
PxQueryHitType::Enum UserQueryFilterCallback::postFilter(const PxFilterData& filterData, const PxQueryHit& hit)
{
	auto fd = FilterData::ToManaged(filterData);
	auto qh = QueryHit::ToManaged((PxQueryHit*)&hit);

	QueryHitType ret = _managed->PostFilter(fd, qh);

	return ToUnmanagedEnum(PxQueryHitType, ret);
}

UserQueryFilterCallback* QueryFilterCallback::UnmanagedPointer::get()
{
	return _callback;
}