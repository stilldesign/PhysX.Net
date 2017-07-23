#pragma once

#include "CharacterEnum.h"
#include "ControllerDesc.h"

namespace PhysX
{
	/// <summary>
	/// A descriptor for a capsule character controller.
	/// </summary>
	public ref class CapsuleControllerDesc : ControllerDesc
	{
		public:
			CapsuleControllerDesc();

		internal:
			static PxCapsuleControllerDesc ToUnmanaged(CapsuleControllerDesc^ desc);
			static CapsuleControllerDesc^ ToManaged(PxCapsuleControllerDesc desc);

			static void AssignToManaged(CapsuleControllerDesc^ m, PxCapsuleControllerDesc* u);
			static void AssignToUnmanaged(CapsuleControllerDesc^ m, PxCapsuleControllerDesc* u);

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
			/// Gets or sets the radius of the capsule.
			/// </summary>
			property float Radius;

			/// <summary>
			/// Gets or sets the height of the capsule.
			/// </summary>
			property float Height;

			/// <summary>
			/// Gets or sets the climbing mode.
			/// </summary>
			property CapsuleClimbingMode ClimbingMode;
	};
};