#pragma once

namespace PhysX
{
	public enum class CudaInteropMode
	{
		None = PxCudaInteropMode::NO_INTEROP,
		D3D10 = PxCudaInteropMode::D3D10_INTEROP,
		D3D11 = PxCudaInteropMode::D3D11_INTEROP,
		OpenGL = PxCudaInteropMode::OGL_INTEROP
	};
}