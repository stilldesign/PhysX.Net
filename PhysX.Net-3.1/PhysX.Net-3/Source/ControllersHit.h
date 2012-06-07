#pragma once

#include <PxController.h> 

namespace PhysX
{
	ref class Controller;

	/// <summary>
	/// Describe a controller hit. Passed to OnControllerHit().
	/// </summary>
	public ref class ControllersHit
	{
		internal:
			static PxControllersHit ToUnmanaged(ControllersHit^ hit);
			static ControllersHit^ ToManaged(PxControllersHit hit);

		public:
			/// <summary>
			/// Current controller.
			/// </summary>
			property PhysX::Controller^ Controller;

			/// <summary>
			/// Touched controller.
			/// </summary>
			property PhysX::Controller^ Other;
	};
};