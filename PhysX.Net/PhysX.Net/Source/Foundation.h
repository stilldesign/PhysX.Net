#pragma once

namespace PhysX
{
	ref class Physics;
	ref class ErrorCallback;

	public ref class Foundation : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxFoundation* _foundation;
		static bool _initalized;

		PxAllocatorCallback* _allocator;

		PhysX::ErrorCallback^ _errorCallback;

		static System::Version^ _version;

	private:
		static Foundation();
	public:
		Foundation([Optional] PhysX::ErrorCallback^ errorCallback);
		~Foundation();
	protected:
		!Foundation();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

	internal:
		PxAllocatorCallback* GetAllocator();

	public:
		property bool Initalized
		{
			static bool get();
		}

		property PhysX::ErrorCallback^ ErrorCallback
		{
			PhysX::ErrorCallback^ get();
		}

		/// <summary>
		/// Gets the PhysX version.
		/// </summary>
		property System::Version^ Version
		{
			static System::Version^ get();
		}

	internal:
		property PxFoundation* UnmanagedPointer
		{
			PxFoundation* get();
		}
	};
};