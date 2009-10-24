#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class SoftBodyConstrainCoefficients
		{
			public:
				void SetToDefault();
				bool IsValid();
			
			internal:
				NxSoftBodyConstrainCoefficients ToUnmanaged();
				static SoftBodyConstrainCoefficients FromUnmanaged( NxSoftBodyConstrainCoefficients constrainCoefficients );
				
			public:
				property float MaximumDistance;
				property float MaximumDistanceBias;
				property float CollisionSphereRadius;
				property float CollisionSphereDistance;
		};
	};
};