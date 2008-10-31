#include "StdAfx.h"

#include <NxHeightFieldSample.h> 

#include "Height Field Sample.h"

using namespace StillDesign::PhysX;

NxHeightFieldSample HeightFieldSample::ToUnmanaged( HeightFieldSample sample )
{
	NxHeightFieldSample s;
		s.height = sample.Height;
		s.materialIndex0 = sample.MaterialIndex0;
		s.materialIndex1 = sample.MaterialIndex1;
		s.tessFlag = sample.TessellationFlag;
		
	return s;
}
HeightFieldSample HeightFieldSample::FromUnmanaged( NxHeightFieldSample* sample )
{
	HeightFieldSample s;
		s.Height = sample->height;
		s.MaterialIndex0 = sample->materialIndex0;
		s.MaterialIndex1 = sample->materialIndex1;
		s.TessellationFlag = sample->tessFlag;
	
	return s;
}

//array<HeightFieldSample>^ HeightFieldSample::CreateGrid( int rows, int columns )
//{
//	array<HeightFieldSample>^ samples = gcnew array<HeightFieldSample>( rows * columns );
//	
//	for( int r = 0; r < rows; r++ )
//	{
//		for( int c = 0; c < columns; c++ )
//		{
//			samples[ columns*r + c ].
//		}
//	}
//}

short HeightFieldSample::Height::get()
{
	return _height;
}
void HeightFieldSample::Height::set( short value )
{
	_height = value;
}
Byte HeightFieldSample::MaterialIndex0::get()
{
	return _materialIndex0;
}
void HeightFieldSample::MaterialIndex0::set( Byte value )
{
	_materialIndex0 = value;
}
Byte HeightFieldSample::MaterialIndex1::get()
{
	return _materialIndex1;
}
void HeightFieldSample::MaterialIndex1::set( Byte value )
{
	_materialIndex1 = value;
}
Byte HeightFieldSample::TessellationFlag::get()
{
	return _tessFlag;
}
void HeightFieldSample::TessellationFlag::set( Byte value )
{
	_tessFlag = value;
}