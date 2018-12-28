#pragma once

namespace PhysX
{
	/// <summary>
	/// A contact point as used by contact notification.
	/// </summary>
	public ref class ContactPairPoint
	{
	internal:
		static ContactPairPoint^ ToManaged(PxContactPairPoint unmanaged);

	public:
		/// <summary>
		/// The position of the contact point between the shapes, in world space.
		/// </summary>
		property Vector3 Position;

		/// <summary>
		/// The separation of the shapes at the contact point. A negative separation denotes a penetration.
		/// </summary>
		property float Separation;

		/// <summary>
		/// The normal of the contacting surfaces at the contact point.
		/// </summary>
		property Vector3 Normal;

		/// <summary>
		/// The surface index of shape 0 at the contact point. This is used to identify the surface material.
		/// </summary>
		property int InternalFaceIndex0;

		/// <summary>
		/// The surface index of shape 1 at the contact point. This is used to identify the surface material.
		/// </summary>
		property int InternalFaceIndex1;

		/// <summary>
		/// The impulse applied at the contact point, in world space. Divide by the simulation time step to get a force value.
		/// </summary>
		property Vector3 Impulse;
	};
}