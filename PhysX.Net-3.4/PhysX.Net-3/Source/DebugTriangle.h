#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class DebugTriangle
	{
		public:
			DebugTriangle(Vector3 point0, int color0, Vector3 point1, int color1, Vector3 point2, int color2);

			property Vector3 Point0;
			property int Color0;

			property Vector3 Point1;
			property int Color1;

			property Vector3 Point2;
			property int Color2;
	};
};