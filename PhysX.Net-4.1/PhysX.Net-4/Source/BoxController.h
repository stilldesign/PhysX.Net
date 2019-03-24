#pragma once

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
			/// <summary>
			/// Gets or sets the extents of box.
			/// Where X = side extent, Y = height extent, Z = forward extent.
			/// </summary>
			property Vector3 Extents
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the size of box.
			/// The box size is simply 2xExtents.
			/// Where X = side extent, Y = height extent, Z = forward extent.
			/// </summary>
			property Vector3 Size
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets controller's half height.
			/// </summary>
			property float HalfHeight
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets controller's half side extent.
			/// </summary>
			property float HalfSideExtent
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets controller's half forward extent.
			/// </summary>
			property float HalfForwardExtent
			{
				float get();
				void set(float value);
			}

		internal:
			property PxBoxController* UnmanagedPointer
			{
				PxBoxController* get() new;
			}
	};
};