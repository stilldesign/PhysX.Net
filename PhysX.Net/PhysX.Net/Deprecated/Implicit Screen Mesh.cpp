#include "StdAfx.h"

#include "Implicit Screen Mesh.h"
#include "Functions.h"
#include "Math.h"
#include "Mesh Data.h"
#include "Scene.h"

#include <NxImplicitScreenMesh.h> 

using namespace StillDesign::PhysX;

ImplicitScreenMesh::ImplicitScreenMesh( NxImplicitScreenMesh* implicitScreenMesh, StillDesign::PhysX::Fluid^ fluid ) : Dependency( fluid )
{
	_implicitScreenMesh = implicitScreenMesh;
	_fluid = fluid;
	
	_projectionMatrix = (float*)malloc( sizeof( float ) * 16 );
	_implicitScreenMesh->setProjectionMatrix( _projectionMatrix );
	const float* q = _implicitScreenMesh->getProjectionMatrix();
	
	_implicitScreenMesh->setProjectionMatrix( &_projectionMatrix[ 0 ] );
	q = _implicitScreenMesh->getProjectionMatrix();
	
	ZeroMemory( &_projectionMatrix[ 0 ], sizeof( float ) * 16 );
}
ImplicitScreenMesh::~ImplicitScreenMesh()
{
	this->!ImplicitScreenMesh();
}
ImplicitScreenMesh::!ImplicitScreenMesh()
{
	if( this->IsDisposed == true )
		return;
	
	onDisposing( this, nullptr );
	
	_fluid->UnmanagedPointer->releaseScreenSurfaceMesh( *_implicitScreenMesh );
	
	_implicitScreenMesh = NULL;
	
	_fluid = nullptr;
	_meshData = nullptr;
	
	_userData = nullptr;
	
	onDisposed( this, nullptr );
}
bool ImplicitScreenMesh::IsDisposed::get()
{
	return (_implicitScreenMesh == NULL);
}

ImplicitScreenMesh^ ImplicitScreenMesh::FromUnmanagedPointer( NxImplicitScreenMesh* implicitScreenMesh, StillDesign::PhysX::Fluid^ fluid )
{
	return gcnew ImplicitScreenMesh( implicitScreenMesh, fluid );
}

bool ImplicitScreenMesh::GenerateMesh()
{
	return _implicitScreenMesh->generateMesh();
}
bool ImplicitScreenMesh::GetMesh()
{
	bool r = _implicitScreenMesh->getMesh();
	NxMeshData d = _implicitScreenMesh->getMeshData();
	
	return r;
}
bool ImplicitScreenMesh::IsMeshGenerationDone()
{
	return _implicitScreenMesh->generateMeshIsDone();
}

StillDesign::PhysX::Fluid^ ImplicitScreenMesh::Fluid::get()
{
	return _fluid;
}

String^ ImplicitScreenMesh::Name::get()
{
	return Functions::UnmanagedToManagedString( _implicitScreenMesh->getName() );
}
void ImplicitScreenMesh::Name::set( String^ value )
{
	_implicitScreenMesh->setName( Functions::ManagedToUnmanagedString( value ) );
}

float ImplicitScreenMesh::ScreenSpacing::get()
{
	return _implicitScreenMesh->getScreenSpacing();
}
void ImplicitScreenMesh::ScreenSpacing::set( float value )
{
	_implicitScreenMesh->setScreenSpacing( value );
}
int ImplicitScreenMesh::HierarchyLevels::get()
{
	return _implicitScreenMesh->getHierarchyLevels();
}
void ImplicitScreenMesh::HierarchyLevels::set( int value )
{
	_implicitScreenMesh->setHierarchyLevels( value );
}

float ImplicitScreenMesh::ParticleRadius::get()
{
	return _implicitScreenMesh->getParticleRadius();
}
void ImplicitScreenMesh::ParticleRadius::set( float value )
{
	_implicitScreenMesh->setParticleRadius( value );
}

float ImplicitScreenMesh::Threshold::get()
{
	return _implicitScreenMesh->getThreshold();
}
void ImplicitScreenMesh::Threshold::set( float value )
{
	_implicitScreenMesh->setThreshold( value );
}

int ImplicitScreenMesh::DepthSmoothing::get()
{
	return _implicitScreenMesh->getDepthSmoothing();
}
void ImplicitScreenMesh::DepthSmoothing::set( int value )
{
	_implicitScreenMesh->setDepthSmoothing( value );
}

int ImplicitScreenMesh::SilhouetteSmoothing::get()
{
	return _implicitScreenMesh->getSilhouetteSmoothing();
}
void ImplicitScreenMesh::SilhouetteSmoothing::set( int value )
{
	_implicitScreenMesh->setSilhouetteSmoothing( value );
}

int ImplicitScreenMesh::Width::get()
{
	return _implicitScreenMesh->getWindowWidth();
}
void ImplicitScreenMesh::Width::set( int value )
{
	_implicitScreenMesh->setWindowWidth( value );
}

int ImplicitScreenMesh::Height::get()
{
	return _implicitScreenMesh->getWindowHeight();
}
void ImplicitScreenMesh::Height::set( int value )
{
	_implicitScreenMesh->setWindowHeight( value );
}

Matrix ImplicitScreenMesh::ViewProjectionMatrix::get()
{
	//return Math::Mat44ToMatrix( _projectionMatrix );
	
	const float* p = _implicitScreenMesh->getProjectionMatrix();
	
	Matrix matrix;
		matrix.M11 = p[ 0 ];
		matrix.M12 = p[ 1 ];
		matrix.M13 = p[ 2 ];
		matrix.M14 = p[ 3 ];
		matrix.M21 = p[ 4 ];
		matrix.M22 = p[ 5 ];
		matrix.M23 = p[ 6 ];
		matrix.M24 = p[ 7 ];
		matrix.M31 = p[ 8 ];
		matrix.M32 = p[ 9 ];
		matrix.M33 = p[ 10 ];
		matrix.M34 = p[ 11 ];
		matrix.M41 = p[ 12 ];
		matrix.M42 = p[ 13 ];
		matrix.M43 = p[ 14 ];
		matrix.M44 = p[ 15 ];
	
	return matrix;
}
void ImplicitScreenMesh::ViewProjectionMatrix::set( Matrix value )
{
	//Math::MatrixToMat44( value, _projectionMatrix );
	
	_projectionMatrix[ 0 ] = value.M11;
	_projectionMatrix[ 1 ] = value.M12;
	_projectionMatrix[ 2 ] = value.M13;
	_projectionMatrix[ 3 ] = value.M14;
	
	_projectionMatrix[ 4 ] = value.M21;
	_projectionMatrix[ 5 ] = value.M22;
	_projectionMatrix[ 6 ] = value.M23;
	_projectionMatrix[ 7 ] = value.M24;
	
	_projectionMatrix[ 8 ] = value.M31;
	_projectionMatrix[ 9 ] = value.M32;
	_projectionMatrix[ 10 ] = value.M33;
	_projectionMatrix[ 11 ] = value.M34;
	
	_projectionMatrix[ 12 ] = value.M41;
	_projectionMatrix[ 13 ] = value.M42;
	_projectionMatrix[ 14 ] = value.M43;
	_projectionMatrix[ 15 ] = value.M44;
	
	_implicitScreenMesh->setProjectionMatrix( _projectionMatrix );
}
Byte ImplicitScreenMesh::TriangleWindingPositive::get()
{
	return _implicitScreenMesh->getTriangleWinding();
}
void ImplicitScreenMesh::TriangleWindingPositive::set( Byte value )
{
	_implicitScreenMesh->setTriangleWinding( value );
}
StillDesign::PhysX::MeshData^ ImplicitScreenMesh::MeshData::get()
{
	return _meshData;
}
void ImplicitScreenMesh::MeshData::set( StillDesign::PhysX::MeshData^ value )
{
	if( value == nullptr || value->UnmanagedPointer == NULL )
		throw gcnew ArgumentNullException( "Mesh data cannot be null" );
	
	_meshData = value;
	
	_implicitScreenMesh->setMeshData( *value->UnmanagedPointer );
}

Object^ ImplicitScreenMesh::UserData::get()
{
	return _userData;
}
void ImplicitScreenMesh::UserData::set( Object^ value )
{
	_userData = value;
}

NxImplicitScreenMesh* ImplicitScreenMesh::UnmanagedPointer::get()
{
	return _implicitScreenMesh;
}