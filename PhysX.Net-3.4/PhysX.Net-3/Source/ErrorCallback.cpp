#include "StdAfx.h"
#include "ErrorCallback.h"

ErrorCallback::ErrorCallback()
{
	_errorCallback = new InternalErrorCallback(this);
}
ErrorCallback::~ErrorCallback()
{
	this->!ErrorCallback();
}
ErrorCallback::!ErrorCallback()
{
	SAFE_DELETE(_errorCallback);
}

InternalErrorCallback* ErrorCallback::UnmanagedPointer::get()
{
	return _errorCallback;
}

//

InternalErrorCallback::InternalErrorCallback(ErrorCallback^ errorCallback)
{
	ThrowIfNull(errorCallback, "errorCallback");

	_errorCallback = errorCallback;
}

void InternalErrorCallback::reportError(PxErrorCode::Enum code, const char *message, const char *file, int line)
{
	_errorCallback->ReportError(ToManagedEnum(ErrorCode, code), Util::ToManagedString(message), Util::ToManagedString(file), line );
}

//

ConsoleErrorCallback::ConsoleErrorCallback()
{

}

void ConsoleErrorCallback::ReportError(ErrorCode errorCode, String^ message, String^ file, int lineNumber)
{
	Console::WriteLine(message);
}

//

DefaultErrorCallback::DefaultErrorCallback()
{

}

void DefaultErrorCallback::ReportError(ErrorCode errorCode, String^ message, String^ file, int lineNumber)
{
	
}