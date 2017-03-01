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
				/// A volume belonging to a rigid body object.
				/// </summary>
				RigidBody = PxSimulationStatistics::eRIGID_BODY, 

				/// <summary>
				/// A volume belonging to a particle system.
				/// </summary>
				ParticleSystem = PxSimulationStatistics::ePARTICLE_SYSTEM, 

				/// <summary>
				/// A volume belonging to a rigid body object.
				/// </summary>
				VolumnCount = PxSimulationStatistics::eVOLUME_COUNT 
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
			/// Note: Includes inactive and kinematic bodies, and articulation links.
			/// </summary>
			property int DynamicBodies;

			/// <summary>
			/// Number of articulations in the scene.
			/// </summary>
			property int Articulations;

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
			/// Gets the number of shapes of each geometry type.
			/// </summary>
			property Dictionary<GeometryType, int>^ Shapes;

			property Dictionary<VolumeType, int>^ BroadPhaseAdds;
			property Dictionary<VolumeType, int>^ BroadPhaseRemoves;
	};
};