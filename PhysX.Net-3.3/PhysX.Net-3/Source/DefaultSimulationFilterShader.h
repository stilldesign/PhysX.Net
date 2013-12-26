#pragma once

namespace PhysX
{
	public ref class DefaultSimulationFilterShader
	{
	private:
		DefaultSimulationFilterShader();

	public:
		static FilterFlag Setup(int attributes0, FilterData filterData0, int attributes1, FilterData filterData1, PairFlag pairFlags, array<Byte>^ constantBlock);

		static bool GetGroupCollisionFlag(int group1, int group2);
		static void SetGroupCollisionFlag(int group1, int group2, bool enable);

		static int GetGroup(RigidActor^ actor);
		static void SetGroup(RigidActor^ actor, int collisionGroup);

		property static SimulationFilterShaderOps FilterOps
		{
			SimulationFilterShaderOps get();
			void set(SimulationFilterShaderOps value);
		}
	};
};