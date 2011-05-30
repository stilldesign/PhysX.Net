#pragma once

namespace PhysX
{
	ref class Physics;

	public ref class Foundation : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxFoundation* _foundation;

		internal:
			Foundation(PxFoundation* foundation, PhysX::Physics^ owner);
		public:
			~Foundation();
		protected:
			!Foundation();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

		internal:
			property PxFoundation* UnmanagedPointer
			{
				PxFoundation* get();
			}
	};
};