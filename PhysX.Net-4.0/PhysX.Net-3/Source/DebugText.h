#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class DebugText
	{
		public:
			DebugText(Vector3 position, float size, int color, System::String^ string);

			property Vector3 Position;
			property float Size;
			property int Color;
			property System::String^ String;
	};
};