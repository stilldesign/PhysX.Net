#pragma once

//#include <PxBoxController.h>
#include "CharacterEnum.h"
#include "ControllerDesc.h"

namespace PhysX
{
	/// <summary>
	/// Descriptor for a box character controller.
	/// </summary>
	public ref class BoxControllerDesc : ControllerDesc
	{
		public:
			BoxControllerDesc();

		internal:
			static PxBoxControllerDesc ToUnmanaged(BoxControllerDesc^ desc);
			static BoxControllerDesc^ ToManaged(PxBoxControllerDesc desc);

			virtual PxControllerDesc ToUnmanaged() override;

		public:
			/// <summary>
			/// Resets the structure to the default.
			/// </summary>
			virtual void SetToDefault() override;
			/// <summary>
			/// Returns true if the current settings are valid.
			/// </summary>
			virtual bool IsValid() override;

			/// <summary>
			/// Gets or sets the size of box.
			/// The box size is simply 2xExtents.
			/// Where X = side extent, Y = height extent, Z = forward extent.
			/// </summary>
			property Vector3 Extents
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets controller's half forward extent.
			/// </summary>
			property float HalfForwardExtent;
			/// <summary>
			/// Gets or sets controller's half height.
			/// </summary>
			property float HalfHeight;
			/// <summary>
			/// Gets or sets controller's half side extent.
			/// </summary>
			property float HalfSideExtent;
	};
};