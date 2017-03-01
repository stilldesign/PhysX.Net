#pragma once

#include "PhysXException.h"

namespace PhysX
{
	public ref class VehicleSDKNotInitializedException : public PhysXException
	{
	internal:
		VehicleSDKNotInitializedException(String^ message)
			: PhysXException(message)
		{

		}

		VehicleSDKNotInitializedException(String^ format, ... array<Object^>^ args)
			: PhysXException(String::Format(format, args))
		{

		}
	};
}