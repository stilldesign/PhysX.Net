#pragma once

#include <PvdConnection.h>

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
				PVD::PvdConnection* _connection;

			internal:
				Connection(PVD::PvdConnection* connection, PhysX::Physics^ owner);
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
				property PVD::PvdConnection* UnmanagedPointer
				{
					PVD::PvdConnection* get();
				}
		};
	};
};