#pragma once

#include "CharacterEnum.h"

namespace PhysX
{
	ref class Shape;
	ref class RigidActor;

	public ref class ControllerState
	{
	internal:
		static ControllerState^ ToManaged(PxControllerState unmanaged);

	public:
		/// <summary>
		/// Delta position vector for the object the CCT is standing/riding on. Not always match the CCT
		/// delta when variable timesteps are used.
		/// </summary>
		property Vector3 DeltaPosition;

		/// <summary>
		/// Shape on which the CCT is standing.
		/// </summary>
		property Shape^ TouchedShape;

		/// <summary>
		/// Actor owning 'touchedShape'.
		/// </summary>
		property RigidActor^ TouchedActor;

		/// <summary>
		/// Obstacle on which the CCT is standing.
		/// </summary>
		//property ObstacleHandle TouchedObstacleHandle;

		/// <summary>
		/// Last known collision flags (ControllerCollisionFlag)
		/// </summary>
		property ControllerCollisionFlag CollisionFlags;

		/// <summary>
		/// Are we standing on another CCT?
		/// </summary>
		property bool StandingOnAnotherCct;

		/// <summary>
		/// Are we standing on a user-defined obstacle?
		/// </summary>
		property bool StandingOnObstacle;

		/// <summary>
		/// Is CCT moving up or not? (i.e. explicit jumping).
		/// </summary>
		property bool MovingUp;
	};
}