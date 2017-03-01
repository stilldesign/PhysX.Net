#pragma once

namespace PhysX
{
	public ref class ConvexMeshMassInformation
	{
		public:
			property float Mass;
			property Matrix LocalInertia;
			property Vector3 LocalCenterOfMass;
	};
};