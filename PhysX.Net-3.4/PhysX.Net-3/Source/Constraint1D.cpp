#include "StdAfx.h"
#include "Constraint1D.h"

// Note: Can not return Px1DConstraint because of PX_ALIGN annoyance, instead pass in by ref.
void Constraint1D::ToUnmanaged(Constraint1D^ constraint, Px1DConstraint& c)
{
	ThrowIfNull(constraint, "constraint");

	c.linear0 = UV(constraint->Linear0);
	c.geometricError = constraint->GeometricError;
	c.angular0 = UV(constraint->Angular0);
	c.velocityTarget = constraint->VelocityTarget;
	c.linear1 = UV(constraint->Linear1);
	c.minImpulse = constraint->MinimumImpulse;
	c.angular1 = UV(constraint->Angular1);
	c.maxImpulse = constraint->MaximumImpulse;
	c.mods.spring.damping = constraint->Spring->Damping;
	c.mods.spring.stiffness = constraint->Spring->Stiffness;
	c.mods.bounce.restitution = constraint->Bounce->Restitution;
	c.mods.bounce.velocityThreshold = constraint->Bounce->VelocityThreshold;
	c.flags = ToUnmanagedEnum2(Px1DConstraintFlags, constraint->Flags);
	c.solveHint = constraint->SolveGroup;
}