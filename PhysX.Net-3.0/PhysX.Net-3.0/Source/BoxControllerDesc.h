#pragma once

#include <PxBoxController.h>
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

			property Vector3 Extents;
	};
};