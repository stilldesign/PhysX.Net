#pragma once

#include "NXU_Helper.h" 

class NxuPhysicsCollection;

namespace StillDesign
{
	namespace PhysX
	{
		namespace Utilities
		{
			class InternalErrorReport;
			
			public ref class ErrorReport abstract
			{
				private:
					InternalErrorReport* _errorReport;
				
				public:
					ErrorReport();
					~ErrorReport();
				protected:
					!ErrorReport();
					
				public:
					virtual void ErrorMessage( bool isError, String^ message ) abstract;
					
				internal:
					property NXU_errorReport* UnmanagedPointer
					{
						NXU_errorReport* get();
					}
			};
			
			class InternalErrorReport : public NXU_errorReport
			{
				private:
					gcroot<ErrorReport^> _errorReport;
					
				public:
					InternalErrorReport( gcroot<ErrorReport^> errorReport );
					~InternalErrorReport();
					
					virtual void  NXU_errorMessage( bool isError, const char *str );
			};
		};
	};
};