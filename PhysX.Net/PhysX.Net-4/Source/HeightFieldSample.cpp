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
HeightFieldSample^ HeightFieldSample::ToManaged(PxHeightFieldSample sample)
{
	auto h = gcnew HeightFieldSample();
		h->Height = sample.height;
		h->MaterialIndex0 = BitAndByte(sample.materialIndex0, sample.materialIndex0.isBitSet());
		h->MaterialIndex1 = BitAndByte(sample.materialIndex1, sample.materialIndex1.isBitSet());

	return h;
}