#pragma once

#include "Joint.h"
#include "JointEnum.h"

namespace PhysX
{
	/// <summary>
	/// 
	/// </summary>
	public ref class DistanceJoint : Joint
	{
		internal:
			DistanceJoint(PxDistanceJoint* joint, PhysX::Physics^ owner);

		public:
			
			//

			/// <summary>
			/// Gets or sets the allowed minimum distance for the joint.
			/// </summary>
			property float MinimumDistance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the allowed maximum distance for the joint.
			/// </summary>
			property float MaximumDistance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the error tolerance of the joint.
			/// </summary>
			property float Tolerance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the strength of the joint spring.
			/// </summary>
			property float Stiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the damping of the joint spring.
			/// </summary>
			property float Damping
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the damping of the joint spring.
			/// </summary>
			property DistanceJointFlag Flags
			{
				DistanceJointFlag get();
				void set(DistanceJointFlag value);
			}

		internal:
			property PxDistanceJoint* UnmanagedPointer
			{
				virtual PxDistanceJoint* get() new;
			}
	};
};