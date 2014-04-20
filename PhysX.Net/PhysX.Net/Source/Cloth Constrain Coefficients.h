#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class ClothConstrainCoefficients
		{
			public:
				void SetToDefault();
				bool IsValid();
			
			internal:
				NxClothConstrainCoefficients ToUnmanaged();
				static ClothConstrainCoefficients FromUnmanaged( NxClothConstrainCoefficients constrainCoefficients );
				
			public:
				property float MaximumDistance;
				property float MaximumDistanceBias;
				property float CollisionSphereRadius;
				property float CollisionSphereDistance;
		};
	};
};