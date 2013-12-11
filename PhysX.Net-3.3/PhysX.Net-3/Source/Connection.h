#pragma once

//#include <PxVisualDebuggerExt.h>
//#include <PvdConnection.h>

namespace PhysX
{
	ref class Physics;

	namespace VisualDebugger
	{
		public ref class Connection : IDisposable
		{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			physx::debugger::comm::PvdConnection* _connection;

		internal:
			Connection(physx::debugger::comm::PvdConnection* connection, PhysX::Physics^ owner);
		public:
			~Connection();
		protected:
			!Connection();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

		internal:
			property physx::debugger::comm::PvdConnection* UnmanagedPointer
			{
				physx::debugger::comm::PvdConnection* get();
			}
		};
	};
};