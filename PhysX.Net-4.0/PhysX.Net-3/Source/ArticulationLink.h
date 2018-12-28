#pragma once

#include "RigidBody.h"

namespace PhysX
{
	ref class Articulation;
	ref class ArticulationJoint;

	/// <summary>Articulation link.</summary>
	public ref class ArticulationLink : RigidBody
	{
		internal:
			ArticulationLink(PxArticulationLink* articulationLink, PhysX::Articulation^ owner);
		public:
			~ArticulationLink();
		protected:
			!ArticulationLink();

		public:
			/// <summary>Gets the articulation to which this articulation link belongs.</summary>
			property PhysX::Articulation^ Articulation
			{
				PhysX::Articulation^ get();
			}

			/// <summary>Gets the joint which connects this link to its parent.</summary>
			property PhysX::ArticulationJoint^ ArticulationJoint
			{
				PhysX::ArticulationJoint^ get();
			}

			/// <summary>Gets all the child links.</summary>
			property array<PhysX::ArticulationLink^>^ Children
			{
				array<PhysX::ArticulationLink^>^ get();
			}

		internal:
			property PxArticulationLink* UnmanagedPointer
			{
				PxArticulationLink* get();
			}
	};
};