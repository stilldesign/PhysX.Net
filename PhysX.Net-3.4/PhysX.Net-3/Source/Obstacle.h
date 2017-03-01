#pragma once

#include "GeometryEnum.h"

namespace PhysX
{
	/// <summary>
	/// Base class for obstacles.
	/// </summary>
	public ref class Obstacle abstract
	{
	private:
		PxObstacle* _obstacle;

	protected:
		Obstacle(PxObstacle* obstacle);
	public:
		~Obstacle();
	protected:
		!Obstacle();

	public:
		property GeometryType Type
		{
			GeometryType get();
		}

		property Vector3 Position
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Quaternion Rotation
		{
			Quaternion get();
			void set(Quaternion value);
		}

	internal:
		property PxObstacle* UnmanagedPointer
		{
			PxObstacle* get();
		}
	};
};