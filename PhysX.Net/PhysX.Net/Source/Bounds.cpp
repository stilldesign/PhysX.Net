#include "StdAfx.h"

#include "Bounds.h"
#include "Math.h"

using namespace System::Globalization;
using namespace StillDesign::PhysX;
UsingFrameworkNamespace

Bounds3::Bounds3( float minX, float minY, float minZ, float maxX, float maxY, float maxZ )
{
	_min = Vector3( minX, minY, minZ );
	_max = Vector3( maxX, maxY, maxZ );
}
Bounds3::Bounds3( Vector3 min, Vector3 max )
{
	_min = min;
	_max = max;
}

Bounds3::operator NxBounds3( Bounds3 bounds )
{
	NxBounds3 b;
		b.min = Math::Vector3ToNxVec3( bounds.Min );
		b.max = Math::Vector3ToNxVec3( bounds.Max );
	
	return b;
}
Bounds3::operator Bounds3( NxBounds3 bounds )
{
	return Bounds3( Math::NxVec3ToVector3( bounds.min ), Math::NxVec3ToVector3( bounds.max ) );
}

void Bounds3::Include( Vector3 vector )
{
#if GRAPHICS_MDX
	this->Min = Vector3::Minimize( this->Min, vector );
	this->Max = Vector3::Maximize( this->Max, vector );
#elif GRAPHICS_XNA2
	this->Min = Vector3::Min( this->Min, vector );
	this->Max = Vector3::Max( this->Max, vector );
#elif GRAPHICS_XNA3
	this->Min = Vector3::Min( this->Min, vector );
	this->Max = Vector3::Max( this->Max, vector );
#elif GRAPHICS_SLIMDX
	this->Min = Vector3::Minimize( this->Min, vector );
	this->Max = Vector3::Maximize( this->Max, vector );
#else
	#error No Graphics Target Specified
#endif
}
void Bounds3::Combine( Bounds3 bounds )
{
#if GRAPHICS_MDX
	this->Min = Vector3::Minimize( bounds.Min, this->Min );
	this->Max = Vector3::Maximize( bounds.Max, this->Max );
#elif GRAPHICS_XNA2
	this->Min = Vector3::Min( bounds.Min, this->Min );
	this->Max = Vector3::Max( bounds.Max, this->Max );
#elif GRAPHICS_XNA3
	this->Min = Vector3::Min( bounds.Min, this->Min );
	this->Max = Vector3::Max( bounds.Max, this->Max );
#elif GRAPHICS_SLIMDX
	this->Min = Vector3::Minimize( bounds.Min, this->Min );
	this->Max = Vector3::Maximize( bounds.Max, this->Max );
#else
	#error No Graphics Target Specified
#endif
}
void Bounds3::BoundsOfOBB( Matrix orientation, Vector3 translation, Vector3 halfDimensions )
{
	float dimX = halfDimensions.X;
	float dimY = halfDimensions.Y;
	float dimZ = halfDimensions.Z;
	
	NxReal x = NxMath::abs(orientation.M11 * dimX) + NxMath::abs(orientation.M12 * dimY) + NxMath::abs(orientation.M13 * dimZ);
	NxReal y = NxMath::abs(orientation.M21 * dimX) + NxMath::abs(orientation.M22 * dimY) + NxMath::abs(orientation.M23 * dimZ);
	NxReal z = NxMath::abs(orientation.M31 * dimX) + NxMath::abs(orientation.M32 * dimY) + NxMath::abs(orientation.M33 * dimZ);
	
	this->Min = Vector3( -x + translation.X, -y + translation.Y, -z + translation.Z );
	this->Max = Vector3( x + translation.X, y + translation.Y, z + translation.Z );
}
void Bounds3::Transform( Matrix orientation, Vector3 translation )
{
#if GRAPHICS_MDX
	Vector3 center = Vector3::TransformCoordinate( this->Center, orientation ) + translation;
#elif GRAPHICS_XNA2
	Vector3 center = Vector3::Transform( this->Center, orientation ) + translation;
#elif GRAPHICS_XNA3
	Vector3 center = Vector3::Transform( this->Center, orientation ) + translation;
#elif GRAPHICS_SLIMDX
	Vector3 center = Vector3::TransformCoordinate( this->Center, orientation ) + translation;
#else
	#error No Graphics Target Specified
#endif
	
	this->BoundsOfOBB( orientation, center, this->Extents );
}
void Bounds3::Scale( float scaleFactor )
{
	this->Min *= scaleFactor;
	this->Max *= scaleFactor;
}
void Bounds3::Expand( float distance )
{
	this->Min -= Vector3( distance, distance, distance );
	this->Max += Vector3( distance, distance, distance );
}

bool Bounds3::Intersects( Bounds3 bounds )
{
	if((bounds.Min.X > this->Max.X) || (this->Min.X > bounds.Max.X))
		return false;
	
	if ((bounds.Min.Y > this->Max.Y) || (this->Min.Y > bounds.Max.Y))
		return false;
		
	if ((bounds.Min.Z > this->Max.Z) || (this->Min.Z > bounds.Max.Z))
		return false;
	
	return true;
}

bool Bounds3::Contains( Vector3 point )
{
	if ((point.X < this->Min.X) || (point.X > this->Max.X))
		return false;
	
	if ((point.Y < this->Min.Y) || (point.Y > this->Max.Y))
		return false;
	
	if ((point.Z < this->Min.Z) || (point.Z > this->Max.Z))
		return false;
	
	return true;
}

void Bounds3::SetToEmpty()
{
	_min = Vector3( 0.0f, 0.0f, 0.0f );
	_max = Vector3( 0.0f, 0.0f, 0.0f );
}

String^ Bounds3::ToString()
{
	Vector3 size = this->Size;
	Vector3 center = this->Center;
	
	return String::Format( CultureInfo::CurrentCulture, "Size: ( {0:0.00}; {1:0.00}; {2:0.00} ) Center: ( {3:0.00}; {4:0.00}; {5:0.00} )", size.X, size.Y, size.Z, center.X, center.Y, center.Z );
}

//

Bounds3 Bounds3::Empty::get()
{
	return Bounds3();
}
Bounds3 Bounds3::Extremes::get()
{
	return Bounds3
	(
		Single::MaxValue, Single::MaxValue, Single::MaxValue, 
		Single::MinValue, Single::MinValue, Single::MinValue
	);
}

Vector3 Bounds3::Min::get()
{
	return _min;
}
void Bounds3::Min::set( Vector3 value )
{
	_min = value;
}

Vector3 Bounds3::Max::get()
{
	return _max;
}
void Bounds3::Max::set( Vector3 value )
{
	_max = value;
}

Vector3 Bounds3::Center::get()
{
	return this->Min + this->Size * 0.5f;
}
Vector3 Bounds3::Size::get()
{
	return this->Max - this->Min;
}
Vector3 Bounds3::Extents::get()
{
	return this->Size * 0.5f;
}

bool Bounds3::IsEmpty::get()
{
#if GRAPHICS_MDX
	return this->Size.LengthSq() == 0;
#elif GRAPHICS_XNA2
	return this->Size.LengthSquared() == 0;
#elif GRAPHICS_XNA3
	return this->Size.LengthSquared() == 0;
#elif GRAPHICS_SLIMDX
	return this->Size.LengthSquared() == 0;
#else
	#error No Graphics Target Specified
#endif
}