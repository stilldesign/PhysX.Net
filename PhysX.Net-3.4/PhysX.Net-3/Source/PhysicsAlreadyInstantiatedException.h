#pragma once

#include "PhysXException.h"

namespace PhysX
{
	public ref class PhysicsAlreadyInstantiatedException : public PhysXException
	{
	internal:
		PhysicsAlreadyInstantiatedException(String^ message)
			: PhysXException(message)
		{

		}

		PhysicsAlreadyInstantiatedException(String^ format, ... array<Object^>^ args)
			: PhysXException(String::Format(format, args))
		{

		}
	};
}