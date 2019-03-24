#pragma once

namespace PhysX
{
	public value class ObjectTableOwnershipType
	{
	public:
		ObjectTableOwnershipType(Object^ owner, System::Type^ type)
		{
			this->Owner = owner;
			this->Type = type;
		}

		property Object^ Owner;
		property System::Type^ Type;

		// TODO: Unit test GetHashCode() and == != (vital methods)
	};
};