#pragma once

using namespace System;

namespace PhysX
{
	public ref class ShapeCreationException : public Exception
	{
		internal:
			ShapeCreationException(String^ message)
				: Exception(message)
			{
					
			}
				
			ShapeCreationException(String^ format, ... array<Object^>^ args)
				: Exception(String::Format(format, args))
			{
					
			}
	};
}