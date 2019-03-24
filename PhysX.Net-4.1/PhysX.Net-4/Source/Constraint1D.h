#pragma once

#include "ConstraintEnum.h"

namespace PhysX
{
	ref class SpringModifiers;
	ref class RestitutionModifiers;

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
		property SpringModifiers^ Spring;
		property RestitutionModifiers^ Bounce;
		property Constraint1DFlag Flags;
		property int SolveGroup;
	};

	public ref class SpringModifiers 
	{
	internal:
		property float Stiffness;
		property float Damping;
	};

	public ref class RestitutionModifiers 
	{
	internal:
		property float Restitution;
		property float VelocityThreshold;
	};
};