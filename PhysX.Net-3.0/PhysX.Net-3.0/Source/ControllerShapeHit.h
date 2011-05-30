#pragma once

#include <PxController.h>

namespace PhysX
{
	ref class Controller;
	ref class Shape;

	/// <summary>
	/// Describes a controller shape hit. Passed to OnShapeHit().
	/// </summary>
	public ref class ControllerShapeHit
	{
		internal:
			static ControllerShapeHit^ ToManaged(PxControllerShapeHit hit);

		public:
			/// <summary>
			/// Current controller.
			/// </summary>
			property Controller^ Controller;

			/// <summary>
			/// Touched shape.
			/// </summary>
			property Shape^ Shape;

			/// <summary>
			/// Contact position in world space.
			/// </summary>
			property Vector3 WorldPosition;

			/// <summary>
			/// Contact normal in world space.
			/// </summary>
			property Vector3 WorldNormal;

			/// <summary>
			/// Motion direction.
			/// </summary>
			property Vector3 Direction;

			/// <summary>
			/// Motion length.
			/// </summary>
			property float Length;
	};
};