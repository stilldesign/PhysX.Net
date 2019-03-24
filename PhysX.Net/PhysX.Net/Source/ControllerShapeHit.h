#pragma once

#include "ControllerHit.h"

namespace PhysX
{
	ref class Controller;
	ref class Shape;

	/// <summary>
	/// Describes a controller shape hit. Passed to OnShapeHit().
	/// </summary>
	public ref class ControllerShapeHit : ControllerHit
	{
		internal:
			static ControllerShapeHit^ ToManaged(PxControllerShapeHit hit);

		public:
			/// <summary>
			/// Touched shape.
			/// </summary>
			property Shape^ Shape;

			/// <summary>
			/// Touched triangle index (only for meshes/heightfields).
			/// </summary>
			property int TriangleIndex;
	};
};