#include "StdAfx.h"
#include "Cloth Split Pair Data.h"
#include "Cloth Split Pair.h"
#include <NxClothDesc.h> 

using namespace StillDesign::PhysX;

ClothSplitPairData::ClothSplitPairData( NxClothSplitPairData* splitPairData )
{
	_data = splitPairData;
		_data->numSplitPairsPtr = new NxU32();
		_data->splitPairsByteStride = sizeof(NxClothSplitPair);
	
	this->MaximumSplitPairs = 0;
}
ClothSplitPairData::~ClothSplitPairData()
{
	this->!ClothSplitPairData();
}
ClothSplitPairData::!ClothSplitPairData()
{
	if( _data != NULL )
	{
		// We allocated the number of pairs memory, so delete it
		//delete _data->numSplitPairsPtr;
		
		// The data object was passed into us, so just set it to NULL without deleting it
		_data = NULL;
	}
}

array<ClothSplitPair>^ ClothSplitPairData::GetSplitPairs()
{
	if( _data->splitPairsBegin == NULL )
		throw gcnew InvalidOperationException( "Cannot get pair data as the memory has not been allocated" );
	
	int numOfPairs = this->NumberOfSplitPairs;
	
	array<ClothSplitPair>^ pairs = gcnew array<ClothSplitPair>( numOfPairs );
	
	for( int x = 0; x < numOfPairs; x++ )
	{
		pairs[ x ] = ClothSplitPair::FromUnmanaged( _data->splitPairsBegin[ x ] );
	}
	
	return pairs;
}

int ClothSplitPairData::MaximumSplitPairs::get()
{
	return _data->maxSplitPairs;
}
void ClothSplitPairData::MaximumSplitPairs::set( int value )
{
	_data->maxSplitPairs = value;
	
	// Delete the existing data
	if( _data->splitPairsBegin != NULL )
		free( _data->splitPairsBegin );
	
	_data->splitPairsBegin = (NxClothSplitPair*)malloc( value * sizeof( NxClothSplitPair ) );
}

int ClothSplitPairData::NumberOfSplitPairs::get()
{
	return *_data->numSplitPairsPtr;
}