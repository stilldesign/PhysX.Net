#pragma once

#include "PhysX Exception.h"

namespace StillDesign
{
	namespace PhysX
	{
		public ref class PhysXInitializationException : public PhysXException
		{
			private:
				CoreCreationError _errorCode;
				
			public:
				property CoreCreationError ErrorCode
				{
					CoreCreationError get()
					{
						return _errorCode; 
					}
				}
				
			internal:
				PhysXInitializationException( CoreCreationError errorCode ) : PhysXException( "PhysX failed to initialize" )
				{
					_errorCode = errorCode;
				}
		};
	}
}