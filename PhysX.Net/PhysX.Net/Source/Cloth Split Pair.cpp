#include "StdAfx.h"
#include "Cloth Split Pair.h"

using namespace StillDesign::PhysX;

ClothSplitPair ClothSplitPair::FromUnmanaged( NxClothSplitPair pair )
{
	ClothSplitPair p;
		p.EdgeIndex0 = pair.edgeIndex0;
		p.EdgeIndex1 = pair.edgeIndex1;
		p.TriangleIndex0 = pair.triangleIndex0;
		p.TriangleIndex1 = pair.triangleIndex1;
	
	return p;
}