#pragma once

#include "Force Field Shape Group.h"
#include "Description.h"

class NxForceFieldShapeGroupDesc;

namespace StillDesign
{
	namespace PhysX
	{
		public ref class ForceFieldShapeGroupDescription : Description
		{
			public:
				ref class ForceFieldShapeDescriptionCollection : ListBase<ForceFieldShapeDescription^>
				{
					
				};
			
			private:
				NxForceFieldShapeGroupDesc* _desc;
				
				ForceFieldShapeDescriptionCollection^ _shapes;
				
				Object^ _userData;
				
			public:
				ForceFieldShapeGroupDescription();
			internal:
				ForceFieldShapeGroupDescription( NxForceFieldShapeGroupDesc* desc );
			public:
				~ForceFieldShapeGroupDescription();
			protected:
				!ForceFieldShapeGroupDescription();
			
			public:
				void SetToDefault();
				/// <summary>Returns 0 if the current settings are valid.</summary>
				virtual int CheckValid() override;
				bool IsValid();
				
				/// <summary></summary>
				property ForceFieldShapeDescriptionCollection^ Shapes
				{
					ForceFieldShapeDescriptionCollection^ get();
				}
				
				property String^ Name
				{
					String^ get();
					void set( String^ value );
				}
				
				/// <summary></summary>
				property ForceFieldShapeGroupFlag Flags
				{
					ForceFieldShapeGroupFlag get();
					void set( ForceFieldShapeGroupFlag value );
				}
				
				property Object^ UserData
				{
					Object^ get();
					void set( Object^ value );
				}
				
			internal:
				property NxForceFieldShapeGroupDesc* UnmanagedPointer
				{
					NxForceFieldShapeGroupDesc* get();
				}
		};	
	};
};