#pragma once

#include "Force Field Shape.h"

class NxForceFieldShapeDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ForceFieldShapeDescription abstract
		{
			protected:
				NxForceFieldShapeDesc* _forceFieldShapeDesc;
				
			private:
				Object^ _userData;
			
			protected:
				ForceFieldShapeDescription( NxForceFieldShapeDesc* forceFieldShapeDesc );
			public:
				~ForceFieldShapeDescription();
			protected:
				!ForceFieldShapeDescription();
			
			public:
				/// <summary></summary>
				void SetToDefault();
				/// <summary></summary>
				bool IsValid();
				
				/// <summary></summary>
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				/// <summary></summary>
				property ShapeType Type
				{
					ShapeType get();
				}
				
				/// <summary></summary>
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
			
			internal:
				property NxForceFieldShapeDesc* UnmanagedPointer
				{
					NxForceFieldShapeDesc* get();
				}
		};
	};
};