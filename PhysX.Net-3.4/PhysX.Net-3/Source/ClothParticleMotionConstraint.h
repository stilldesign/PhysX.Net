#pragma once

using namespace System::Runtime::InteropServices;

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothParticleMotionConstraint
	{
	public:
		property Vector3 Position;
		property float Radius;
	};
};