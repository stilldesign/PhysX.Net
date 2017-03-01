#pragma once

using namespace System::Runtime::InteropServices;

#include "ClothEnum.h"

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class ClothFabricPhase
	{
	public:
		property ClothFabricPhaseType PhaseType;
		property int SetIndex;
	};
};