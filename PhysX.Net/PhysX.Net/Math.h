#pragma once

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		private ref class Math
		{
			internal:
				static Matrix Mat34ToMatrix( NxMat34* pose );
				static Matrix Mat33ToMatrix( NxMat33* orientation );
				static Matrix Mat44ToMatrix( const float* matrix44 );
				
				static NxMat34 MatrixToMat34( Matrix matrix );
				static NxMat33 MatrixToMat33( Matrix matrix );
				static void MatrixToMat44( Matrix matrix44, float* outMatrix44 );
				
				static Vector3 QuatToEuler( NxQuat q );
				
				static Vector3 NxVec3ToVector3( NxVec3 vector );
				static NxVec3 Vector3ToNxVec3( Vector3 vector );
				
				static Quaternion NxQuatToQuaternion( NxQuat quat );
				static NxQuat QuaternionNxQuat( Quaternion quat );
				
				static NxPlane PlaneToNxPlane( Plane plane );
				static Plane NxPlaneToPlane( NxPlane plane );
				
				static bool IsMultipleOf( int num, int divisor )
				{
					return ( num % divisor ) == 0;
				}
		};
	};
};