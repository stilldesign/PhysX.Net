#pragma once

#include "ControllerHit.h"

namespace PhysX
{
	ref class Controller;

	/// <summary>
	/// Describe a controller hit. Passed to OnControllerHit().
	/// </summary>
	public ref class ControllersHit : ControllerHit
	{
		internal:
			//static PxControllersHit ToUnmanaged(ControllersHit^ hit);
			static ControllersHit^ ToManaged(PxControllersHit hit);

		public:
			/// <summary>
			/// Touched controller.
			/// </summary>
			property PhysX::Controller^ Other;
	};
};