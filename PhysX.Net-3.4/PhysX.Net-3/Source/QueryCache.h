#pragma once


namespace PhysX
{
	ref class Shape;
	ref class RigidActor;

	public ref class QueryCache
	{
	internal:
		static QueryCache^ ToManaged(PxQueryCache unmanaged);
		static PxQueryCache ToUnmanaged(QueryCache^ managed);

	public:
		property Shape^ Shape;
		property RigidActor^ Actor;
		property int FaceIndex;
	};
};