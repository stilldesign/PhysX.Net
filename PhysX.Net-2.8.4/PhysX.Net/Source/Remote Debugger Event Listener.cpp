#include "StdAfx.h"

#include "Remote Debugger Event Listener.h"

#include <NxRemoteDebugger.h> 

using namespace StillDesign::PhysX;

RemoteDebuggerEventListener::RemoteDebuggerEventListener()
{
	
}
RemoteDebuggerEventListener::~RemoteDebuggerEventListener()
{
	this->!RemoteDebuggerEventListener();
}
RemoteDebuggerEventListener::!RemoteDebuggerEventListener()
{
	
}

NxRemoteDebuggerEventListener* RemoteDebuggerEventListener::UnmanagedPointer::get()
{
	return _listener;
}