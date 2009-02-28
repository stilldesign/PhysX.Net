#include "StdAfx.h"

#include "Error Report.h"
#include "Functions.h"

using namespace StillDesign::PhysX::Utilities;

ErrorReport::ErrorReport()
{
	_errorReport = new InternalErrorReport( this );
}
ErrorReport::~ErrorReport()
{
	this->!ErrorReport();	
}
ErrorReport::!ErrorReport()
{
	SAFE_DELETE( _errorReport );
}

NXU_errorReport* ErrorReport::UnmanagedPointer::get()
{
	return _errorReport;
}

//

InternalErrorReport::InternalErrorReport( gcroot<ErrorReport^> errorReport )
{
	_errorReport = errorReport;
}
InternalErrorReport::~InternalErrorReport()
{
	_errorReport = nullptr;
}
void InternalErrorReport::NXU_errorMessage( bool isError, const char *str )
{
	String^ message = Functions::UnmanagedToManagedString( str );
	
	_errorReport->ErrorMessage( isError, message );
}