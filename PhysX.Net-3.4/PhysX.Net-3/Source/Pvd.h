#pragma once

#include "PvdEnum.h"

using namespace physx::pvdsdk;

namespace PhysX
{
	ref class Foundation;

	namespace VisualDebugger
	{
		public ref class Pvd : IDisposable
		{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxPvd* _pvd;

		public:
			Pvd(Foundation^ foundation);
			~Pvd();
		protected:
			!Pvd();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			void Connect(String^ host, [Optional] Nullable<int> port, [Optional] Nullable<TimeSpan> timeout, [Optional] Nullable<InstrumentationFlag> connectionType);
			void Disconnect();

			bool IsConnected(bool useCachedStatus);

		internal:
			property PxPvd* UnmanagedPointer
			{
				PxPvd* get();
			}
		};
	};
};