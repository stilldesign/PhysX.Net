#pragma once

#include "PhysicsEnum.h"

namespace PhysX
{
	ref class RigidActor;

	public ref class ContactPairHeader
	{
	internal:
		static ContactPairHeader^ ToManaged(PxContactPairHeader unmanaged);

	public:
		/// <summary>
		/// 
		/// </summary>
		property RigidActor^ Actor0;

		/// <summary>
		/// 
		/// </summary>
		property RigidActor^ Actor1;

		/// <summary>
		/// 
		/// </summary>
		property array<Byte>^ ExtraData;

		/// <summary>
		/// 
		/// </summary>
		property ContactPairHeaderFlag Flags;
	};
}