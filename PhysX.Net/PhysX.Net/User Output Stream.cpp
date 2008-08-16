#include "StdAfx.h"

#include "User Output Stream.h"
#include "Functions.h"

using namespace StillDesign::PhysX;

UserOutputStream::UserOutputStream()
{
	_userOutputStream = new InternalUserOutputStream( this );
}
UserOutputStream::~UserOutputStream()
{
	this->!UserOutputStream();
}
UserOutputStream::!UserOutputStream()
{
	SAFE_DELETE( _userOutputStream );
}

InternalUserOutputStream* UserOutputStream::UnmanagedPointer::get()
{
	return _userOutputStream;
}

//

InternalUserOutputStream::InternalUserOutputStream( UserOutputStream^ userOutputStream )
{
	_userOutputStream = userOutputStream;
}

void InternalUserOutputStream::reportError( NxErrorCode code, const char *message, const char *file, int line )
{
	_userOutputStream->ReportError( (ErrorCode)code, Functions::UnmanagedToManagedString( message ), Functions::UnmanagedToManagedString( file ), line );
}
NxAssertResponse InternalUserOutputStream::reportAssertViolation (const char *message, const char *file, int line )
{
	_userOutputStream->ReportAssertionViolation( Functions::UnmanagedToManagedString( message ), Functions::UnmanagedToManagedString( file ), line );
	
	return NX_AR_BREAKPOINT;
}
void InternalUserOutputStream::print (const char *message)
{
	_userOutputStream->Print( Functions::UnmanagedToManagedString( message ) );
}

//

ConsoleOutputStream::ConsoleOutputStream()
{
	
}

void ConsoleOutputStream::ReportError( ErrorCode errorCode, String^ message, String^ file, int lineNumber )
{
	Console::WriteLine( message );
}
AssertResponse ConsoleOutputStream::ReportAssertionViolation( String^ message, String^ file, int lineNumber )
{
	Console::WriteLine( message );
	
	return AssertResponse::Continue;
}
void ConsoleOutputStream::Print( String^ message )
{
	Console::WriteLine( message );
}