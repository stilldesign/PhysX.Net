#include "StdAfx.h"

#include "Descriptor Validity.h"

using namespace StillDesign::PhysX;

DescriptorValidity::DescriptorValidity( bool isValid, String^ errorMessage )
{
	_isValid = isValid;
	_errorCode = 0;
	_errorMessage = errorMessage;
}
DescriptorValidity::DescriptorValidity( bool isValid, int errorCode, String^ errorMessage )
{
	_isValid = isValid;
	_errorCode = errorCode;
	_errorMessage = errorMessage;
}

DescriptorValidity^ DescriptorValidity::Invalid( String^ message )
{
	return gcnew DescriptorValidity( false, message );
}

bool DescriptorValidity::operator ==( DescriptorValidity^ descriptor, bool isValid )
{
	return descriptor->IsValid == isValid;
}
bool DescriptorValidity::operator !=( DescriptorValidity^ descriptor, bool isValid )
{
	return descriptor->IsValid != isValid;
}
DescriptorValidity::operator DescriptorValidity^( bool valid )
{
	return gcnew DescriptorValidity( valid, String::Empty );
}
DescriptorValidity::operator bool( DescriptorValidity^ v )
{
	return v->IsValid;
}

bool DescriptorValidity::IsValid::get()
{
	return _isValid;
}
void DescriptorValidity::IsValid::set( bool value )
{
	_isValid = value;
}


int DescriptorValidity::ErrorCode::get()
{
	return _errorCode;
}
void DescriptorValidity::ErrorCode::set( int value )
{
	_errorCode = value;
}

String^ DescriptorValidity::ErrorMessage::get()
{
	return _errorMessage;
}
void DescriptorValidity::ErrorMessage::set( String^ value )
{
	_errorMessage = value;
}