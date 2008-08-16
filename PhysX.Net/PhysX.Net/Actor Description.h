#pragma once

#include "Actor Description Base.h"
#include "Shape Description.h"

#include <NxActorDesc.h> 

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		
		public ref class ActorDescription : ActorDescriptionBase
		{
			private:
				ShapeDescription::ShapeDescriptionCollection^ _shapes;
				
			public:
				ActorDescription();
				ActorDescription( ... array<ShapeDescription^>^ shapeDescriptions );
				~ActorDescription();
			protected:
				!ActorDescription();
			private:
				void CreateActorDescription();
				
			public:
				virtual DescriptorValidity^ IsValid() override;
				
			private:
				void ShapeAdded( Object^ sender, ShapeDescription^ e );
				void ShapeRemoved( Object^ sender, ShapeDescription^ e );
			
			public:
				property ShapeDescription::ShapeDescriptionCollection^ Shapes
				{
					ShapeDescription::ShapeDescriptionCollection^ get();
				}
		};
	};
};