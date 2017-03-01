#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class DebugLine
	{
		public:
			DebugLine(Vector3 point0, int color0, Vector3 point1, int color1);

			property Vector3 Point0;
			property int Color0;

			property Vector3 Point1;
			property int Color1;
	};
};