#pragma once

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

			static void BoxControllerDesc::AssignToManaged(BoxControllerDesc^ m, PxBoxControllerDesc* u);
			static void BoxControllerDesc::AssignToUnmanaged(BoxControllerDesc^ m, PxBoxControllerDesc* u);

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
			/// Gets or sets the size/extents of box.
			/// The box size is simply 2*[HalfSideExtent, HalfHeight, HalfForwardExtent].
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