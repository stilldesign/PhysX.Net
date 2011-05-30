#pragma once

class PxDeformableConstrainCoefficients;

namespace PhysX
{
	/// <summary>
	/// Defines a set of per vertex coefficients.
	/// The user can supply a buffer of positions and normals coming from an animation of the deformable.
	/// The simulated vertices are then corrected via the constrain positions, normals and the constrain coefficiens.
	/// </summary>
	public ref class DeformableConstrainCoefficients
	{
		public:
			DeformableConstrainCoefficients();

		internal:
			static DeformableConstrainCoefficients^ ToManaged(PxDeformableConstrainCoefficients coe);
			static PxDeformableConstrainCoefficients ToUnmanaged(DeformableConstrainCoefficients^ coe);

		public:
			/// <summary>
			/// (Re)sets the structure to the default.
			/// </summary>
			void SetToDefault();
			/// <summary>
			/// Returns true if the current settings are valid.
			/// </summary>
			bool IsValid();

			/// <summary>Gets the maximum distance.</summary>
			property float MaximumDistance;

			/// <summary>Gets the collision sphere radius.</summary>
			property float CollisionSphereRadius;

			/// <summary>Gets the collision sphere distance.</summary>
			property float CollisionSphereDistance;
	};
};