#pragma once

#include "Enums.h"
#include "User Entity Report.h"
#include "Triangle.h"
#include "Base Shape.h"

using namespace System;

namespace StillDesign
{
	namespace PhysX
	{
		ref class HeightField;
		ref class HeightFieldShapeDescription;
		value class Bounds3;
		
		public ref class HeightFieldShape : Shape
		{
			public:
				ref class GetTriangleResult;
			
			private:
				HeightField^ _heightField;
				
			internal:
				HeightFieldShape( NxHeightFieldShape* heightFieldShape );
							
			public:
				HeightFieldShapeDescription^ SaveToDescription();
				
				GetTriangleResult^ GetTriangle( int triangleIndex );
				GetTriangleResult^ GetTriangle( int triangleIndex, bool worldSpaceTranslation, bool worldSpaceRotation );
				
				array<int>^ GetOverlapAABBTriangles( Bounds3 bounds, QueryFlag flags );
				//bool GetOverlapAABBTriangles( Bounds3 bounds, QueryFlags flags, UserEntityReport<int>^ callback );
				bool IsShapePointOnHeightField( float x, float z );
				bool GetMaterialAtShapePoint( float x, float z );
				Vector3 GetNormalAtShapePoint( float x, float z );
				Vector3 GetSmoothedNormalAtShapePoint( float x, float z );
				
				property StillDesign::PhysX::HeightField^ HeightField
				{
					StillDesign::PhysX::HeightField^ get();
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
			
			internal:
				property NxHeightFieldShape* UnmanagedPointer
				{
					NxHeightFieldShape* get() new;
				}
				
			public:
				ref class GetTriangleResult
				{
					private:
						Triangle _worldTriangle;
						Triangle _edgeTriangle;
						TriangleFlag _flags;
						
					public:
						property Triangle WorldTriangle
						{
							Triangle get();
							void set( Triangle value );
						}
						property Triangle EdgeTriangle
						{
							Triangle get();
							void set( Triangle value );
						}
						property TriangleFlag Flags
						{
							TriangleFlag get();
							void set( TriangleFlag value );
						}
				};
		};
	};
};