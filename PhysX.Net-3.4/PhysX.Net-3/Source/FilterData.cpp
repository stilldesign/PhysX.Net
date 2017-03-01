#include "StdAfx.h"
#include "FilterData.h"

FilterData::FilterData(unsigned int word0, unsigned int word1, unsigned int word2, unsigned int word3)
{
	Word0 = word0;
	Word1 = word1;
	Word2 = word2;
	Word3 = word3;
}

PxFilterData FilterData::ToUnmanaged(FilterData data)
{
	PxFilterData d;
		d.word0 = data.Word0;
		d.word1 = data.Word1;
		d.word2 = data.Word2;
		d.word3 = data.Word3;

	return d;
}
FilterData FilterData::ToManaged(PxFilterData data)
{
	FilterData d;
		d.Word0 = data.word0;
		d.Word1 = data.word1;
		d.Word2 = data.word2;
		d.Word3 = data.word3;

	return d;
}

void FilterData::SetToDefault()
{
	Word0 = 0;
	Word1 = 0;
	Word2 = 0;
	Word3 = 0;
}