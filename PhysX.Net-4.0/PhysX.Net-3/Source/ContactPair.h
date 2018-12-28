#pragma once

#include "PhysicsEnum.h"

namespace PhysX
{
	ref class Shape;
	ref class ContactPairPoint;

	public ref class ContactPair : System::IDisposable
	{
	private:
		PxContactPair* _pair;

	internal:
		ContactPair(PxContactPair* pair);
	public:
		~ContactPair();
	protected:
		!ContactPair();

	public:
		/// <summary>
		/// Extracts the contact points from the stream and stores them in a convenient format.
		/// </summary>
		array<ContactPairPoint^>^ ExtractContacts();

		// TODO: Implement
		//ContactPair^ BufferContacts();

		/// <summary>
		/// The first of the two shapes that make up the pair. 
		/// Note: The shape pointers might reference deleted shapes.
		/// This will be the case if PairFlag.NotifyTouchLost or PairFlag.NotifyThresholdForceLost events
		/// were requested for the pair and one of the involved shapes gets deleted.Check the flags member to see
		/// whether that is the case.Do not dereference a pointer to a deleted shape.The pointer to a deleted shape is
		/// only provided such that user data structures which might depend on the pointer value can be updated.
		/// </summary>
		property Shape^ Shape0;

		/// <summary>
		/// The second of the two shapes that make up the pair. 
		/// Note: The shape pointers might reference deleted shapes.
		/// This will be the case if PairFlag.NotifyTouchLost or PairFlag.NotifyThresholdForceLost events
		/// were requested for the pair and one of the involved shapes gets deleted.Check the flags member to see
		/// whether that is the case.Do not dereference a pointer to a deleted shape.The pointer to a deleted shape is
		/// only provided such that user data structures which might depend on the pointer value can be updated.
		/// </summary>
		property Shape^ Shape1;

		/// <summary>
		/// Contact stream/data containing contact point data.
		/// This pointer is only valid if contact point information has been requested for the
		/// contact report pair(see PairFlag::NotifyContactPoints).
		/// Use ExtractContacts() as a reference for the data layout of the stream.
		/// </summary>
		property array<Byte>^ ContactPoints;

		/// <summary>
		/// Size of the contact stream [bytes] including force buffer.
		/// </summary>
		property int RequiredBufferSize;

		/// <summary>
		/// Number of contact points stored in the contact stream.
		/// </summary>
		property int ContactCount;

		/// <summary>
		/// Additional information on the contact report pair.
		/// </summary>
		property ContactPairFlag Flags;
	};
}