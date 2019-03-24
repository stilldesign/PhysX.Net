#pragma once

#include "Obstacle.h"

namespace PhysX
{
	public ref class BoxObstacle : Obstacle
	{
	internal:
		BoxObstacle(PxObstacle* obstacle);
	public:
		BoxObstacle();
	private:
		static PxBoxObstacle* CreateBoxObstacle();

	public:
		property Vector3 HalfExtents
		{
			Vector3 get();
			void set(Vector3 value);
		}

		property Vector3 Extents
		{
			Vector3 get();
			void set(Vector3 value);
		}

	internal:
		property PxBoxObstacle* UnmanagedPointer
		{
			virtual PxBoxObstacle* get() new;
		}
	};
};