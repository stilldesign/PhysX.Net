#include "StdAfx.h"
#include "DebugTriangle.h"

DebugTriangle::DebugTriangle(Vector3 point0, int color0, Vector3 point1, int color1, Vector3 point2, int color2)
{
	Point0 = point0;
	Color0 = color0;

	Point1 = point1;
	Color1 = color1;

	Point2 = point2;
	Color2 = color2;
}