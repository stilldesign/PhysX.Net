#pragma once

#include "ActorEnum.h"
#include "CharacterEnum.h"

namespace PhysX
{
	/// <summary>
	/// Actor Descriptor.
	/// This structure is used to save and load the state of Actor objects.
	/// </summary>
	public ref class ActorDesc
	{
		private:
			ActorType _type;

		public:
			ActorDesc(ActorType type);

		internal:
			void PopulateManaged(PxActorDesc& desc);
			void PopulateUnmanaged(PxActorDesc& desc);

			//

		public:
			property ActorType Type
			{
				ActorType get();
			}

			property Byte DominanceGroup;

			property ActorFlag Flags;

			property Byte OwnerClient;

			property ClientBehaviorBit ClientBehaviorBits;

			property Object^ UserData;

			property String^ Name;
	};
};