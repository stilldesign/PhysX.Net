#include "StdAfx.h"
#include "OperationFailedException.h"

OperationFailedException::OperationFailedException()
{

}
OperationFailedException::OperationFailedException(String^ messageFormat, ... array<Object^>^ args)
	: Exception(String::Format(messageFormat, args))
{

}