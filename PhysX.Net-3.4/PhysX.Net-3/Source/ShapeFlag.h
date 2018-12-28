#pragma once

namespace PhysX
{
	/// <summary>
	/// Flags which affect the behavior of Shapes.
	/// </summary>
	[Flags]
	public enum class ShapeFlag
	{
		SimulationShape = PxShapeFlag::eSIMULATION_SHAPE,
		SceneQueryShape = PxShapeFlag::eSCENE_QUERY_SHAPE,
		TriggerShape = PxShapeFlag::eTRIGGER_SHAPE,
		Visualization = PxShapeFlag::eVISUALIZATION
	};
};