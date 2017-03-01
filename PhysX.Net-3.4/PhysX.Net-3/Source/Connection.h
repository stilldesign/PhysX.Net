#pragma once

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
			physx::PxPvd* _connection;

		internal:
			Connection(physx::PxPvd* connection, PhysX::Physics^ owner);
		public:
			~Connection();
		protected:
			!Connection();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			void Connect();

		internal:
			property physx::PxPvd* UnmanagedPointer
			{
				physx::PxPvd* get();
			}
		};
	};
};