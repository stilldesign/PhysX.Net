#pragma once

#include <PxController.h>

namespace PhysX
{
	ref class Controller;

	public ref class CctHit abstract
	{
	protected:
		static void PopulateManaged(PxCCTHit* unmanaged, CctHit^ managed);
		static void PopulateUnmanaged(PxCCTHit* unmanaged, CctHit^ managed);

	public:
		/// <summary>
		/// Current controller.
		/// </summary>
		property PhysX::Controller^ Controller;

		/// <summary>
		/// Contact position in world space.
		/// </summary>
		property Vector3 WorldPosition;

		/// <summary>
		/// Contact normal in world space.
		/// </summary>
		property Vector3 WorldNormal;

		/// <summary>
		/// Motion direction.
		/// </summary>
		property Vector3 Direction;

		/// <summary>
		/// Motion length.
		/// </summary>
		property float Length;
	};
};