#pragma once

#include "PhysicsEnum.h"

namespace PhysX
{
	/// <summary>
	/// Parent class for bulk data that is shared between the SDK and the application.
	/// </summary>
	public ref class LockedData abstract : IDisposable
	{
		public:
			/// <summary>Raised before any disposing is performed.</summary>
			virtual event EventHandler^ OnDisposing;
			/// <summary>Raised once all disposing is performed.</summary>
			virtual event EventHandler^ OnDisposed;

		private:
			PxLockedData* _data;

		protected:
			LockedData(PxLockedData* data);
		public:
			~LockedData();
		protected:
			!LockedData();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Unlocks the bulk data.
			/// </summary>
			virtual void Unlock();

			/// <summary>
			/// Any combination of DataAccessFlag.Readable and DataAccessFlag.Writable.
			/// </summary>
			property PhysX::DataAccessFlag DataAccessFlag
			{
				virtual PhysX::DataAccessFlag get();
			}

		internal:
			property PxLockedData* UnmanagedPointer
			{
				PxLockedData* get();
			}
	};
};