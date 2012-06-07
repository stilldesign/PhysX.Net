#pragma once

#include "RigidDynamic.h"
#include <PxVehicleWheels.h> 

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
		
		/// <summary>
		/// Set mapping between wheel id and position of corresponding wheel shape in the list of actor shapes.
		/// This mapping is used to pose the correct wheel shapes with the latest wheel rotation angle, steer
		/// angle, and suspension travel and allows arbitrary ordering of the wheel shapes in the actor's list
		/// of shapes. Use setWheelShapeMapping(i,-1) to register that there is no wheel shape corresponding
		/// to the ith wheel Set setWheelShapeMapping(i,k) to register that the ith wheel corresponds to the
		/// kth shape in the actor's list of shapes. Default value are provided in the setup functions.
		/// The default values correspond to setWheelShapeMapping(i,i) for all i<numWheels.
		/// </summary>
		void SetWheelShapeMapping(int wheelId, int shapeId);

		float ComputeForwardSpeed();
		float ComputeSidewaysSpeed();
		bool IsInAir();
		bool IsInAir(int wheelId);

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