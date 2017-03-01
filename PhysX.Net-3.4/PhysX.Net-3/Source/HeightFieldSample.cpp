#include "StdAfx.h"
#include "HeightFieldSample.h"

HeightFieldSample::HeightFieldSample()
{
	
}

PxHeightFieldSample HeightFieldSample::ToUnmanaged(HeightFieldSample^ sample)
{
	PxHeightFieldSample s;
		s.height = sample->Height;
		s.materialIndex0 = BitAndByte::ToUnmanaged(sample->MaterialIndex0);
		s.materialIndex1 = BitAndByte::ToUnmanaged(sample->MaterialIndex1);

	return s;
}