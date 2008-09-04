
#pragma once

#include "PhysX Exception.h"



namespace StillDesign
{
	namespace PhysX
	{

		public ref class PhysXInitializationException : public PhysXException
		{
		public:
			property CoreCreationError ErrorCode
			{
				CoreCreationError get() { return _errorCode; }
			}

		internal:
			PhysXInitializationException( CoreCreationError errorCode )
				: PhysXException( "PhysX failed to initialize" )
				, _errorCode( errorCode )
			{
			}

		private:
			CoreCreationError _errorCode;
		};

	}
}