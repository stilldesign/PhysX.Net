#pragma once

//#include <PxShape.h>

namespace PhysX
{
	/// <summary>
	/// Flags which affect the behavior of PxShapes.
	/// </summary>
	public enum class ShapeFlag
	{
		SimulationShape = PxShapeFlag::eSIMULATION_SHAPE,
		SceneQueryShape = PxShapeFlag::eSCENE_QUERY_SHAPE,
		TriggerShape = PxShapeFlag::eTRIGGER_SHAPE,
		Visualization = PxShapeFlag::eVISUALIZATION,
		ParticleDrain = PxShapeFlag::ePARTICLE_DRAIN
	};
};