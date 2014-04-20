#include "StdAfx.h"

#include "Box.h"
#include "Sphere.h"
#include "Capsule.h"
#include "Bounds.h"
#include "Math.h"

#include "Utilities Library.h"
#include "PhysX Exception.h"

using namespace System;
using namespace StillDesign::PhysX;

UtilitiesLibrary::UtilitiesLibrary()
{
	_library = NxGetUtilLib();
	
	if( _library == NULL )
		throw gcnew PhysXException( "Utilities library failed to be created. Possible cause: Physics core not created." );
}
UtilitiesLibrary::~UtilitiesLibrary()
{
	this->!UtilitiesLibrary();
}
UtilitiesLibrary::!UtilitiesLibrary()
{
	
}

bool UtilitiesLibrary::BoxContainsPoint( StillDesign::PhysX::Box box, Vector3 point )
{
	return _library->NxBoxContainsPoint( (NxBox)box, Math::Vector3ToNxVec3( point ) );
}
StillDesign::PhysX::Box UtilitiesLibrary::CreateBox( Bounds3 AABB, Matrix transform )
{
	NxBox b;
	_library->NxCreateBox( b, (NxBounds3)AABB, StillDesign::PhysX::Math::MatrixToMat34( transform ) );
	
	return (Box)b;
}

UtilitiesLibrary::BoxPlanesResult^ UtilitiesLibrary::ComputeBoxPlanes( StillDesign::PhysX::Box box )
{
	NxPlane outputPlanes[ 6 ];
	
	bool success = _library->NxComputeBoxPlanes( (NxBox)box, &outputPlanes[0] );
	
	if( success == true )
	{
		array< Plane >^ planes = gcnew array< Plane >( 6 );
		
		for( int x = 0; x < 6; x++ )
		{
			planes[ x ] = Plane( outputPlanes[ x ].normal.x, outputPlanes[ x ].normal.y, outputPlanes[ x ].normal.z, outputPlanes[ x ].d );
		}
		
		return gcnew UtilitiesLibrary::BoxPlanesResult( true, planes );
	}else{
		return gcnew UtilitiesLibrary::BoxPlanesResult( false, nullptr );
	}
}
UtilitiesLibrary::BoxPointsResult^ UtilitiesLibrary::ComputeBoxPoints( StillDesign::PhysX::Box box )
{
	NxVec3* outputPoints = new NxVec3[ 8 ];
	
	bool success = _library->NxComputeBoxPoints( (NxBox)box, outputPoints );
	
	BoxPointsResult^ result;
	if( success == true )
	{
		array<Vector3>^ points = gcnew array<Vector3>( 8 );
		
		for( int x = 0; x < 8; x++ )
		{
			points[ x ] = Vector3( outputPoints[ x ].x, outputPoints[ x ].y, outputPoints[ x ].z );
		}
		
		result = gcnew BoxPointsResult( true, points );
	}else{
		result = gcnew BoxPointsResult( false, nullptr );
	}
	
	delete[] outputPoints;
	
	return result;
}
UtilitiesLibrary::BoxNormalsResult^ UtilitiesLibrary::ComputeBoxVertexNormals( StillDesign::PhysX::Box box )
{
	NxVec3* normals = new NxVec3[ 8 ];
	
	bool success = _library->NxComputeBoxVertexNormals( (NxBox)box, normals );
	
	BoxNormalsResult^ result;
	if( success == true )
	{
		array<Vector3>^ n = gcnew array<Vector3>( 8 );
		
		for( int x = 0; x < 8; x++ )
		{
			n[ x ] = Vector3( normals[ x ].x, normals[ x ].y, normals[ x ].z );
		}
		
		result = gcnew BoxNormalsResult( true, n );
	}else{
		result = gcnew BoxNormalsResult( false, nullptr );
	}
	
	delete[] normals;
	
	return result;
}
array<int>^ UtilitiesLibrary::GetBoxEdges()
{
	const NxU32* e = _library->NxGetBoxEdges();
	
	array<int>^ edges = gcnew array<int>( 12 );
	for( int x = 0; x < 12; x++ )
	{
		edges[ x ] = e[ x ];
	}
	
	return edges;
}
//array<int>^ UtilitiesLibrary::GetBoxEdgesAxes()
//{
//	throw gcnew NotImplementedException();
//}
//array<int>^ UtilitiesLibrary::GetBoxTriangles()
//{
//	throw gcnew NotImplementedException();
//}
//array<Vector3>^ UtilitiesLibrary::GetBoxLocalEdgeNormals()
//{
//	throw gcnew NotImplementedException();
//}

Vector3 UtilitiesLibrary::ComputeBoxWorldEdgeNormal( StillDesign::PhysX::Box box, unsigned int edgeIndex )
{
	NxVec3 normal;
	
	_library->NxComputeBoxWorldEdgeNormal( (NxBox)box, edgeIndex, normal );
	
	return Math::NxVec3ToVector3( normal );
}

Capsule UtilitiesLibrary::ComputeCapsuleAroundBox( StillDesign::PhysX::Box box )
{
	NxCapsule capsule;
	
	_library->NxComputeCapsuleAroundBox( (NxBox)box, capsule );
	
	return (Capsule)capsule;
}

array<int>^ UtilitiesLibrary::GetBoxQuads()
{
	throw gcnew NotImplementedException();
}
array<int>^ UtilitiesLibrary::BoxVertexToQuad( int vertexIndex )
{
	throw gcnew NotImplementedException();
}
StillDesign::PhysX::Box UtilitiesLibrary::ComputeBoxAroundCapsule( Capsule capsule )
{
	NxBox box;
	
	_library->NxComputeBoxAroundCapsule( (NxCapsule)capsule, box );
	
	return (StillDesign::PhysX::Box)box;
}

void UtilitiesLibrary::SetFPUPrecision24()
{
	_library->NxSetFPUPrecision24();
}
void UtilitiesLibrary::SetFPUPrecision53()
{
	_library->NxSetFPUPrecision53();
}
void UtilitiesLibrary::SetFPUPrecision64()
{
	_library->NxSetFPUPrecision64();
}
void UtilitiesLibrary::SetFPURoundingChop()
{
	_library->NxSetFPURoundingChop();
}
void UtilitiesLibrary::SetFPURoundingUp()
{
	_library->NxSetFPURoundingUp();
}
void UtilitiesLibrary::SetFPURoundingDown()
{
	_library->NxSetFPURoundingDown();
}
void UtilitiesLibrary::SetFPURoundingNear()
{
	_library->NxSetFPURoundingNear();
}
void UtilitiesLibrary::SetFPUExceptions( bool enable )
{
	_library->NxSetFPUExceptions( enable );
}
int UtilitiesLibrary::IntegerChop( float value )
{
	return _library->NxIntChop( value );
}
int UtilitiesLibrary::IntegerFloor( float value )
{
	return _library->NxIntFloor( value );
}
int UtilitiesLibrary::IntegerCeiling( float value )
{
	return _library->NxIntCeil( value );
}

Matrix UtilitiesLibrary::FindRotationMatrix( Vector3 x, Vector3 b )
{
	NxMat33 matrix;
	
	_library->NxFindRotationMatrix( Math::Vector3ToNxVec3( x ), Math::Vector3ToNxVec3( b ), matrix );
	
	return Math::Mat33ToMatrix( &matrix );
}
Bounds3 UtilitiesLibrary::ComputeBounds( array<Vector3>^ vertices )
{
	if( vertices == nullptr )
		throw gcnew ArgumentNullException( "vertices" );
	
	NxVec3* v = (NxVec3*)malloc( sizeof( NxVec3 ) * vertices->Length );
	if( v == NULL )
		throw gcnew PhysXException( "Cannot allocate memory for vertices" );
	
	pin_ptr<Vector3> b = &vertices[ 0 ];
	memcpy_s( v, sizeof( NxVec3 ) * vertices->Length, b, sizeof( Vector3 ) * vertices->Length );
	
	NxVec3 min, max;
	_library->NxComputeBounds( min, max, vertices->Length, v );
	
	v = NULL;
	free( v );
	
	NxBounds3 bounds;
		bounds.set( min, max );
	
	return (Bounds3)bounds;
}
System::UInt32 UtilitiesLibrary::CRC32( array<System::Byte>^ buffer )
{
	if( buffer == nullptr )
		throw gcnew ArgumentNullException( "buffer" );
	
	BYTE* b = (BYTE*)malloc( sizeof( BYTE ) * buffer->Length );
	for( int x = 0; x < buffer->Length; x++ )
	{
		b[ x ] = buffer[ x ];
	}
	
	NxU32 crc = _library->NxCrc32( b, buffer->Length );
	
	free( b );
	b = NULL;
	
	return crc;
}

// Shape Densities and Mass
// Box
float UtilitiesLibrary::ComputeBoxDensity( Vector3 size, float mass )
{
	return _library->NxComputeBoxDensity( NxVec3( size.X, size.Y, size.Z ) * 2.0f, mass );
}
float UtilitiesLibrary::ComputeBoxMass( Vector3 size, float density )
{
	return _library->NxComputeBoxMass( NxVec3( size.X, size.Y, size.Z ) * 2.0f, density );
}
Vector3 UtilitiesLibrary::ComputeBoxInteriaTensor( Vector3 diagonalInertia, float mass, Vector3 size )
{
	NxVec3 i;
	_library->NxComputeBoxInertiaTensor( i, mass, size.X, size.Y, size.Z );
	
	return Math::NxVec3ToVector3( i );
}

// Cone
float UtilitiesLibrary::ComputeConeDensity( float radius, float length, float mass )
{
	return _library->NxComputeConeDensity( radius, length, mass );
}
float UtilitiesLibrary::ComputeConeMass( float radius, float length, float density )
{
	return _library->NxComputeConeMass( radius, length, density );
}

// Cylinder
float UtilitiesLibrary::ComputeCylinderDensity( float radius, float length, float mass )
{
	return _library->NxComputeCylinderDensity( radius, length, mass );
}
float UtilitiesLibrary::ComputeCylinderMass( float radius, float length, float density )
{
	return _library->NxComputeCylinderMass( radius, length, density );
}

// Ellipse
float UtilitiesLibrary::ComputeEllipsoidDensity( Vector3 radius, float mass )
{
	return _library->NxComputeEllipsoidDensity( NxVec3( radius.X, radius.Y, radius.Z ), mass );
}
float UtilitiesLibrary::ComputeEllipsoidMass( Vector3 radius, float density )
{
	return _library->NxComputeEllipsoidMass( NxVec3( radius.X, radius.Y, radius.Z ), density );
}

// Sphere
float UtilitiesLibrary::ComputeSphereDensity( float radius, float mass )
{
	return _library->NxComputeSphereDensity( radius, mass );
}
float UtilitiesLibrary::ComputeSphereMass( float radius, float density )
{
	return _library->NxComputeSphereMass( radius, density );
}

UtilitiesLibrary::SphereGenerationResult^ UtilitiesLibrary::ComputeSphere( array<Vector3>^ vertices )
{
	ThrowIfNull( vertices, "vertices" );
	
	NxSphere sphere;
	NxVec3* v = new NxVec3[ vertices->Length ];
	
	for( int x = 0; x < vertices->Length; x++ )
	{
		v[ x ] = Math::Vector3ToNxVec3( vertices[ x ] );
	}
	
	NxBSphereMethod method = _library->NxComputeSphere( sphere, vertices->Length, v );
	
	delete[] v;
	
	return gcnew SphereGenerationResult( (SphereGenerationMethod)method, (StillDesign::PhysX::Sphere)sphere );
}
Sphere UtilitiesLibrary::MergeSpheres( Sphere sphere0, Sphere sphere1 )
{
	NxSphere sphere;
	_library->NxMergeSpheres( sphere, (NxSphere)sphere0, (NxSphere)sphere1 );
	
	return (Sphere)sphere;
}

Vector3 UtilitiesLibrary::ComputeSphereInertiaTensor( float mass, float radius, bool hollow )
{
	NxVec3 it;
	
	_library->NxComputeSphereInertiaTensor( it, mass, radius, hollow );
	
	return Math::NxVec3ToVector3( it );
}

bool UtilitiesLibrary::IsBoxAInsideBoxB( StillDesign::PhysX::Box boxA, StillDesign::PhysX::Box boxB )
{
	return _library->NxIsBoxAInsideBoxB( (NxBox)boxA, (NxBox)boxB );
}

//

UtilitiesLibrary::BoxPlanesResult::BoxPlanesResult( bool successful, array<Plane>^ planes )
{
	_successful = successful;
	_planes = planes;
}
bool UtilitiesLibrary::BoxPlanesResult::Successful::get()
{
	return _successful;
}
array< Plane >^ UtilitiesLibrary::BoxPlanesResult::Planes::get()
{
	return _planes;
}

//

UtilitiesLibrary::BoxPointsResult::BoxPointsResult( bool successful, array<Vector3>^ points ) 
{
	_successful = successful;
	_points = points;
}
bool UtilitiesLibrary::BoxPointsResult::Successful::get()
{
	return _successful;
}
array<Vector3>^ UtilitiesLibrary::BoxPointsResult::Points::get()
{
	return _points;
}

//

UtilitiesLibrary::BoxNormalsResult::BoxNormalsResult( bool successful, array<Vector3>^ normals ) 
{
	_successful = successful;
	_normals = normals;
}
bool UtilitiesLibrary::BoxNormalsResult::Successful::get()
{
	return _successful;
}
array<Vector3>^ UtilitiesLibrary::BoxNormalsResult::Normals::get()
{
	return _normals;
}

//

UtilitiesLibrary::SphereGenerationResult::SphereGenerationResult( SphereGenerationMethod generationMethod, StillDesign::PhysX::Sphere sphere )
{
	_generationMethod = generationMethod;
	
	_sphere = sphere;
}

SphereGenerationMethod UtilitiesLibrary::SphereGenerationResult::GenerationMethod::get()
{
	return _generationMethod;
}
StillDesign::PhysX::Sphere UtilitiesLibrary::SphereGenerationResult::Sphere::get()
{
	return _sphere;
}