#include "StdAfx.h"
#include "PlaneGeometry.h"
#include <PxPlaneGeometry.h>

using namespace PhysX;

PlaneGeometry::PlaneGeometry()
	: Geometry(GeometryType::Plane)
{
	
}

PxGeometry* PlaneGeometry::ToUnmanaged()
{
	return new PxPlaneGeometry();
}