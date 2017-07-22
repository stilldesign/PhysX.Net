#pragma once

#include <PxBroadPhase.h>

namespace PhysX
{
	/// <summary>
	/// Broad phase algorithm used in the simulation. 
	/// eSAP is a good generic choice with great performance when many objects are sleeping.Performance can degrade significantly though, when all objects are moving, or when large numbers of objects are added to or removed from the broad phase.This algorithm does not need world bounds to be defined in order to work.
	/// eMBP is an alternative broad phase algorithm that does not suffer from the same performance issues as eSAP when all objects are moving or when inserting large numbers of objects.However its generic performance when many objects are sleeping might be inferior to eSAP, and it requires users to define world bounds in order to work.
	/// </summary>
	[Flags]
	public enum class BroadPhaseType
	{
		/// <summary>
		/// 3-axes sweep-and-prune.
		/// </summary>
		SweepAndPrune = PxBroadPhaseType::eSAP,

		/// <summary>
		/// Multi box pruning.
		/// </summary>
		MultiBoxPrune = PxBroadPhaseType::eMBP,

		Gpu = PxBroadPhaseType::eGPU
	};
};