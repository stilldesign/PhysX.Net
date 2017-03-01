#pragma once

//#include <PvdConnectionManager.h>
#include "VisualDebuggerEnum.h"

using namespace physx::pvdsdk;

namespace PhysX
{
	ref class Foundation;

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
			PxPvd* _manager;

		public:
			ConnectionManager();
			~ConnectionManager();
		protected:
			!ConnectionManager();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			property bool IsConnected
			{
				bool get();
			}

			void Disconnect();

			void Connect(String^ host, [Optional] Nullable<int> port, [Optional] Nullable<TimeSpan> timeout, [Optional] Nullable<InstrumentationFlag> connectionType);

			static ConnectionManager^ GetInstance(Foundation^ foundation);

		internal:
			property PxPvd* UnmanagedPointer
			{
				PxPvd* get();
			}
		};
	};
};