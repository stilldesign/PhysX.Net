#pragma once

#include "RigidDynamic.h"

namespace PhysX
{
	ref class Physics;
	ref class Actor;

	public ref class VehicleWheels abstract : IDisposable
	{
	public:
		/// <summary>Raised before any disposing is performed.</summary>
		virtual event EventHandler^ OnDisposing;
		/// <summary>Raised once all disposing is performed.</summary>
		virtual event EventHandler^ OnDisposed;

	private:
		PxVehicleWheels* _wheels;

	protected:
		VehicleWheels(PxVehicleWheels* wheels, PhysX::Physics^ owner);
	public:
		~VehicleWheels();
	protected:
		!VehicleWheels();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		//
		
		float ComputeForwardSpeed();
		float ComputeSidewaysSpeed();

		//

		/// <summary>
		/// Gets the parent physics object.
		/// </summary>
		property PhysX::Physics^ Physics
		{
			PhysX::Physics^ get();
		}

		property int VehicleType
		{
			int get();
		}

		property PhysX::RigidDynamic^ Actor
		{
			PhysX::RigidDynamic^ get();
		}

	internal:
		property PxVehicleWheels* UnmanagedPointer
		{
			PxVehicleWheels* get();
		}
	};
};