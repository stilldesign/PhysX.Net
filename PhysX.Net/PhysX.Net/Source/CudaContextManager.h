#pragma once

#include "CudaEnum.h"

namespace PhysX
{
	ref class Foundation;

	public ref class CudaContextManager : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxCudaContextManager* _cudaContextManager;

	public:
		CudaContextManager(Foundation^ foundation);
		~CudaContextManager();
	protected:
		!CudaContextManager();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		void AcquireContext();

		void ReleaseContext();

		//PxCudaMemoryManager *  getMemoryManager() = 0

		property bool ContextIsValid
		{
			bool get();
		}

		property bool SupportsArchSM10
		{
			bool get();
		}

		property bool SupportsArchSM11
		{
			bool get();
		}

		property bool SupportsArchSM12
		{
			bool get();
		}

		property bool SupportsArchSM13
		{
			bool get();
		}

		property bool SupportsArchSM20
		{
			bool get();
		}

		property bool SupportsArchSM30
		{
			bool get();
		}

		property bool SupportsArchSM35
		{
			bool get();
		}

		property bool IsIntegrated
		{
			bool get();
		}

		property bool CanMapHostMemory
		{
			bool get();
		}

		property int DriverVersion
		{
			int get();
		}

		property long DeviceTotalMemoryBytes
		{
			long get();
		}

		property int MultiprocessorCount
		{
			int get();
		}

		property int ClockRate
		{
			int get();
		}

		property int SharedMemoryPerBlock
		{
			int get();
		}

		property String^ DeviceName
		{
			String^ get();
		}

		property CudaInteropMode InteropMode
		{
			CudaInteropMode get();
		}

		property bool UsingConcurrentStreams
		{
			bool get();
			void set(bool value);
		}

		//virtual bool  registerResourceInCudaGL(CUgraphicsResource &resource, PxU32 buffer) = 0
		//Register a rendering resource with CUDA.

		//virtual bool  registerResourceInCudaD3D(CUgraphicsResource &resource, void *resourcePointer) = 0
		//Register a rendering resource with CUDA.

		//virtual bool  unregisterResourceInCuda(CUgraphicsResource resource) = 0
		//Unregister a rendering resource with CUDA.

		property Nullable<bool> UsingDedicatedGPU
		{
			Nullable<bool> get();
		}

		property PxCudaContextManager* UnmanagedPointer
		{
			PxCudaContextManager* get();
		}
	};
}