#pragma once

#if GRAPHICS_SLIMDX
	#define Vector3_Minimize( v1, v2 ) Vector3::Minimize( v1, v2 )
	#define Vector3_Maximize( v1, v2 ) Vector3::Maximize( v1, v2 )
	#define Vector3_Transform( p, m ) Vector3::TransformCoordinate( p, m )
	#define Vector3_LengthSquared( v ) v.LengthSquared()
	
	#define Matrix_CreateTranslation( translation ) Matrix::Translation( translation )
	
	#define Plane_GetNormal( p ) p.Normal
	#define _PlaneToNxPlane( p ) NxPlane( p.Normal.X, p.Normal.Y, p.Normal.Z, p.D );
#elif GRAPHICS_XNA31
	#define Vector3_Minimize( v1, v2 ) Vector3::Min( v1, v2 )
	#define Vector3_Maximize( v1, v2 ) Vector3::Max( v1, v2 )
	#define Vector3_Transform( p, m ) Vector3::Transform( p, m )
	#define Vector3_LengthSquared( v ) v.LengthSquared()
	
	#define Matrix_CreateTranslation( translation ) Matrix::CreateTranslation( translation )
	
	#define Plane_GetNormal( p ) p.Normal
	#define _PlaneToNxPlane( p ) NxPlane( p.Normal.X, p.Normal.Y, p.Normal.Z, p.D )
#else
		NoGraphicsTargetSpecified
#endif