#include "StdAfx.h"
#include "ClothParticle.h"

ClothParticle::ClothParticle(Vector3 position, float inverseWeight)
{
	Position = position;
	InverseWeight = inverseWeight;
}