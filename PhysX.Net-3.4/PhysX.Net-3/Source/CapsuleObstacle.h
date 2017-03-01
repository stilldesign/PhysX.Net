#pragma once

#include "Obstacle.h"

namespace PhysX
{
	public ref class CapsuleObstacle : Obstacle
	{
	internal:
		CapsuleObstacle(PxObstacle* obstacle);
	public:
		CapsuleObstacle();
	private:
		static PxCapsuleObstacle* CreateCapsuleObstacle();

	public:
		property float HalfHeight
		{
			float get();
			void set(float value);
		}
		property float Height
		{
			float get();
			void set(float value);
		}

		property float Radius
		{
			float get();
			void set(float value);
		}

	internal:
		property PxCapsuleObstacle* UnmanagedPointer
		{
			virtual PxCapsuleObstacle* get() new;
		}
	};
};