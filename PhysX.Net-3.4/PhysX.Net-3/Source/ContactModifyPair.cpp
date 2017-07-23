#include "StdAfx.h"
#include "RigidActor.h"
#include "Shape.h"
#include "ContactSet.h"

#include "ContactModifyPair.h"

ContactModifyPair^ ContactModifyPair::ToManaged(PxContactModifyPair* unmanaged)
{
	auto managed = gcnew ContactModifyPair();

	managed->ActorA = (RigidActor^)ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)unmanaged->actor[0]);
	managed->ActorB = (RigidActor^)ObjectTable::Instance->GetObject<RigidActor^>((intptr_t)unmanaged->actor[1]);

	managed->ShapeA = (Shape^)ObjectTable::Instance->GetObject<Shape^>((intptr_t)unmanaged->shape[0]);
	managed->ShapeB = (Shape^)ObjectTable::Instance->GetObject<Shape^>((intptr_t)unmanaged->shape[1]);

	managed->TransformA = MM(&unmanaged->transform[0]);
	managed->TransformB = MM(&unmanaged->transform[1]);

	managed->Contacts = gcnew ContactSet(unmanaged->contacts);

	return managed;
}

PxContactModifyPair ContactModifyPair::ToUnmanaged(ContactModifyPair^ pair)
{
	ThrowIfNull(pair, "pair");
	if (pair->Contacts == nullptr)
		throw gcnew InvalidOperationException("Cannot convert the managed ContactModifyPair to unmanaged as the Contacts property is null");

	PxContactModifyPair unmanaged;
		unmanaged.actor[0] = GetPointerOrNull(pair->ActorA);
		unmanaged.actor[1] = GetPointerOrNull(pair->ActorB);

		unmanaged.contacts = *pair->Contacts->UnmanagedPointer;

		unmanaged.shape[0] = GetPointerOrNull(pair->ShapeA);
		unmanaged.shape[1] = GetPointerOrNull(pair->ShapeB);

		unmanaged.transform[0] = UM(pair->TransformA);
		unmanaged.transform[1] = UM(pair->TransformB);

	return unmanaged;
}