#include "StdAfx.h"
#include "Foundation.h"
#include "Remote Debugger.h"

#include <NxFoundationSDK.h> 

using namespace StillDesign::PhysX;

Foundation::Foundation( NxFoundationSDK* foundationSDK )
{
	Debug::Assert( foundationSDK != NULL );
	
	_foundationSDK = foundationSDK;
	
	_remoteDebugger = gcnew StillDesign::PhysX::RemoteDebugger( _foundationSDK->getRemoteDebugger() );
}
Foundation::~Foundation()
{
	_foundationSDK = NULL;
}
Foundation::!Foundation()
{
	_foundationSDK = NULL;
}

StillDesign::PhysX::RemoteDebugger^ Foundation::RemoteDebugger::get()
{
	return _remoteDebugger;
}

NxFoundationSDK* Foundation::UnmanagedPointer::get()
{
	return _foundationSDK;
}