#pragma once

#include "GeometryEnum.h"
//#include <PxSimulationStatistics.h> 

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
			property int NumberOfActiveConstraints;

			/// <summary>
			/// Gets the number of active dynamic bodies for the current simulation step.
			/// </summary>
			property int NumberOfActiveDynamicBodies;

			/// <summary>
			/// Gets the number of active kinematic bodies for the current simulation step.
			/// </summary>
			property int NumberOfActiveKinematicBodies;

			/// <summary>
			/// Gets the number of static bodies for the current simulation step. 
			/// </summary>
			property int NumberOfStaticBodies;

			/// <summary>
			/// Gets the number of dynamic bodies for the current simulation step.
			/// Note: Includes inactive and kinematic bodies, and articulation links.
			/// </summary>
			property int NumberOfDynamicBodies;

			/// <summary>
			/// Gets the number of shapes of each geometry type.
			/// </summary>
			property Dictionary<GeometryType, int>^ NumberOfShapes;

			property Dictionary<VolumeType, int>^ NumberOfBroadPhaseAdds;
			property Dictionary<VolumeType, int>^ NumberOfBroadPhaseRemoves;
	};
};