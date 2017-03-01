#pragma once

#include "FilterData.h"
#include "QueryHit.h"

class UserQueryFilterCallback;

namespace PhysX
{
	ref class Shape;
	ref class RigidActor;
	
	public ref class QueryFilterCallback abstract
	{
	private:
		UserQueryFilterCallback* _callback;

	protected:
		QueryFilterCallback();
	public:
		~QueryFilterCallback();
	protected:
		!QueryFilterCallback();

	public:
		virtual QueryHitType PreFilter(FilterData filterData, Shape^ shape, RigidActor^ actor, HitFlag queryFlags) abstract;
		virtual QueryHitType PostFilter(FilterData filterData, QueryHit^ hit) abstract;

	internal:
		property UserQueryFilterCallback* UnmanagedPointer
		{
			UserQueryFilterCallback* get();
		}
	};
};

class UserQueryFilterCallback : public PxQueryFilterCallback
{
private:
	gcroot<PhysX::QueryFilterCallback^> _managed;

public:
	UserQueryFilterCallback(QueryFilterCallback^ managed);

	virtual PxQueryHitType::Enum preFilter(const PxFilterData& filterData, const PxShape* shape, const PxRigidActor* actor, PxHitFlags& queryFlags);
	virtual PxQueryHitType::Enum postFilter(const PxFilterData& filterData, const PxQueryHit& hit);
};