#pragma once

#include "Obstacle.h"

namespace PhysX
{
	ref class ControllerManager;

	/// <summary>
	/// Context class for obstacles.
	/// An obstacle context class contains and manages a set of user-defined obstacles.
	/// </summary>
	public ref class ObstacleContext : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxObstacleContext* _context;

	internal:
		ObstacleContext(PxObstacleContext* context, ControllerManager^ owner);
	public:
		~ObstacleContext();
	protected:
		!ObstacleContext();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		/// <summary>
		/// Adds an obstacle to the context.
		/// </summary>
		int AddObstacle(Obstacle^ obstacle);
 
		/// <summary>
		/// Removes an obstacle from the context.
		/// </summary>
		bool RemoveObstacle(int handle);
		
		/// <summary>
		/// Updates data for an existing obstacle.
		/// </summary>
		bool UpdateObstacle(int handle, Obstacle^ obstacle);
		
		/// <summary>
		/// Retrieves desired obstacle.
		/// </summary>
		Obstacle^ GetObstacle(int i);

		/// <summary>
		/// Retrieves number of obstacles in the context.
		/// </summary>
		property int NumberOfObstacles
		{
			int get();
		}

	internal:
		property PxObstacleContext* UnmanagedPointer
		{
			PxObstacleContext* get();
		}
	};
};