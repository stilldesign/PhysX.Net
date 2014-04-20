#include "StdAfx.h"

#include "Constant Contact Stream.h"

using namespace StillDesign::PhysX;

ConstantContactStream::ConstantContactStream( NxConstContactStream* stream )
{
	_stream = stream;
}

NxConstContactStream* ConstantContactStream::UnmanagedPointer::get()
{
	return _stream;
}