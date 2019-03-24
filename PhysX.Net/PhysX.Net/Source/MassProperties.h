#pragma once

namespace PhysX
{
	ref class Geometry;

	public value class MassProperties
	{
	public:
		/// <summary>
		/// The inertia tensor of the object.
		/// Only the upper 3x3 portion of this matrix is used. System.Numerics doesn't have a
		/// Matrix3x3 so we just make use of the 4x4.
		/// </summary>
		property Matrix4x4 InertiaTensor;

		/// <summary>
		/// The center of mass of the object.
		/// </summary>
		property Vector3 CenterOfMass;

		/// <summary>
		/// The mass of the object.
		/// </summary>
		property float Mass;

		/// <summary>
		/// Translate the center of mass by a given vector and adjust the inertia tensor accordingly.
		/// </summary>
		static MassProperties Translate(MassProperties massProperties, Vector3 t);

		static MassProperties FromGeometry(Geometry^ geometry);

		/// <summary>
		/// Get the entries of the diagonalized inertia tensor and the corresponding reference rotation.
		/// </summary>
		static Vector3 GetMassSpaceInertia(Matrix4x4 inertia, Quaternion massFrame);

		/// <summary>
		/// Translate an inertia tensor using the parallel axis theorem.
		/// </summary>
		/// <param name="inertia"></param>
		/// <param name="mass"></param>
		/// <param name="t"></param>
		static Matrix TranslateInertia(Matrix inertia, float mass, Vector3 t);
		
		/// <summary>
		/// Rotate an inertia tensor around the center of mass.
		/// </summary>
		/// <param name="inertia"></param>
		/// <param name="q"></param>
		static Matrix4x4 RotateInertia(Matrix4x4 inertia, Quaternion q);
		
		/// <summary>
		/// Non - uniform scaling of the inertia tensor.
		/// </summary>
		/// <param name="inertia"></param>
		/// <param name="scaleRotation"></param>
		/// <param name="scale"></param>
		static Matrix4x4 ScaleInertia(Matrix4x4 inertia, Quaternion scaleRotation, Vector3 scale);

		/// <summary>
		/// Sum up individual mass properties.
		/// </summary>
		static MassProperties Sum(array<MassProperties>^ properties, array<Matrix4x4>^ transforms);

	internal:
		static PxMassProperties ToUnmanaged(MassProperties m);
		static MassProperties ToManaged(PxMassProperties u);
	};
}