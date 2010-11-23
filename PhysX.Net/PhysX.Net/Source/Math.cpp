#include "StdAfx.h"

#include "Math.h"
#include <NxMat34.h>
#include <NxQuat.h>

UsingFrameworkNamespace

using namespace StillDesign::PhysX;
using namespace StillDesign::PhysX::MathPrimitives;

Matrix StillDesign::PhysX::Math::Mat34ToMatrix( NxMat34* pose )
{
	float mat[ 4*4 ];
	pose->getRowMajor44( &mat[ 0 ] );
	
	Matrix matrix = Matrix::Identity;
	
	matrix.M11 = mat[ 0 ];
	matrix.M21 = mat[ 1 ];
	matrix.M31 = mat[ 2 ];
	matrix.M41 = mat[ 3 ];
	
	matrix.M12 = mat[ 4 ];
	matrix.M22 = mat[ 5 ];
	matrix.M32 = mat[ 6 ];
	matrix.M42 = mat[ 7 ];
	
	matrix.M13 = mat[ 8 ];
	matrix.M23 = mat[ 9 ];
	matrix.M33 = mat[ 10 ];
	matrix.M43 = mat[ 11 ];
	
	matrix.M14 = mat[ 12 ];
	matrix.M24 = mat[ 13 ];
	matrix.M34 = mat[ 14 ];
	matrix.M44 = mat[ 15 ];
	
	return matrix;
}

Matrix StillDesign::PhysX::Math::Mat44ToMatrix( const float* matrix44 )
{
	Matrix matrix;
		matrix.M11 = matrix44[ 0 ];
		matrix.M21 = matrix44[ 1 ];
		matrix.M31 = matrix44[ 2 ];
		matrix.M41 = matrix44[ 3 ];
		
		matrix.M12 = matrix44[ 4 ];
		matrix.M22 = matrix44[ 5 ];
		matrix.M32 = matrix44[ 6 ];
		matrix.M42 = matrix44[ 7 ];
		
		matrix.M13 = matrix44[ 8 ];
		matrix.M23 = matrix44[ 9 ];
		matrix.M33 = matrix44[ 10 ];
		matrix.M43 = matrix44[ 11 ];
		
		matrix.M14 = matrix44[ 12 ];
		matrix.M24 = matrix44[ 13 ];
		matrix.M34 = matrix44[ 14 ];
		matrix.M44 = matrix44[ 15 ];
	
	return matrix;
}

Matrix StillDesign::PhysX::Math::Mat33ToMatrix( NxMat33* orientation )
{
	float mat[ 3*3 ];
	orientation->getRowMajor( &mat[ 0 ] );
	
	Matrix matrix = Matrix::Identity;
	
	matrix.M11 = mat[ 0 ];
	matrix.M21 = mat[ 1 ];
	matrix.M31 = mat[ 2 ];
	
	matrix.M12 = mat[ 3 ];
	matrix.M22 = mat[ 4 ];
	matrix.M32 = mat[ 5 ];
	
	matrix.M13 = mat[ 6 ];
	matrix.M23 = mat[ 7 ];
	matrix.M33 = mat[ 8 ];
	
	return matrix;
}

NxMat34 StillDesign::PhysX::Math::MatrixToMat34( Matrix matrix )
{
	float values[ 16 ];
		values[ 0 ] = matrix.M11;
		values[ 1 ] = matrix.M21;
		values[ 2 ] = matrix.M31;
		values[ 3 ] = matrix.M41;
		
		values[ 4 ] = matrix.M12;
		values[ 5 ] = matrix.M22;
		values[ 6 ] = matrix.M32;
		values[ 7 ] = matrix.M42;
		
		values[ 8 ] = matrix.M13;
		values[ 9 ] = matrix.M23;
		values[ 10 ] = matrix.M33;
		values[ 11 ] = matrix.M43;
		
		values[ 12 ] = matrix.M14;
		values[ 13 ] = matrix.M24;
		values[ 14 ] = matrix.M34;
		values[ 15 ] = matrix.M44;
	
	NxMat34 mat = NxMat34( true );
		mat.setRowMajor44( &values[ 0 ] );
	
	return mat;
}
NxMat33 StillDesign::PhysX::Math::MatrixToMat33( Matrix matrix )
{
	float values[ 9 ];
		values[ 0 ] = matrix.M11;
		values[ 1 ] = matrix.M21;
		values[ 2 ] = matrix.M31;
		
		values[ 3 ] = matrix.M12;
		values[ 4 ] = matrix.M22;
		values[ 5 ] = matrix.M32;
		
		values[ 6 ] = matrix.M13;
		values[ 7 ] = matrix.M23;
		values[ 8 ] = matrix.M33;
	
	NxMat33 mat( NX_ZERO_MATRIX );
		mat.setRowMajor( &values[ 0 ] );
	
	return mat;
}
void StillDesign::PhysX::Math::MatrixToMat44( Matrix matrix44, float* outMatrix44 )
{
	outMatrix44[ 0 ] = matrix44.M11;
	outMatrix44[ 1 ] = matrix44.M21;
	outMatrix44[ 2 ] = matrix44.M31;
	outMatrix44[ 3 ] = matrix44.M41;
	
	outMatrix44[ 4 ] = matrix44.M12;
	outMatrix44[ 5 ] = matrix44.M22;
	outMatrix44[ 6 ] = matrix44.M32;
	outMatrix44[ 7 ] = matrix44.M42;
	
	outMatrix44[ 8 ] = matrix44.M13;
	outMatrix44[ 9 ] = matrix44.M23;
	outMatrix44[ 10 ] = matrix44.M33;
	outMatrix44[ 11 ] = matrix44.M43;
	
	outMatrix44[ 12 ] = matrix44.M14;
	outMatrix44[ 13 ] = matrix44.M24;
	outMatrix44[ 14 ] = matrix44.M34;
	outMatrix44[ 15 ] = matrix44.M44;
}

Vector3 StillDesign::PhysX::Math::QuatToEuler( NxQuat q )
{
	q.normalize();
	
	float sqw = q.w * q.w;
	float sqx = q.x * q.x;
	float sqy = q.y * q.y;
	float sqz = q.z * q.z;
	
	float test = q.x*q.y + q.z*q.w;
	
	Vector3 rotation = Vector3( 0, 0, 0 );
	
	// Singularity at north pole
	if( test >= 0.499999999999999999f )
	{
		rotation.Y = 2.0f * atan2( q.x, q.w );
		rotation.Z = (float)System::Math::PI;
		rotation.X = 0.0f;
		
		return rotation;
	}
	if( test <= -0.499999999999999999f )
	{
		rotation.Y = -2.0f * atan2( q.x, q.w );
		rotation.Z = -((float)System::Math::PI / 2.0f);
		rotation.X = 0.0f;
		
		return rotation;
	}
	
	rotation.Y = atan2(2*q.y*q.w-2*q.x*q.z , sqx - sqy - sqz + sqw);
	rotation.Z = asin(2*test);
	rotation.X = atan2(2*q.x*q.w-2*q.y*q.z , -sqx + sqy - sqz + sqw);
	
	return rotation;
}
//Quaternion StillDesign::PhysX::Math::RoationMatrixToQuaternion( NxMat33 matrix )
//{
//	Quaternion q = gcnew Quaternion()
//		q.W = (float)Math.Sqrt( Math.Max( 0, 1 + matrix.M11 + matrix.M22 + matrix.M33 ) ) / 2.0f,
//		q.X = (float)Math.Sqrt( Math.Max( 0, 1 + matrix.M11 - matrix.M22 - matrix.M33 ) ) / 2.0f,
//		q.Y = (float)Math.Sqrt( Math.Max( 0, 1 - matrix.M11 + matrix.M22 - matrix.M33 ) ) / 2.0f,
//		q.Z = (float)Math.Sqrt( Math.Max( 0, 1 - matrix.M11 - matrix.M22 + matrix.M33 ) ) / 2.0f
//		
//		q.X = CopySign( q.X, matrix.M23 - matrix.M32 );
//		q.Y = CopySign( q.Y, matrix.M31 - matrix.M13 );
//		q.Z = CopySign( q.Z, matrix.M12 - matrix.M21 );
//	
//	return q;
//}

Vector3 StillDesign::PhysX::Math::NxVec3ToVector3( NxVec3 vector )
{
	return Vector3( vector.x, vector.y, vector.z );
}
Vector3 StillDesign::PhysX::Math::NxVec3ToVector3( NxExtendedVec3 vector )
{
	return Vector3( (float)vector.x, (float)vector.y, (float)vector.z );
}
NxVec3 StillDesign::PhysX::Math::Vector3ToNxVec3( Vector3 vector )
{
	return NxVec3( vector.X, vector.Y, vector.Z );
}

Quaternion StillDesign::PhysX::Math::NxQuatToQuaternion( NxQuat quat )
{
	return Quaternion( quat.x, quat.y, quat.z, quat.w );
}
NxQuat StillDesign::PhysX::Math::QuaternionNxQuat( Quaternion quat )
{
	return NxQuat( NxVec3( quat.X, quat.Y, quat.Z ), quat.W );
}

NxPlane StillDesign::PhysX::Math::PlaneToNxPlane( Plane plane )
{
	Vector3 normal = plane.Normal;	

	return NxPlane( normal.X, normal.Y, normal.Z, plane.D );
}
Plane StillDesign::PhysX::Math::NxPlaneToPlane( NxPlane plane )
{
	return Plane( plane.normal.x, plane.normal.y, plane.normal.z, plane.d );
}