#pragma once

#include "GeometryEnum.h"

namespace PhysX
{
	/// <summary>
	/// Class used to retrieve statistics for a simulation step.
	/// </summary>
	public ref class SimulationStatistics
	{
		public:
			#pragma region Enums
			/// <summary>
			/// Identifies each type of broadphase volume.
			/// </summary>
			enum class VolumeType
			{
				/// <summary>
				/// Shape pairs processed as discrete contact pairs for the current simulation step.
				/// </summary>
				DiscreteContactPairs = PxSimulationStatistics::eDISCRETE_CONTACT_PAIRS,

				/// <summary>
				/// Shape pairs processed as swept integration pairs for the current simulation step.
				/// </summary>
				/// <remarks>
				/// Counts the pairs for which special CCD (continuous collision detection) work was actually done and NOT the number of pairs which were configured for CCD.
				/// Furthermore, there can be multiple CCD passes and all processed pairs of all passes are summed up, hence the number can be larger than the amount of pairs which have been configured for CCD.
				/// </remarks>
				CcdPairs = PxSimulationStatistics::eCCD_PAIRS,

				/// <summary>
				/// Shape pairs processed with user contact modification enabled for the current simulation step.
				/// </summary>
				ModifiedContactPairs = PxSimulationStatistics::eMODIFIED_CONTACT_PAIRS,

				/// <summary>
				/// Trigger shape pairs processed for the current simulation step.
				/// </summary>
				TriggerPairs = PxSimulationStatistics::eTRIGGER_PAIRS
			};

			/// <summary>
			/// Different types of rigid body collision pair statistics.
			/// </summary>
			enum class RigidBodyPairStatsType
			{
				/// <summary>
				/// Shape pairs processed as discrete contact pairs for the current simulation step.
				/// Discrete contact pairs do not have the PairFlag.SweptContactGeneration flag set.
				/// </summary>
				DiscreteContactPairs = PxSimulationStatistics::eDISCRETE_CONTACT_PAIRS,

				/// <summary>
				/// Shape pairs processed as swept integration pairs for the current simulation step.
				/// </summary>
				CCDPairs = PxSimulationStatistics::eCCD_PAIRS,

				/// <summary>
				/// Shape pairs processed with user contact modification enabled for the current simulation step.
				/// </summary>
				ModifiedContactPairs = PxSimulationStatistics::eMODIFIED_CONTACT_PAIRS,

				/// <summary>
				/// Trigger shape pairs processed for the current simulation step.
				/// </summary>
				TriggerPairs = PxSimulationStatistics::eTRIGGER_PAIRS
			};
			#pragma endregion

			SimulationStatistics();

		internal:
			static SimulationStatistics^ ToManaged(PxSimulationStatistics* stats);

		public:
			/// <summary>
			/// Gets the number of active Constraint objects (joints etc.) for the current simulation step.
			/// </summary>
			property int ActiveConstraints;

			/// <summary>
			/// Gets the number of active dynamic bodies for the current simulation step.
			/// </summary>
			property int ActiveDynamicBodies;

			/// <summary>
			/// Gets the number of active kinematic bodies for the current simulation step.
			/// </summary>
			property int ActiveKinematicBodies;

			/// <summary>
			/// Gets the number of static bodies for the current simulation step. 
			/// </summary>
			property int StaticBodies;

			/// <summary>
			/// Gets the number of dynamic bodies for the current simulation step.
			/// Note: Includes inactive bodies and articulation links.
			/// Note: Does not include kinematic bodies.
			/// </summary>
			property int DynamicBodies;

			/// <summary>
			/// Number of kinematic bodies for the current simulation step.
			/// </summary>
			property int KinematicBodies;

			/// <summary>
			/// Number of aggregates in the scene.
			/// </summary>
			property int Aggregates;

			/// <summary>
			/// Number of articulations in the scene.
			/// </summary>
			property int Articulations;

			/// <summary>
			/// The number of 1D axis constraints(joints + contact) present in the current simulation step.
			/// </summary>
			property int AxisSolverConstraints;

			/// <summary>
			/// The size(in bytes) of the compressed contact stream in the current simulation step.
			/// </summary>
			property int CompressedContactSize;

			/// <summary>
			/// The total required size(in bytes) of the contact constraints in the current simulation step.
			/// </summary>
			property int RequiredContactConstraintMemory;

			/// <summary>
			/// The peak amount of memory(in bytes) that was allocated for constraints(this includes joints) in the current simulation step.
			/// </summary>
			property int PeakConstraintMemory;

			/// <summary>
			/// Total number of (non CCD) pairs reaching narrow phase.
			/// </summary>
			property int DiscreteContactPairsTotal;

			/// <summary>
			/// Total number of (non CCD) pairs for which contacts are successfully cached (<=DiscreteContactPairsTotal). 
			/// This includes pairs for which no contacts are generated, it still counts as a cache hit.
			/// </summary>
			property int DiscreteContactPairsWithCacheHits;

			/// <summary>
			/// Total number of (non CCD) pairs for which at least 1 contact was generated (<=DiscreteContactPairsTotal).
			/// </summary>
			property int DiscreteContactPairsWithContacts;

			/// <summary>
			/// Number of new pairs found by BP this frame.
			/// </summary>
			property int NewPairs;

			/// <summary>
			/// Number of new touches found by NP this frame.
			/// </summary>
			property int NewTouches;

			/// <summary>
			/// Number of lost touches from NP this frame.
			/// </summary>
			property int LostTouches;

			/// <summary>
			/// Number of partitions used by the solver this frame.
			/// </summary>
			property int Partitions;

			/// <summary>
			/// Gets the number of shapes of each geometry type.
			/// </summary>
			property Dictionary<GeometryType, int>^ Shapes;

			property int BroadPhaseAdds;
			property int BroadPhaseRemoves;

			/// <summary>
			/// Use [GeometryType, GeometryType] to lookup a pair.
			/// </summary>
			property array<int, 2>^ ModifiedContactPairs;

			/// <summary>
			/// Use [GeometryType, GeometryType] to lookup a pair.
			/// </summary>
			property array<int, 2>^ TriggerPairs;

			property int ParticlesGpuMeshCacheSize;
			property int ParticlesGpuMeshCacheUsed;
			property float ParticlesGpuMeshCacheHitrate;
	};
};