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
			
			internal:
				PhysXInitializationException( CoreCreationError errorCode ) 
					: PhysXException( "PhysX failed to initialize. PhysX returned the error code {0} ({1}).", (int)errorCode, errorCode )
				{
					_errorCode = errorCode;
				}
				
			public:
				property CoreCreationError ErrorCode
				{
					CoreCreationError get()
					{
						return _errorCode; 
					}
				}
		};
	}
}