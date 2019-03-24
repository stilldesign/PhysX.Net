#include "StdAfx.h"
#include "Bounds3.h"
#include "MathUtil.h"

using namespace System;
using namespace System::Globalization;

Bounds3::Bounds3(Vector3 size)
{
	this->Min = -size * 0.5f;
	this->Max = size * 0.5f;
}
Bounds3::Bounds3(Vector3 min, Vector3 max)
{
	this->Min = min;
	this->Max = max;
}
Bounds3::Bounds3(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
{
	this->Min = Vector3(minX, minY, minZ);
	this->Max = Vector3(maxX, maxY, maxZ);
}

PxBounds3 Bounds3::ToUnmanaged(Bounds3 bounds)
{
	PxVec3 min = MathUtil::Vector3ToPxVec3(bounds.Min);
	PxVec3 max = MathUtil::Vector3ToPxVec3(bounds.Max);

	PxBounds3 b(min, max);
	
	return b;
}
Bounds3 Bounds3::ToManaged(PxBounds3 bounds)
{
	PxVec3 center = bounds.getCenter();
	PxVec3 extents = bounds.getExtents();

	return Bounds3(MathUtil::PxVec3ToVector3(center - extents), MathUtil::PxVec3ToVector3(center + extents));
}

void Bounds3::Include(Vector3 vector)
{
	this->Min = Vector3::Min(this->Min, vector);
	this->Max = Vector3::Max(this->Max, vector);
}
void Bounds3::Combine(Bounds3 bounds)
{
	this->Min = Vector3::Min(bounds.Min, this->Min);
	this->Max = Vector3::Max(bounds.Max, this->Max);
}
void Bounds3::BoundsOfOBB(Matrix orientation, Vector3 translation, Vector3 halfDimensions)
{
	float dimX = halfDimensions.X;
	float dimY = halfDimensions.Y;
	float dimZ = halfDimensions.Z;
	
	PxReal x = PxAbs(orientation.M11 * dimX) + PxAbs(orientation.M12 * dimY) + PxAbs(orientation.M13 * dimZ);
	PxReal y = PxAbs(orientation.M21 * dimX) + PxAbs(orientation.M22 * dimY) + PxAbs(orientation.M23 * dimZ);
	PxReal z = PxAbs(orientation.M31 * dimX) + PxAbs(orientation.M32 * dimY) + PxAbs(orientation.M33 * dimZ);
	
	this->Min = Vector3(-x + translation.X, -y + translation.Y, -z + translation.Z);
	this->Max = Vector3(x + translation.X, y + translation.Y, z + translation.Z);
}
void Bounds3::Transform(Matrix orientation, Vector3 translation)
{
	Vector3 center = Vector3::Transform(this->Center, orientation) + translation;
	
	this->BoundsOfOBB(orientation, center, this->Extents);
}
void Bounds3::Scale(float scaleFactor)
{
	this->Min *= scaleFactor;
	this->Max *= scaleFactor;
}
void Bounds3::Expand(float distance)
{
	this->Min -= Vector3(distance, distance, distance);
	this->Max += Vector3(distance, distance, distance);
}

bool Bounds3::Intersects(Bounds3 bounds)
{
	if ((bounds.Min.X > this->Max.X) || (this->Min.X > bounds.Max.X))
		return false;
	
	if ((bounds.Min.Y > this->Max.Y) || (this->Min.Y > bounds.Max.Y))
		return false;
		
	if ((bounds.Min.Z > this->Max.Z) || (this->Min.Z > bounds.Max.Z))
		return false;
	
	return true;
}

bool Bounds3::Contains(Vector3 point)
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
	this->Min = Vector3(0.0f, 0.0f, 0.0f);
	this->Max = Vector3(0.0f, 0.0f, 0.0f);
}

String^ Bounds3::ToString()
{
	Vector3 size = this->Size;
	Vector3 center = this->Center;
	
	return String::Format(CultureInfo::CurrentCulture, "Size: ({0:0.00}; {1:0.00}; {2:0.00}) Center: ({3:0.00}; {4:0.00}; {5:0.00})", size.X, size.Y, size.Z, center.X, center.Y, center.Z);
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
		Single::MinValue, Single::MinValue, Single::MinValue,
		Single::MaxValue, Single::MaxValue, Single::MaxValue
	);
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
	return this->Size.LengthSquared() == 0;
}