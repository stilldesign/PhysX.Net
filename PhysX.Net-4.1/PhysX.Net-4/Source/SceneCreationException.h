#pragma once

#include "PhysXException.h"

using namespace System;

namespace PhysX
{
	public ref class SceneCreationException : public PhysXException
	{
		internal:
			SceneCreationException(String^ message)
				: PhysXException(message)
			{
					
			}
				
			SceneCreationException(String^ format, ... array<Object^>^ args)
				: PhysXException(String::Format(format, args))
			{
					
			}
	};
}