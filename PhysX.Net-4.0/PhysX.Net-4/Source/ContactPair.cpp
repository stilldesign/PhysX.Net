#include "StdAfx.h"
#include "ContactPair.h"
#include "ContactPairPoint.h"

ContactPair::ContactPair(PxContactPair* pair)
{
	ThrowIfNull(pair, "pair");

	_pair = pair;

	this->Shape0 = ObjectTable::Instance->TryGetObject<Shape^>((intptr_t)pair->shapes[0]);
	this->Shape1 = ObjectTable::Instance->TryGetObject<Shape^>((intptr_t)pair->shapes[1]);

	this->ContactPoints = (pair->contactPoints == NULL) ?
		nullptr :
		Util::AsManagedArray<Byte>(pair->contactPoints, pair->contactStreamSize);

	this->RequiredBufferSize = pair->requiredBufferSize;
	this->ContactCount = pair->contactCount;
	this->Flags = ToManagedEnum(ContactPairFlag, pair->flags);
}
ContactPair::~ContactPair()
{
	this->!ContactPair();
}
ContactPair::!ContactPair()
{
	this->Shape0 = nullptr;
	this->Shape1 = nullptr;
	this->ContactPoints = nullptr;
	this->RequiredBufferSize = 0;
	this->ContactCount = 0;
	this->Flags = (ContactPairFlag)0;
}

array<ContactPairPoint^>^ ContactPair::ExtractContacts()
{
	int n = _pair->contactCount;

	auto contacts = gcnew array<ContactPairPoint^>(n);

	PxContactPairPoint* cpp = new PxContactPairPoint[n];

	_pair->extractContacts(cpp, n);

	for (int i = 0; i < n; i++)
	{
		contacts[i] = ContactPairPoint::ToManaged(cpp[i]);
	}

	delete[] cpp;

	return contacts;
}