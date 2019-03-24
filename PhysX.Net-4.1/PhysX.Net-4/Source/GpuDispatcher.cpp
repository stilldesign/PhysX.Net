#include "StdAfx.h"
#include "CudaContextManager.h"
#include "GpuDispatcher.h"

GpuDispatcher::GpuDispatcher(PxGpuDispatcher* gpuDispatcher, PhysX::CudaContextManager^ owner)
{
	ThrowIfNull(gpuDispatcher, "gpuDispatcher");

	_gpuDispatcher = gpuDispatcher;

	ObjectTable::Instance->Add((intptr_t)gpuDispatcher, this, owner);
}
GpuDispatcher::~GpuDispatcher()
{
	this->!GpuDispatcher();
}
GpuDispatcher::!GpuDispatcher()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_gpuDispatcher = NULL;

	OnDisposed(this, nullptr);
}

bool GpuDispatcher::Disposed::get()
{
	return _gpuDispatcher == NULL;
}

void GpuDispatcher::StartSimulation()
{
	_gpuDispatcher->startSimulation();
}

void GpuDispatcher::StartGroup()
{
	_gpuDispatcher->startGroup();
}

//void SubmitTask()

void GpuDispatcher::FinishGroup()
{
	_gpuDispatcher->finishGroup();
}

//void AddCompletionPrereq()

void GpuDispatcher::StopSimulation()
{
	_gpuDispatcher->stopSimulation();
}

void GpuDispatcher::ForceFailureMode()
{
	_gpuDispatcher->forceFailureMode();
}

//void *  getCurrentProfileBuffer();

int GpuDispatcher::RegisterKernelNames(array<String^>^ kernelNames)
{
	throw gcnew NotImplementedException();
	//const char* c = new char[kernelNames->Length]

	//_gpuDispatcher->registerKernelNames();
}

//void LaunchCopyKernel(PxGpuCopyDesc *desc, PxU32 count, CUstream stream);

//virtual PxBaseTask &  getPreLaunchTask() = 0

//virtual void  addPreLaunchDependent(PxBaseTask &dependent) = 0

//virtual PxBaseTask &  getPostLaunchTask() = 0

//virtual void  addPostLaunchDependent(PxBaseTask &dependent) = 0

bool GpuDispatcher::FailureDetected::get()
{
	return _gpuDispatcher->failureDetected();
}

PhysX::CudaContextManager^ GpuDispatcher::CudaContextManager::get()
{
	PxCudaContextManager* ccm = _gpuDispatcher->getCudaContextManager();

	return ObjectTable::Instance->GetObject<PhysX::CudaContextManager^>((intptr_t)ccm);
}

PxGpuDispatcher* GpuDispatcher::UnmanagedPointer::get()
{
	return _gpuDispatcher;
}