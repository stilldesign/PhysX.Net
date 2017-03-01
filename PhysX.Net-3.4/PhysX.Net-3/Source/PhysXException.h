#pragma once

namespace PhysX
{
	public ref class PhysXException : public Exception
	{
		internal:
			PhysXException(String^ message)
				: Exception(message)
			{
					
			}
				
			PhysXException(String^ format, ... array<Object^>^ args)
				: Exception(String::Format(format, args))
			{
					
			}
	};
}