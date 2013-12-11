#pragma once

//#include <PvdConnectionManager.h>
#include "VisualDebuggerEnum.h"

using namespace physx::debugger::comm;

namespace PhysX
{
	ref class Physics;

	namespace VisualDebugger
	{
		public ref class ConnectionManager : IDisposable
		{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PvdConnectionManager* _manager;
			PhysX::Physics^ _physics;

		public:
			ConnectionManager(PvdConnectionManager* manager, PhysX::Physics^ owner);
			~ConnectionManager();
		protected:
			!ConnectionManager();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			bool IsConnected();

			void Disconnect();

			//void Connect(NetworkStream^ inStream, NetworkStream^ outStream, ConnectionFlagsType connectionType, bool doubleBuffered);
			void Connect(String^ host, [Optional] Nullable<int> port, [Optional] Nullable<TimeSpan> timeout, [Optional] Nullable<VisualDebuggerConnectionFlag> connectionType, [Optional] Nullable<bool> doubleBuffered);

			property PhysX::Physics^ Physics
			{
				PhysX::Physics^ get();
			}

		internal:
			property PvdConnectionManager* UnmanagedPointer
			{
				PvdConnectionManager* get();
			}
		};
	};
};