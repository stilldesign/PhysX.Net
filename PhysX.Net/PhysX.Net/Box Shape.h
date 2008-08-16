#pragma once

#include "Base Shape.h"

UsingFrameworkNamespace

namespace StillDesign
{
	namespace PhysX
	{
		ref class BoxShape;
		value class Box;
		ref class BoxShapeDescription;
		
		public ref class BoxShape : Shape
		{
			internal:
				BoxShape( NxBoxShape* boxShape );
				
			public:
				BoxShapeDescription^ SaveToDescription();
				
				Box GetWorldSpaceOBB();
				
				/// <summary>Gets or Sets the Size of the Box Shape</summary>
				property Vector3 Size
				{
					Vector3 get();
					void set( Vector3 value );
				}
			
			internal:
				property NxBoxShape* UnmanagedPointer
				{
					NxBoxShape* get() new;
				}
		};
		
		/*public ref class BoxShapesManager : BaseListNotifiableRetrieveOnly< BoxShape^ >
		{
			
		};*/
	};
};