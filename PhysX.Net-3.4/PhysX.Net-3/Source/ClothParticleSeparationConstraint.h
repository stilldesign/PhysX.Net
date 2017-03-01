#pragma once

using namespace System::Runtime::InteropServices;

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothParticleSeparationConstraint
	{
	public:
		property Vector3 Position;
		property float Radius;
	};
};