#pragma once

//#include <PxController.h>
#include "CharacterEnum.h"

namespace PhysX
{
	ref class Material;
	ref class Scene;
	value class FilterData;
	ref class UserControllerHitReport;

	/// <summary>
	/// Descriptor class for a character controller.
	/// </summary>
	public ref class ControllerDesc abstract
	{
	private:
		ControllerShapeType _type;

	internal:
		virtual PxControllerDesc ToUnmanaged() abstract;

		static void AssignToUnmanaged(ControllerDesc^ desc, PxControllerDesc& d);
		static void AssignToManaged(PxControllerDesc& d, ControllerDesc^ desc);

	protected:
		ControllerDesc(ControllerShapeType type);

	public:
		/// <summary>
		/// Resets the structure to the default.
		/// </summary>
		virtual void SetToDefault();
		/// <summary>
		/// Returns true if the current settings are valid.
		/// </summary>
		virtual bool IsValid() abstract;

		//

		/// <summary>
		/// Gets the character controller type.
		/// </summary>
		property ControllerShapeType Type
		{
			ControllerShapeType get();
		}

		/// <summary>
		/// Gets or sets the position of the character.
		/// </summary>
		property Vector3 Position;

		/// <summary>
		/// Gets or sets the 'up' direction.
		/// </summary>
		property Vector3 UpDirection;

		/// <summary>
		/// Gets or sets the maximum slope which the character can walk up.
		/// </summary>
		property float SlopeLimit;

		/// <summary>
		/// Gets or sets the contact offset used by the controller.
		/// </summary>
		property float ContactOffset;

		/// <summary>
		/// Gets or sets the maximum height of an obstacle which the character can climb.
		/// </summary>
		property float StepOffset;

		/// <summary>
		/// Gets or sets the density for proxy shape.
		/// </summary>
		property float Density;

		/// <summary>
		/// Gets or sets scale coeff for underlying kinematic actor.
		/// </summary>
		property float ScaleCoefficient;

		/// <summary>
		/// Gets or sets the non-walkable mode controls if a character controller slides or not on a non-walkable part.
		/// </summary>
		property ControllerNonWalkableMode NonWalkableMode;
			
		/// <summary>
		/// Gets or sets the material for the actor associated with the controller.
		/// </summary>
		property PhysX::Material^ Material;

		/// <summary>
		/// Gets or sets the user specified data associated with the controller.
		/// </summary>
		property Object^ UserData;
	};
};