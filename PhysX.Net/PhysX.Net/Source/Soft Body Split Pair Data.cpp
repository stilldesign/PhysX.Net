#include "StdAfx.h"

#include "Soft Body Split Pair Data.h"

using namespace StillDesign::PhysX;

SoftBodySplitPairData::SoftBodySplitPairData()
	: BufferData( true, true )
{
	_data = new NxSoftBodySplitPairData();
	
	_data->numSplitPairsPtr = new NxU32();

}
SoftBodySplitPairData^ SoftBodySplitPairData::FromUnmanaged( NxSoftBodySplitPairData* data, bool objectOwner, bool dataOwner )
{
	Debug::Assert( data != NULL );
	
	SoftBodySplitPairData^ managedPairData = gcnew SoftBodySplitPairData();

	managedPairData->_data = data;
	managedPairData->ObjectOwner = objectOwner;
	managedPairData->DataOwner = dataOwner;
	
	return managedPairData;
}
SoftBodySplitPairData::~SoftBodySplitPairData()
{
	this->!SoftBodySplitPairData();
}
SoftBodySplitPairData::!SoftBodySplitPairData()
{
	if( this->IsDisposed )
		return;

	OnDisposing( this, EventArgs::Empty );

	if( this->DataOwner )
	{
		SAFE_DELETE( _data->numSplitPairsPtr );
		
		SAFE_FREE( _data->splitPairsBegin );
	}

	if( this->ObjectOwner )
	{
		SAFE_DELETE( _data );
	}

	_data = NULL;

	OnDisposed(this, EventArgs::Empty);
}

bool SoftBodySplitPairData::IsDisposed::get()
{
	return _data == NULL;
}

SoftBodySplitPairData^ SoftBodySplitPairData::Clone()
{
	NxSoftBodySplitPairData* data = new NxSoftBodySplitPairData();

	data->maxSplitPairs = _data->maxSplitPairs;

	if( _data->numSplitPairsPtr != NULL)
	{
		data->numSplitPairsPtr = new NxU32();
		*data->numSplitPairsPtr = *data->numSplitPairsPtr;
	}

	if( _data->splitPairsBegin != NULL && _data->maxSplitPairs >= 0 )
	{
		data->splitPairsBegin = (NxSoftBodySplitPair*)malloc( _data->maxSplitPairs * sizeof(NxSoftBodySplitPair) );

		int byteSize = data->maxSplitPairs * sizeof( NxSoftBodySplitPair );
		memcpy_s( data->splitPairsBegin, byteSize, _data->splitPairsBegin, byteSize );
	}

	data->splitPairsByteStride = _data->splitPairsByteStride;

	SoftBodySplitPairData^ managedPairData = gcnew SoftBodySplitPairData();
	managedPairData->_data = data;

	return managedPairData;
}
Object^ SoftBodySplitPairData::ICloneableClone()
{
	return Clone();
}

void SoftBodySplitPairData::AllocateSplitPairs( int count )
{
	if( count < 0 )
		throw gcnew ArgumentOutOfRangeException( "count" );

	if( _data->splitPairsBegin != NULL )
	{
		SAFE_FREE( _data->splitPairsBegin );
	}

	_data->splitPairsBegin = (NxSoftBodySplitPair*)malloc( count * sizeof( NxSoftBodySplitPair ) );
}

void SoftBodySplitPairData::SetToDefault()
{
	_data->setToDefault();
}
bool SoftBodySplitPairData::IsValid()
{
	return _data->isValid();
}
int SoftBodySplitPairData::CheckValid()
{
	return _data->checkValid();
}

array<SoftBodySplitPair>^ SoftBodySplitPairData::GetSplitPairs()
{
	int count = *_data->numSplitPairsPtr;
	array<SoftBodySplitPair>^ pairs = gcnew array<SoftBodySplitPair>( count );

	for (int i = 0; i < count; i++)
	{
		pairs[ i ] = (SoftBodySplitPair)_data->splitPairsBegin[ i ];
	}

	return pairs;
}

Nullable<int> SoftBodySplitPairData::MaximumSplitPairs::get()
{
	if( _data->numSplitPairsPtr == NULL )
		return Nullable<int>();

	return Nullable<int>( *_data->numSplitPairsPtr );
}
void SoftBodySplitPairData::MaximumSplitPairs::set( Nullable<int> value )
{
	if( !value.HasValue )
	{
		if( _data->numSplitPairsPtr != NULL )
		{
			SAFE_DELETE( _data->numSplitPairsPtr );
		}
	}
	else
	{
		if( _data->numSplitPairsPtr == NULL )
			_data->numSplitPairsPtr = new NxU32();

		*_data->numSplitPairsPtr = value.Value;
	}
}

NxSoftBodySplitPairData* SoftBodySplitPairData::UnmanagedPointer::get()
{
	return _data;
}