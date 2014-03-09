#pragma once

namespace PhysX
{
	ref class CudaContextManager;

	public ref class GpuDispatcher : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxGpuDispatcher* _gpuDispatcher;

	internal:
		GpuDispatcher(PxGpuDispatcher* gpuDispatcher, PhysX::CudaContextManager^ owner);
	public:
		~GpuDispatcher();
	protected:
		!GpuDispatcher();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		void StartSimulation();

		void StartGroup();

		//void SubmitTask()

		void FinishGroup();

		//void AddCompletionPrereq()

		void StopSimulation();

		void ForceFailureMode();

		//void *  getCurrentProfileBuffer();

		int RegisterKernelNames(array<String^>^ kernelNames);

		//void LaunchCopyKernel(PxGpuCopyDesc *desc, PxU32 count, CUstream stream);

		//virtual PxBaseTask &  getPreLaunchTask() = 0

		//virtual void  addPreLaunchDependent(PxBaseTask &dependent) = 0

		//virtual PxBaseTask &  getPostLaunchTask() = 0

		//virtual void  addPostLaunchDependent(PxBaseTask &dependent) = 0

		property bool FailureDetected
		{
			bool get();
		}

		property PhysX::CudaContextManager^ CudaContextManager
		{
			PhysX::CudaContextManager^ get();
		}

	internal:
		property PxGpuDispatcher* UnmanagedPointer
		{
			PxGpuDispatcher* get();
		}
	};
};