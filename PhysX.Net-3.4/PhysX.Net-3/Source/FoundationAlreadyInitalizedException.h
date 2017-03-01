#pragma once

#include "PhysXException.h"

namespace PhysX
{
	public ref class FoundationAlreadyInitalizedException : public PhysXException
	{
	internal:
		FoundationAlreadyInitalizedException(String^ message)
			: PhysXException(message)
		{

		}

		FoundationAlreadyInitalizedException(String^ format, ... array<Object^>^ args)
			: PhysXException(String::Format(format, args))
		{

		}
	};
}