#pragma once

namespace PhysX
{
	ref class RigidActor;
	ref class Shape;
	ref class ContactSet;

	public ref class ContactModifyPair
	{
	internal:
		static ContactModifyPair^ ToManaged(PxContactModifyPair* unmanaged);
		static PxContactModifyPair ToUnmanaged(ContactModifyPair^ pair);

	public:
		property RigidActor^ ActorA;
		property RigidActor^ ActorB;

		property Shape^ ShapeA;
		property Shape^ ShapeB;

		property Matrix TransformA;
		property Matrix TransformB;

		property ContactSet^ Contacts;
	};
}