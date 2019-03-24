#pragma once

namespace PhysX
{
	public ref class ConstraintConnector
	{
	public:
		void PrepareData();

		bool UpdatePvdProperties();

		void OnConstraintRelease();

		void OnComShift(int actor);
	};
};