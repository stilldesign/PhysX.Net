#pragma once

#include "Actor Description Base.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		ref class ShapeDescription;
		generic< class T> ref class ListBase;
		
		public ref class ActorDescription : ActorDescriptionBase
		{
			private:
				ListBase<ShapeDescription^>^ _shapes;
				
			public:
				ActorDescription();
				ActorDescription( ... array<ShapeDescription^>^ shapeDescriptions );
				~ActorDescription();
			protected:
				!ActorDescription();
			private:
				void CreateActorDescription();
				
			public:
				/// <summary>Is the ActorDescription valid. (Step into to diagnose)</summary>
				virtual bool IsValid() override;
				
			private:
				void ShapeAdded( Object^ sender, ShapeDescription^ e );
				void ShapeRemoved( Object^ sender, ShapeDescription^ e );
			
			public:
				/// <summary>Gets a collection of shape descriptions</summary>
				property ListBase<ShapeDescription^>^ Shapes
				{
					ListBase< ShapeDescription^ >^ get();
				}
		};
	};
};