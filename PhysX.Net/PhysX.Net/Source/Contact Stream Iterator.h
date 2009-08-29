#pragma once

#include "Enums.h"

namespace StillDesign
{
	namespace PhysX
	{
		ref class ConstantContactStream;
		ref class Shape;
		
		public ref class ContactStreamIterator
		{
			private:
				NxContactStreamIterator* _iter;
			
			public:
				ContactStreamIterator( ConstantContactStream^ contactStream );
			protected:
				~ContactStreamIterator();
			public:
				!ContactStreamIterator();
				property bool IsDisposed
				{
					bool get();
				}
				
				/// <summary>Goes on to the next pair, silently skipping invalid pairs.</summary>
				bool GoToNextPair();
				/// <summary>Goes on to the next patch (contacts with the same normal).</summary>
				bool GoToNextPatch();
				/// <summary>Goes on to the next contact point.</summary>
				bool GoToNextPoint();
				
				/// <summary>Returns the number of pairs in the structure.</summary>
				int GetNumberOfPairs();
				
				Shape^ GetShapeA();
				Shape^ GetShapeB();
			private:
				/// <summary>Retrieves the shapes for the current pair.</summary>
				Shape^ GetShape( int shapeIndex );
				
			public:
				bool IsDeletedShapeA();
				bool IsDeletedShapeB();
			private:
				/// <summary>Specifies for each shape of the pair if it has been deleted.</summary>
				bool IsDeletedShape( int shapeIndex );
				
			public:
				/// <summary>Retrieves the shape flags for the current pair.</summary>
				ShapeFlag GetShapeFlags();
				
				/// <summary>Retrieves the number of patches for the current pair.</summary>
				int GetNumberOfPatches();
				
				/// <summary>Retrieves the number of remaining patches.</summary>
				int GetNumberOfPatchesRemaining();
				
				/// <summary>Retrieves the patch normal.</summary>
				Vector3 GetPatchNormal();
				
				/// <summary>Retrieves the number of points in the current patch.</summary>
				int GetNumberOfPoints();
				
				/// <summary>Retrieves the number of points remaining in the current patch.</summary>
				int GetNumberOfPointsRemaining();
				
				/// <summary>Returns the contact point position.</summary>
				Vector3 GetPoint();
				
				/// <summary>Return the separation for the contact point.</summary>
				float GetSeperation();
				
				/// <summary>Retrieves the feature index.</summary>
				int GetFeatureIndex0();
				/// <summary>Retrieves the feature index.</summary>
				int GetFeatureIndex1();
				
				/// <summary>Retrieves the point normal force.</summary>
				float GetPointNormalForce();
		};
	};
};