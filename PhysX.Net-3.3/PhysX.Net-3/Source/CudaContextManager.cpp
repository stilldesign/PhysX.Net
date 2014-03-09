#include "StdAfx.h"
#include "CudaContextManager.h"
#include "Foundation.h"
#include "GpuDispatcher.h"

CudaContextManager::CudaContextManager(Foundation^ foundation)
{
	ThrowIfNullOrDisposed(foundation, "foundation");

	// TODO: Take a CudaContextManagerDesc^ ctor arg
	PxCudaContextManagerDesc cudaContextManagerDesc;

	auto native = PxCreateCudaContextManager(*foundation->UnmanagedPointer, cudaContextManagerDesc, NULL);

	if (native == NULL)
		throw gcnew OperationFailedException("Failed to create PxCudaContextManager instance");

	_cudaContextManager = native;

	_gpuDispatcher = gcnew PhysX::GpuDispatcher(native->getGpuDispatcher(), this);

	ObjectTable::Add((intptr_t)native, this, foundation);
}
CudaContextManager::~CudaContextManager()
{
	this->!CudaContextManager();
}
CudaContextManager::!CudaContextManager()
{
	OnDisposing(this, nullptr);

	if (Disposed)
		return;

	_cudaContextManager->release();
	_cudaContextManager = NULL;

	OnDisposed(this, nullptr);
}

bool CudaContextManager::Disposed::get()
{
	return _cudaContextManager == NULL;
}

void CudaContextManager::AcquireContext()
{
	_cudaContextManager->acquireContext();
}

void CudaContextManager::ReleaseContext()
{
	_cudaContextManager->releaseContext();
}

//PxCudaMemoryManager *  getMemoryManager() = 0

PhysX::GpuDispatcher^ CudaContextManager::GpuDispatcher::get()
{
	return _gpuDispatcher;
}

bool CudaContextManager::ContextIsValid::get()
{
	return _cudaContextManager->contextIsValid();
}

bool CudaContextManager::SupportsArchSM10::get()
{
	return _cudaContextManager->supportsArchSM10();
}

bool CudaContextManager::SupportsArchSM11::get()
{
	return _cudaContextManager->supportsArchSM11();
}

bool CudaContextManager::SupportsArchSM12::get()
{
	return _cudaContextManager->supportsArchSM12();
}

bool CudaContextManager::SupportsArchSM13::get()
{
	return _cudaContextManager->supportsArchSM13();
}

bool CudaContextManager::SupportsArchSM20::get()
{
	return _cudaContextManager->supportsArchSM20();
}

bool CudaContextManager::SupportsArchSM30::get()
{
	return _cudaContextManager->supportsArchSM30();
}

bool CudaContextManager::SupportsArchSM35::get()
{
	return _cudaContextManager->supportsArchSM35();
}

bool CudaContextManager::IsIntegrated::get()
{
	return _cudaContextManager->isIntegrated();
}

bool CudaContextManager::CanMapHostMemory::get()
{
	return _cudaContextManager->canMapHostMemory();
}

int CudaContextManager::DriverVersion::get()
{
	return _cudaContextManager->getDriverVersion();
}

long CudaContextManager::DeviceTotalMemoryBytes::get()
{
	return _cudaContextManager->getDriverVersion();
}

int CudaContextManager::MultiprocessorCount::get()
{
	return _cudaContextManager->getMultiprocessorCount();
}

int CudaContextManager::ClockRate::get()
{
	return _cudaContextManager->getClockRate();
}

int CudaContextManager::SharedMemoryPerBlock::get()
{
	return _cudaContextManager->getSharedMemPerBlock();
}

String^ CudaContextManager::DeviceName::get()
{
	return Util::ToManagedString(_cudaContextManager->getDeviceName());
}

CudaInteropMode CudaContextManager::InteropMode::get()
{
	return ToManagedEnum(CudaInteropMode, _cudaContextManager->getInteropMode());
}

bool CudaContextManager::UsingConcurrentStreams::get()
{
	return _cudaContextManager->getUsingConcurrentStreams();
}
void CudaContextManager::UsingConcurrentStreams::set(bool value)
{
	return _cudaContextManager->setUsingConcurrentStreams(value);
}

//virtual bool  registerResourceInCudaGL(CUgraphicsResource &resource, PxU32 buffer) = 0
//Register a rendering resource with CUDA.

//virtual bool  registerResourceInCudaD3D(CUgraphicsResource &resource, void *resourcePointer) = 0
//Register a rendering resource with CUDA.

//virtual bool  unregisterResourceInCuda(CUgraphicsResource resource) = 0
//Unregister a rendering resource with CUDA.

int CudaContextManager::UsingDedicatedPhysXGPU::get()
{
	return _cudaContextManager->usingDedicatedPhysXGPU();
}