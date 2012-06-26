#pragma once

namespace PhysX
{
	[Serializable]
	public ref class OperationFailedException : Exception
	{
	public:
		OperationFailedException();
		OperationFailedException(String^ messageFormat, ... array<String^>^ args);
	};
};