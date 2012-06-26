#pragma once

#include "ConstraintFlag.h"

namespace PhysX
{
	public ref class Constraint1D
	{
	internal:
		static void ToUnmanaged(Constraint1D^ constraint, Px1DConstraint& c);

	public:
		property Vector3 Linear0;
		property float GeometricError;
		property Vector3 Angular0;
		property float VelocityTarget;
		property Vector3 Linear1;
		property float MinimumImpulse;
		property Vector3 Angular1;
		property float MaximumImpulse;
		property float Spring;
		property float Damping;
		property float Restitution;
		property Constraint1DFlag Flags;
		property int SolveGroup;
	};
};