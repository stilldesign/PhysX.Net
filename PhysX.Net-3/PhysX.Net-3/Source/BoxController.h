#pragma  once

#include <PxBoxController.h>
#include "CharacterEnum.h"
#include "Controller.h"

namespace PhysX
{
	/// <summary>
	/// Box character controller.
	/// </summary>
	public ref class BoxController : Controller
	{
		internal:
			BoxController(PxBoxController* boxController, PhysX::ControllerManager^ controllerManager);

		public:
			/// <summary>Gets or sets the extents of box.</summary>
			property Vector3 Extents
			{
				Vector3 get();
				void set( Vector3 value );
			}

			/// <summary>Gets or sets the size of box.</summary>
			property Vector3 Size
			{
				Vector3 get();
				void set( Vector3 value );
			}

		internal:
			property PxBoxController* UnmanagedPointer
			{
				PxBoxController* get() new;
			}
	};
};