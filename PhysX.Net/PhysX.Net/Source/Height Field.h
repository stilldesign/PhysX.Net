#pragma once

#include "IDisposable.h"
#include "Enums.h"
#include "Height Field Sample.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class HeightFieldDescription;
		ref class Core;
		
		public ref class HeightField : IDisposable
		{
			public:
				virtual event EventHandler^ OnDisposing;
				virtual event EventHandler^ OnDisposed;
				
			private:
				NxHeightField* _heightField;
				StillDesign::PhysX::Core^ _core;
				
				String^ _name;
			
			internal:
				HeightField( NxHeightField* heightField, StillDesign::PhysX::Core^ core );
			public:
				~HeightField();
			protected:
				!HeightField();
			
			public:
				property bool IsDisposed
				{
					virtual bool get();
				}
				
			public:
				/// <summary></summary>
				HeightFieldDescription^ SaveToDescription();
				/// <summary></summary>
				bool LoadFromDescription( HeightFieldDescription^ description );
				
				/// <summary></summary>
				array<HeightFieldSample>^ SaveCells();
				
				/// <summary></summary>
				float GetHeight( float x, float z );
				
				/// <summary></summary>
				property StillDesign::PhysX::Core^ Core
				{
					StillDesign::PhysX::Core^ get();
				}
				/// <summary></summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary></summary>
				property int NumberOfRows
				{
					int get();
				}
				/// <summary></summary>
				property int NumberOfColumns
				{
					int get();
				}
				/// <summary></summary>
				property HeightFieldFormat Format
				{
					HeightFieldFormat get();
				}
				
				/// <summary></summary>
				property float Thickness
				{
					float get();
				}
				/// <summary></summary>
				property float ConvexEdgeThreshold
				{
					float get();
				}
				/// <summary></summary>
				property HeightFieldFlag Flags
				{
					HeightFieldFlag get();
				}
				
				/// <summary></summary>
				property int ReferencedCount
				{
					int get();
				}
			
			internal:
				property NxHeightField* UnmanagedPointer
				{
					NxHeightField* get();
				}
		};
	};
};