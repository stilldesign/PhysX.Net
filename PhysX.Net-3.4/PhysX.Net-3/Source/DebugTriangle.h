#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Explicit)]
	public value class DebugTriangle
	{
		public:
			[FieldOffset(0)]	Vector3 Point0;
			[FieldOffset(12)]	int Color0;

			[FieldOffset(16)]	Vector3 Point1;
			[FieldOffset(28)]	int Color1;

			[FieldOffset(32)]	Vector3 Point2;
			[FieldOffset(44)]	int Color2;
	};
};