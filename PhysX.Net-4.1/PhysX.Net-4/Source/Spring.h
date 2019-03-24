#pragma once


using namespace System::Runtime::InteropServices;

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class Spring
	{
	internal:
		static PxSpring ToUnmanaged(Spring managed);
		static Spring ToManaged(PxSpring unmanaged);

	public:
		Spring(float stiffness, float damping);

		property float Stiffness;
		property float Damping;
	};
}