#pragma once


namespace PhysX
{
	namespace VisualDebugger
	{
		/// <summary>
		/// This class has a direct mapping to the PVD::TConnectionType datatype.
		/// It is redefined here because not all classes including this header have the PVDSDK in their include path. 
		/// </summary>
		public enum class InstrumentationFlag
		{
			/// <summary>
			/// Send debugging information to PVD.
			/// This information is the actual object data of the rigid statics, shapes, articulations, etc.
			/// Sending this information has a noticeable impact on performance and thus this flag should not be set if you
			/// want an accurate performance profile.
			/// </summary>
			Debug = PxPvdInstrumentationFlag::eDEBUG,

			/// <summary>
			/// Send profile information to PVD.
			/// This information populates PVD's profile view. It has (at this time) negligible cost compared to Debug
			/// information and makes PVD *much* more useful so it is quite highly recommended. 
			/// </summary>
			Profile = PxPvdInstrumentationFlag::ePROFILE,

			/// <summary>
			/// Send memory information to PVD.
			/// The PVD sdk side hooks into the Foundation memory controller and listens to allocation/deallocation events.
			/// This has a noticable hit on the first frame, however, this data is somewhat compressed and the PhysX SDK doesn't
			/// allocate much once it hits a steady state. This information also has a fairly negligible impact and thus is also
			/// highly recommended.
			/// This flag works together with a PxCreatePhysics parameter, trackOustandingAllocations. Using both of them together
			/// allows users to have an accurate view of the overall memory usage of the simulation at the cost of a hashtable
			/// lookup per allocation/deallocation. Again, PhysX makes a best effort attempt not to allocate or deallocate during
			/// simulation so this hashtable lookup tends to have no effect past the first frame.
			/// Sending memory information without tracking outstanding allocations means that PVD will accurate information about
			/// the state of the memory system before the actual connection happened. 
			/// </summary>
			Memory = PxPvdInstrumentationFlag::eMEMORY,

			All = PxPvdInstrumentationFlag::eALL
		};
	};
};