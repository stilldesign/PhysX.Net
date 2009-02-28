#pragma once

#include "Remote Debugger Values.h"

class NxRemoteDebuggerEventListener;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class RemoteDebuggerEventListener abstract
		{
			private:
				NxRemoteDebuggerEventListener* _listener;
			
			protected:
				RemoteDebuggerEventListener();
			public:
				~RemoteDebuggerEventListener();
			protected:
				!RemoteDebuggerEventListener();
				
			public:
				virtual void OnConnect() = 0;
				virtual void OnDisconnect() = 0;
				virtual void BeforeMaskChange( RemoteDebuggerEventMask oldMask, RemoteDebuggerEventMask newMask ) = 0;
				virtual void AfterMaskChange( RemoteDebuggerEventMask oldMask, RemoteDebuggerEventMask newMask ) = 0;
			
			internal:
				property NxRemoteDebuggerEventListener* UnmanagedPointer
				{
					NxRemoteDebuggerEventListener* get();
				}
		};
	};
};