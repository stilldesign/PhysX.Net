#include "StdAfx.h"
#include "MassProperties.h"
#include "Geometry.h"

MassProperties MassProperties::Translate(MassProperties massProperties, Vector3 t)
{
	PxMassProperties m = ToUnmanaged(massProperties);

	m.translate(UV(t));

	return ToManaged(m);
}

MassProperties MassProperties::FromGeometry(Geometry^ geometry)
{
	ThrowIfNull(geometry, "geometry");

	PxGeometry* g = geometry->ToUnmanaged();

	PxMassProperties m(*g);
	delete g;

	return ToManaged(m);
}
PxMassProperties MassProperties::ToUnmanaged(MassProperties m)
{
	PxMassProperties u;
	u.centerOfMass = UV(m.CenterOfMass);
	u.inertiaTensor = MathUtil::MatrixToPxMat33(m.InertiaTensor);
	u.mass = m.Mass;

	return u;
}
MassProperties MassProperties::ToManaged(PxMassProperties u)
{
	MassProperties m;
	m.CenterOfMass = MV(u.centerOfMass);
	m.InertiaTensor = MathUtil::PxMat33ToMatrix(&u.inertiaTensor);
	m.Mass = u.mass;

	return m;
}

Vector3 MassProperties::GetMassSpaceInertia(Matrix4x4 inertia, Quaternion massFrame)
{
	return MV(PxMassProperties::getMassSpaceInertia(MathUtil::MatrixToPxMat33(inertia), MathUtil::QuaternionToPxQuat(massFrame)));
}

Matrix MassProperties::TranslateInertia(Matrix inertia, float mass, Vector3 t)
{
	return MathUtil::PxMat33ToMatrix(&PxMassProperties::translateInertia(MathUtil::MatrixToPxMat33(inertia), mass, UV(t)));
}

Matrix4x4 MassProperties::RotateInertia(Matrix4x4 inertia, Quaternion q)
{
	return MathUtil::PxMat33ToMatrix(&PxMassProperties::rotateInertia(MathUtil::MatrixToPxMat33(inertia), MathUtil::QuaternionToPxQuat(q)));
}

Matrix4x4 MassProperties::ScaleInertia(Matrix4x4 inertia, Quaternion scaleRotation, Vector3 scale)
{
	return MathUtil::PxMat33ToMatrix(&PxMassProperties::scaleInertia(MathUtil::MatrixToPxMat33(inertia), MathUtil::QuaternionToPxQuat(scaleRotation), UV(scale)));
}

MassProperties MassProperties::Sum(array<MassProperties>^ properties, array<Matrix4x4>^ transforms)
{
	ThrowIfNull(properties, "properties");
	ThrowIfNull(transforms, "transforms");

	if (properties->Length != transforms->Length)
		throw gcnew ArgumentException("The length of 'properties' and 'transforms' must be the same");

	int n = properties->Length;

	PxMassProperties* m = new PxMassProperties[n];
	PxTransform* t = new PxTransform[n];

	for (size_t i = 0; i < n; i++)
	{
		m[i] = ToUnmanaged(properties[i]);
		t[i] = MathUtil::MatrixToPxTransform(transforms[i]);
	}

	PxMassProperties sum = PxMassProperties::sum(m, t, n);

	delete[] m;
	delete[] t;

	return ToManaged(sum);
}