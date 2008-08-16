#include "StdAfx.h"

#include "Implicit Screen Mesh Description.h"
#include "Functions.h"
#include "Math.h"
#include "Mesh Data.h"

#include <NxImplicitScreenMeshDesc.h> 

using namespace StillDesign::PhysX;

ImplicitScreenMeshDescription::ImplicitScreenMeshDescription()
{
	_implicitScreenMesh = new NxImplicitScreenMeshDesc();
		_implicitScreenMesh->projectionMatrix = (float*)malloc( sizeof( float ) * 16 );
		_implicitScreenMesh->triangleWindingPositive = 0;
		
	if( _implicitScreenMesh->projectionMatrix == NULL )
		throw gcnew OutOfMemoryException( "Could allocate memory for a projection matrix" );
	
	SecureZeroMemory( _implicitScreenMesh->projectionMatrix, sizeof( float ) * 16 );
}
ImplicitScreenMeshDescription::~ImplicitScreenMeshDescription()
{
	this->!ImplicitScreenMeshDescription();
}
ImplicitScreenMeshDescription::!ImplicitScreenMeshDescription()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	if( _implicitScreenMesh != NULL )
	{
		free( _implicitScreenMesh->projectionMatrix );
		
		SAFE_DELETE( _implicitScreenMesh );
	}
	
	_meshData = nullptr;
	
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool ImplicitScreenMeshDescription::IsDisposed::get()
{
	return (_implicitScreenMesh == NULL);
}

void ImplicitScreenMeshDescription::SetToDefault()
{
	_implicitScreenMesh->setToDefault();
	
	_meshData = nullptr;
	_userData = nullptr;
}
bool ImplicitScreenMeshDescription::IsValid()
{
	return _implicitScreenMesh->isValid();
}

String^ ImplicitScreenMeshDescription::Name::get()
{
	return Functions::UnmanagedToManagedString( _implicitScreenMesh->name );
}
void ImplicitScreenMeshDescription::Name::set( String^ value )
{
	_implicitScreenMesh->name = Functions::ManagedToUnmanagedString( value );
}

float ImplicitScreenMeshDescription::ScreenSpacing::get()
{
	return _implicitScreenMesh->screenSpacing;
}
void ImplicitScreenMeshDescription::ScreenSpacing::set( float value )
{
	_implicitScreenMesh->screenSpacing = value;
}
int ImplicitScreenMeshDescription::HierarchyLevels::get()
{
	return _implicitScreenMesh->hierarchyLevels;
}
void ImplicitScreenMeshDescription::HierarchyLevels::set( int value )
{
	_implicitScreenMesh->hierarchyLevels = value;
}

float ImplicitScreenMeshDescription::ParticleRadius::get()
{
	return _implicitScreenMesh->particleRadius;
}
void ImplicitScreenMeshDescription::ParticleRadius::set( float value )
{
	_implicitScreenMesh->particleRadius = value;
}

float ImplicitScreenMeshDescription::Threshold::get()
{
	return _implicitScreenMesh->threshold;
}
void ImplicitScreenMeshDescription::Threshold::set( float value )
{
	_implicitScreenMesh->threshold = value;
}

int ImplicitScreenMeshDescription::DepthSmoothing::get()
{
	return _implicitScreenMesh->depthSmoothing;
}
void ImplicitScreenMeshDescription::DepthSmoothing::set( int value )
{
	_implicitScreenMesh->depthSmoothing = value;
}

int ImplicitScreenMeshDescription::SilhouetteSmoothing::get()
{
	return _implicitScreenMesh->silhouetteSmoothing;
}
void ImplicitScreenMeshDescription::SilhouetteSmoothing::set( int value )
{
	_implicitScreenMesh->silhouetteSmoothing = value;
}

int ImplicitScreenMeshDescription::Width::get()
{
	return _implicitScreenMesh->width;
}
void ImplicitScreenMeshDescription::Width::set( int value )
{
	_implicitScreenMesh->width = value;
}

int ImplicitScreenMeshDescription::Height::get()
{
	return _implicitScreenMesh->height;
}
void ImplicitScreenMeshDescription::Height::set( int value )
{
	_implicitScreenMesh->height = value;
}

Matrix ImplicitScreenMeshDescription::ViewProjectionMatrix::get()
{
	Matrix matrix;
		matrix.M11 = _implicitScreenMesh->projectionMatrix[ 0 ];
		matrix.M12 = _implicitScreenMesh->projectionMatrix[ 1 ];
		matrix.M13 = _implicitScreenMesh->projectionMatrix[ 2 ];
		matrix.M14 = _implicitScreenMesh->projectionMatrix[ 3 ];
		matrix.M21 = _implicitScreenMesh->projectionMatrix[ 4 ];
		matrix.M22 = _implicitScreenMesh->projectionMatrix[ 5 ];
		matrix.M23 = _implicitScreenMesh->projectionMatrix[ 6 ];
		matrix.M24 = _implicitScreenMesh->projectionMatrix[ 7 ];
		matrix.M31 = _implicitScreenMesh->projectionMatrix[ 8 ];
		matrix.M32 = _implicitScreenMesh->projectionMatrix[ 9 ];
		matrix.M33 = _implicitScreenMesh->projectionMatrix[ 10 ];
		matrix.M34 = _implicitScreenMesh->projectionMatrix[ 11 ];
		matrix.M41 = _implicitScreenMesh->projectionMatrix[ 12 ];
		matrix.M42 = _implicitScreenMesh->projectionMatrix[ 13 ];
		matrix.M43 = _implicitScreenMesh->projectionMatrix[ 14 ];
		matrix.M44 = _implicitScreenMesh->projectionMatrix[ 15 ];
	
	return matrix;
}
void ImplicitScreenMeshDescription::ViewProjectionMatrix::set( Matrix value )
{
	_implicitScreenMesh->projectionMatrix[ 0 ] = value.M11;
	_implicitScreenMesh->projectionMatrix[ 1 ] = value.M12;
	_implicitScreenMesh->projectionMatrix[ 2 ] = value.M13;
	_implicitScreenMesh->projectionMatrix[ 3 ] = value.M14;
	
	_implicitScreenMesh->projectionMatrix[ 4 ] = value.M21;
	_implicitScreenMesh->projectionMatrix[ 5 ] = value.M22;
	_implicitScreenMesh->projectionMatrix[ 6 ] = value.M23;
	_implicitScreenMesh->projectionMatrix[ 7 ] = value.M24;
	
	_implicitScreenMesh->projectionMatrix[ 8 ] = value.M31;
	_implicitScreenMesh->projectionMatrix[ 9 ] = value.M32;
	_implicitScreenMesh->projectionMatrix[ 10 ] = value.M33;
	_implicitScreenMesh->projectionMatrix[ 11 ] = value.M34;
	
	_implicitScreenMesh->projectionMatrix[ 12 ] = value.M41;
	_implicitScreenMesh->projectionMatrix[ 13 ] = value.M42;
	_implicitScreenMesh->projectionMatrix[ 14 ] = value.M43;
	_implicitScreenMesh->projectionMatrix[ 15 ] = value.M44;
}
Byte ImplicitScreenMeshDescription::TriangleWindingPositive::get()
{
	return _implicitScreenMesh->triangleWindingPositive;
}
void ImplicitScreenMeshDescription::TriangleWindingPositive::set( Byte value )
{
	_implicitScreenMesh->triangleWindingPositive = value;
}
StillDesign::PhysX::MeshData^ ImplicitScreenMeshDescription::MeshData::get()
{
	return _meshData;
}
void ImplicitScreenMeshDescription::MeshData::set( StillDesign::PhysX::MeshData^ value )
{
	if( value == nullptr )
		throw gcnew NullReferenceException( "MeshData Cannot be Null" );
	
	_meshData = value;
	
	_implicitScreenMesh->meshData = *value->UnmanagedPointer;
}

Object^ ImplicitScreenMeshDescription::UserData::get()
{
	return _userData;
}
void ImplicitScreenMeshDescription::UserData::set( Object^ value )
{
	_userData = value;
}

NxImplicitScreenMeshDesc* ImplicitScreenMeshDescription::UnmanagedPointer::get()
{
	return _implicitScreenMesh;
}