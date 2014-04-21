#pragma once

#include "Remote Debugger Values.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class RemoteDebuggerEventListener;
		ref class Foundation;
		
		public ref class RemoteDebugger
		{
			public:
				const static int DefaultPort = 5425;
				
			private:
				NxRemoteDebugger* _remoteDebugger;
			
			internal:
				RemoteDebugger( NxRemoteDebugger* remoteDebugger );
			public:
				~RemoteDebugger();
			protected:
				!RemoteDebugger();
			
			public:
				void Connect( String^ host );
				void Connect( String^ host, int port, RemoteDebuggerEventMask eventMask );
				void Disconnect();
				void Flush();
				void FrameBreak();
				
				void CreateObject( IntPtr^ object, RemoteDebuggerObjectType type, String^ className, RemoteDebuggerEventMask mask );
				void RemoveObject( IntPtr^ object, RemoteDebuggerEventMask mask );
				void AddChild( IntPtr^ object, IntPtr^ child, RemoteDebuggerEventMask mask );
				void RemoveChild( IntPtr^ object, IntPtr^ child, RemoteDebuggerEventMask mask );
				
				IntPtr^ GetPickedObject();
				Vector3 GetPickPoint();
				
				void RegisterEventListener( RemoteDebuggerEventListener^ eventListener );
				void UnregisterEventListener( RemoteDebuggerEventListener^ eventListener );
				
				void WriteParameter( float parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( unsigned int parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( Vector3 parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( Plane parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( Matrix parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( Byte parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( bool parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				void WriteParameter( IntPtr^ parameter, IntPtr^ object, bool create, String^ name, RemoteDebuggerEventGroup eventGroups );
				
				property bool IsConnected
				{
					bool get();
				}
				property RemoteDebuggerEventMask Mask
				{
					RemoteDebuggerEventMask get();
					void set( RemoteDebuggerEventMask value );
				}
			
			internal:
				property NxRemoteDebugger* UnmanagedPointer
				{
					NxRemoteDebugger* get();
				}
		};
	};
};