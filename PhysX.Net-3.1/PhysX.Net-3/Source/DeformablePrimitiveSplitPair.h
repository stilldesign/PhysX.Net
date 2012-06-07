#pragma once

namespace PhysX
{
	[StructLayout(LayoutKind::Sequential)]
	public value class DeformablePrimitiveSplitPair
	{
		public:
			property int PrimitiveIndex0;
			property int PrimitiveIndex1;

			property Byte SplitSite0;
			property Byte SplitSite1;
	};
};