#include "StdAfx.h"

#include "Remote Debugger.h"
#include "Functions.h"
#include "Math.h"
#include "Remote Debugger Event Listener.h"
#include "Foundation.h"

#include <NxRemoteDebugger.h>

using namespace StillDesign::PhysX;

RemoteDebugger::RemoteDebugger( NxRemoteDebugger* remoteDebugger )
{
	Debug::Assert( remoteDebugger != NULL );
	
	_remoteDebugger = remoteDebugger;
}
RemoteDebugger::~RemoteDebugger()
{
	this->!RemoteDebugger();
}
RemoteDebugger::!RemoteDebugger()
{
	// Remote Debugger is to be Released by the Foundation SDK
	_remoteDebugger = NULL;
}

void RemoteDebugger::Connect( String^ host )
{
	_remoteDebugger->connect( Functions::ManagedToUnmanagedString( host ) );
}
void RemoteDebugger::Connect( String^ host, int port, RemoteDebuggerEventMask eventMask )
{
	_remoteDebugger->connect( Functions::ManagedToUnmanagedString( host ), port, (unsigned int)eventMask );
}
void RemoteDebugger::Disconnect()
{
	_remoteDebugger->disconnect();
}
void RemoteDebugger::Flush()
{
	_remoteDebugger->flush();
}
void RemoteDebugger::FrameBreak()
{
	_remoteDebugger->frameBreak();
}

void RemoteDebugger::CreateObject( IntPtr^ object, RemoteDebuggerObjectType type, String^ className, RemoteDebuggerEventMask mask )
{
	_remoteDebugger->createObject( object->ToPointer(), (NxRemoteDebuggerObjectType)type, Functions::ManagedToUnmanagedString( className ), (unsigned int)mask );
}
void RemoteDebugger::RemoveObject( IntPtr^ object, RemoteDebuggerEventMask mask )
{
	_remoteDebugger->removeObject( object->ToPointer(), (unsigned int)mask );
}
void RemoteDebugger::AddChild( IntPtr^ object, IntPtr^ child, RemoteDebuggerEventMask mask )
{
	_remoteDebugger->addChild( object->ToPointer(), child->ToPointer(), (unsigned int)mask );
}
void RemoteDebugger::RemoveChild( IntPtr^ object, IntPtr^ child, RemoteDebuggerEventMask mask )
{
	_remoteDebugger->removeChild( object->ToPointer(), child->ToPointer(), (unsigned int)mask );
}

IntPtr^ RemoteDebugger::GetPickedObject()
{
	return gcnew IntPtr( _remoteDebugger->getPickedObject() );
}
Vector3 RemoteDebugger::GetPickPoint()
{
	return Math::NxVec3ToVector3( _remoteDebugger->getPickPoint() );
}

void RemoteDebugger::RegisterEventListener( RemoteDebuggerEventListener^ eventListener )
{
	_remoteDebugger->registerEventListener( eventListener->UnmanagedPointer );
}
void RemoteDebugger::UnregisterEventListener( RemoteDebuggerEventListener^ eventListener )
{
	_remoteDebugger->unregisterEventListener( eventListener->UnmanagedPointer );
}

void RemoteDebugger::WriteParameter( float parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( parameter, object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( unsigned int parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( parameter, object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( Vector3 parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( Math::Vector3ToNxVec3( parameter ), object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( Plane parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( Math::PlaneToNxPlane( parameter ), object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( Matrix parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( Math::MatrixToMat34( parameter ), object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( Byte parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( &((NxU8)parameter), object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( bool parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( parameter, object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}
void RemoteDebugger::WriteParameter( IntPtr^ parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups )
{
	_remoteDebugger->writeParameter( parameter->ToPointer(), object->ToPointer(), create, Functions::ManagedToUnmanagedString( name ), (unsigned int)eventGroups );
}

bool RemoteDebugger::IsConnected::get()
{
	return _remoteDebugger->isConnected();
}
RemoteDebuggerEventMask RemoteDebugger::Mask::get()
{
	return (RemoteDebuggerEventMask)_remoteDebugger->getMask();
}
void RemoteDebugger::Mask::set( RemoteDebuggerEventMask value )
{
	_remoteDebugger->setMask( (unsigned int)value );
}

NxRemoteDebugger* RemoteDebugger::UnmanagedPointer::get()
{
	return _remoteDebugger;
}