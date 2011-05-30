#pragma  once

#include <PxController.h>
#include "CharacterEnum.h"

namespace PhysX
{
	ref class Material;
	ref class Scene;
	value class FilterData;

	/// <summary>
	/// Descriptor class for a character controller.
	/// </summary>
	public ref class ControllerDesc abstract
	{
		private:
			ControllerShapeType _type;

		internal:
			virtual PxControllerDesc ToUnmanaged() abstract;

			static void AssignToUnmanaged(ControllerDesc^ desc, PxControllerDesc* d);
			static void AssignToManaged(PxControllerDesc* d, ControllerDesc^ desc);

		protected:
			ControllerDesc(ControllerShapeType type);

		public:
			/// <summary>
			/// Resets the structure to the default.
			/// </summary>
			virtual void SetToDefault() abstract;
			/// <summary>
			/// Returns true if the current settings are valid.
			/// </summary>
			virtual bool IsValid() abstract;

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
			property CCTUpAxis UpDirection;

			/// <summary>
			/// Gets or sets the contact offset used by the controller.
			/// </summary>
			property float ContactOffset;

			/// <summary>
			/// Gets or sets the maximum height of an obstacle which the character can climb.
			/// </summary>
			property float StepOffset;

			/// <summary>
			/// Gets or sets the maximum slope which the character can walk up.
			/// </summary>
			property float SlopeLimit;

			///// <summary>
			///// Specifies a user callback interface.
			///// </summary>
			//property  Callback;

			/// <summary>
			/// Gets or sets the interaction flag controls if a character controller collides with other controllers.
			/// </summary>
			property CCTInteractionMode InteractionMode;

			/// <summary>
			/// Gets or sets the material for the actor associated with the controller.
			/// </summary>
			property PhysX::Material^ Material;

			/// <summary>
			/// Gets or sets the user specified data associated with the controller.
			/// </summary>
			property Object^ UserData;
			
			/// <summary>
			/// Gets or sets what scene the controller will be interacting with.
			/// </summary>
			property PhysX::Scene^ Scene;

			///// <summary>
			///// Gets or sets the interaction priority for one-way interaction support.
			///// </summary>
			//property PhysX::DominanceGroup^ DominanceGroup;

			/// <summary>
			/// Gets or sets the simulation filter data for the character controller.
			/// </summary>
			property FilterData^ ControllerSimulationFilterData;

			///// <summary>
			///// The collision shapes of the character controller (for now support only 1 shape).
			///// </summary>
			//property ControllerShapeDesc^ ShapeDesc;

			/// <summary>
			/// Gets or sets the initial pose of the character controller.
			/// </summary>
			property Matrix GlobalPose;

			/// <summary>
			/// Gets or sets the density for proxy shape.
			/// </summary>
			property float Density;
	};
};