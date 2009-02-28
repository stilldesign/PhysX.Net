#include "StdAfx.h"

#include "Soft Body Split Pair Data.h"

using namespace StillDesign::PhysX;

SoftBodySplitPairData::SoftBodySplitPairData()
{
	_data = new NxSoftBodySplitPairData();
	
	_data->numSplitPairsPtr = new NxU32();
}
SoftBodySplitPairData::SoftBodySplitPairData( NxSoftBodySplitPairData data )
{
	_data = new NxSoftBodySplitPairData();
	
	_data->maxSplitPairs = data.maxSplitPairs;
	
	_data->numSplitPairsPtr = new NxU32();
	if( data.numSplitPairsPtr != NULL )
		*_data->numSplitPairsPtr = *data.numSplitPairsPtr;
	
	if( data.splitPairsBegin != NULL )
	{
		_data->splitPairsBegin = new NxSoftBodySplitPair[ data.maxSplitPairs ];
		
		memcpy_s( _data->splitPairsBegin, data.maxSplitPairs * sizeof( NxSoftBodySplitPair ), data.splitPairsBegin, data.maxSplitPairs * sizeof( NxSoftBodySplitPair ) );
	}
	_data->splitPairsByteStride = data.splitPairsByteStride;
}
SoftBodySplitPairData::~SoftBodySplitPairData()
{
	this->!SoftBodySplitPairData();
}
SoftBodySplitPairData::!SoftBodySplitPairData()
{
	if( _data != NULL )
	{
		SAFE_DELETE( _data->numSplitPairsPtr );
		
		SAFE_DELETE( _data->splitPairsBegin );
		
		SAFE_DELETE( _data );
	}
}

void SoftBodySplitPairData::SetToDefault()
{
	_data->setToDefault();
	
	_pairs = nullptr;
}
bool SoftBodySplitPairData::IsValid()
{
	return _data->isValid();
}

array<SoftBodySplitPair>^ SoftBodySplitPairData::SplitPairs::get()
{
	return _pairs;
}