#pragma once

#include "Enums.h"
#include "Shape Description.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class HeightField;
		
		public ref class HeightFieldShapeDescription : ShapeDescription
		{
			private:
				HeightField^ _heightField;
				
			public:
				HeightFieldShapeDescription();
				
				property StillDesign::PhysX::HeightField^ HeightField
				{
					StillDesign::PhysX::HeightField^ get();
					void set( StillDesign::PhysX::HeightField^ value );
				}
				property float HeightScale
				{
					float get();
					void set( float value );
				}
				property float RowScale
				{
					float get();
					void set( float value );
				}
				property float ColumnScale
				{
					float get();
					void set( float value );
				}
				property short MaterialIndexHighBits
				{
					short get();
					void set( short value );
				}
				property short HoleMaterial
				{
					short get();
					void set( short value );
				}
				property MeshShapeFlag Flags
				{
					MeshShapeFlag get();
					void set( MeshShapeFlag value );
				}
				
			internal:
				property NxHeightFieldShapeDesc* UnmanagedPointer
				{
					NxHeightFieldShapeDesc* get() new;
				}
		};
	};
};