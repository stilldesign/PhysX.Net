#pragma once


namespace PhysX
{
	/// <summary>
	/// Data structure with instanced dynamics data for vehicle with engine, clutch, gears, autobox.
	/// </summary>
	public ref class VehicleDriveDynData
	{
	private:
		PxVehicleDriveDynData* _data;

	internal:
		VehicleDriveDynData(PxVehicleDriveDynData* data);

	public:
		/// <summary>
		/// Set all dynamics data to zero to bring the vehicle to rest.
		/// </summary>
		void SetToRestState();

		void ToggleAutoGears();

		void StartGearChange(int targetGear);
		void ForceGearChange(int targetGear);
		
		/// <summary>
		/// Autogear flag used by vehicle simulation.
		/// </summary>
		property bool UseAutoGears
		{
			bool get();
			void set(bool value);
		}

		/// <summary>
		/// Gearup digital control value used by vehicle simulation.
		/// </summary>
		property bool GearUpPressed
		{
			bool get();
			void set(bool value);
		}

		/// <summary>
		/// Geardown digital control value used by vehicle simulation.
		/// </summary>
		property bool GearDownPressed
		{
			bool get();
			void set(bool value);
		}

		/// <summary>
		/// Current gear.
		/// </summary>
		property int CurrentGear
		{
			int get();
		}

		/// <summary>
		/// Target gear (different from current gear if a gear change is underway).
		/// </summary>
		property int TargetGear
		{
			int get();
		}

		/// <summary>
		/// Return the rotation speed of the engine.
		/// </summary>
		property float EngineRotationSpeed
		{
			float get();
		}

		/// <summary>
		/// Reported time that has passed since gear change started.
		/// </summary>
		property float GearSwitchTime
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// Reported time that has passed since last autobox gearup/geardown decision.
		/// </summary>
		property float AutoBoxSwitchTime
		{
			float get();
			void set(float value);
		}
	};
};