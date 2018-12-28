#include "StdAfx.h"
#include "HeightFieldDesc.h"

HeightFieldDesc::HeightFieldDesc()
{
	SetToDefault();
}

bool HeightFieldDesc::IsValid()
{
	auto desc = ToUnmanaged(this);

	bool valid = desc.isValid();

	delete[] desc.samples.data;

	return valid;
}
void HeightFieldDesc::SetToDefault()
{
	NumberOfColumns				= 0;
	NumberOfRows				= 0;
	Format						= HeightFieldFormat::Signed16BitIntegersWithTriangleMaterials;
	Thickness					= -1.0f;
	ConvexEdgeThreshold			= 0.0f;
}

PxHeightFieldDesc HeightFieldDesc::ToUnmanaged(HeightFieldDesc^ desc)
{
	ThrowIfNull(desc, "desc");

	PxStridedData samples;
		samples.data = new PxHeightFieldSample[desc->Samples->Length];
		samples.stride = sizeof(PxHeightFieldSample);

		PxHeightFieldSample* s = (PxHeightFieldSample*)samples.data;
		for (int i = 0; i < desc->Samples->Length; i++)
		{
			auto sample = HeightFieldSample::ToUnmanaged(desc->Samples[i]);

			memcpy(s++, &sample, sizeof(PxHeightFieldSample));
		}

	PxHeightFieldDesc d;
		d.convexEdgeThreshold = desc->ConvexEdgeThreshold;
		d.flags = ToUnmanagedEnum(PxHeightFieldFlag, desc->Flags);
		d.format = ToUnmanagedEnum(PxHeightFieldFormat, desc->Format);
		d.nbColumns = desc->NumberOfColumns;
		d.nbRows = desc->NumberOfRows;
		d.samples = samples;

	return d;
}