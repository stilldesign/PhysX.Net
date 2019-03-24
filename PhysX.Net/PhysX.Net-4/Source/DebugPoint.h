#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Explicit)]
	public value class DebugPoint
	{
		public:
			[FieldOffset(0)]	Vector3 Point;
			[FieldOffset(12)]	int Color;
	};
};