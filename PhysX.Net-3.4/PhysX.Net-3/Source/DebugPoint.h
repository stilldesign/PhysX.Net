#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class DebugPoint
	{
		public:
			DebugPoint(Vector3 point, int color);

			property Vector3 Point;
			property int Color;
	};
};