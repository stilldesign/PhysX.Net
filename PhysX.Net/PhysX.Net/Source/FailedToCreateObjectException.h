#pragma once

#include "PhysXException.h"

namespace PhysX
{
	public ref class FailedToCreateObjectException : public PhysXException
	{
	internal:
		FailedToCreateObjectException(String^ message)
			: PhysXException(message)
		{

		}

		FailedToCreateObjectException(String^ format, ... array<Object^>^ args)
			: PhysXException(String::Format(format, args))
		{

		}
	};
}