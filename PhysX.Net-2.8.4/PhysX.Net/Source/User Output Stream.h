#pragma once

#include "Enums.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		class InternalUserOutputStream;
		
		public ref class UserOutputStream abstract
		{
			private:
				InternalUserOutputStream* _userOutputStream;
			
			protected:
				UserOutputStream();
			public:
				~UserOutputStream();
			protected:
				!UserOutputStream();
			
			public:
				virtual void ReportError( ErrorCode errorCode, String^ message, String^ file, int lineNumber ) abstract;
				virtual AssertResponse ReportAssertionViolation( String^ message, String^ file, int lineNumber ) abstract;
				virtual void Print( String^ message ) abstract;
			
			internal:
				property InternalUserOutputStream* UnmanagedPointer
				{
					InternalUserOutputStream* get();
				}
		};
		
		class InternalUserOutputStream : public NxUserOutputStream
		{
			private:
				gcroot< UserOutputStream^ > _userOutputStream;
			
			public:
				InternalUserOutputStream( UserOutputStream^ userOutputStream );
				
				virtual void reportError( NxErrorCode code, const char *message, const char *file, int line );
				virtual NxAssertResponse reportAssertViolation( const char *message, const char *file, int line );
				virtual void  print ( const char *message );
		};
		
		public ref class ConsoleOutputStream sealed : UserOutputStream
		{
			public:
				ConsoleOutputStream();
				
				virtual void ReportError( ErrorCode errorCode, String^ message, String^ file, int lineNumber ) override;
				virtual AssertResponse ReportAssertionViolation( String^ message, String^ file, int lineNumber ) override;
				virtual void Print( String^ message ) override;
		};
	};
};