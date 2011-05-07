#pragma once

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::ComponentModel;

namespace PhysX
{
	private ref class Util
	{
		internal:
			/// <summary>A very specific method to copy an unmanaged struct containing floats to a managed version.</summary>
			generic<typename T> where T : value class
			static T CloneFloatStruct( int numOfFloats, void* p_unmanaged );
	};
};