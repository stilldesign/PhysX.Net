#include "StdAfx.h"
#include "HullPolygon.h"

PxHullPolygon HullPolygon::ToUnmanaged(HullPolygon^ hullPolygon)
{
	PxHullPolygon hp;
		hp.mIndexBase = hullPolygon->IndexBase;
		hp.mNbVerts = hullPolygon->NumberOfVertices;
		hp.mPlane[0] = hullPolygon->Plane.Normal.X;
		hp.mPlane[1] = hullPolygon->Plane.Normal.Y;
		hp.mPlane[2] = hullPolygon->Plane.Normal.Z;
		hp.mPlane[3] = hullPolygon->Plane.D;

	return hp;
}
HullPolygon^ HullPolygon::ToManaged(PxHullPolygon hullPolygon)
{
	HullPolygon^ hp = gcnew HullPolygon();
		hp->IndexBase = hullPolygon.mIndexBase;
		hp->NumberOfVertices = hullPolygon.mNbVerts;
		hp->Plane = System::Numerics::Plane(hullPolygon.mPlane[0], hullPolygon.mPlane[1], hullPolygon.mPlane[2], hullPolygon.mPlane[3]);

	return hp;
}