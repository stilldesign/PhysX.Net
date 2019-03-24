#pragma once


namespace PhysX
{
	/// <summary>
	/// Describes the parameters for a joint limit.
	/// Limits are enabled or disabled by setting flags or other configuration parameters joints, see the
	/// documentation for specific joint types for details.
	/// </summary>
	public ref class JointLimitParameters
	{
	private:
		PxJointLimitParameters* _parameters;

	protected:
		JointLimitParameters(PxJointLimitParameters* parameters);
	public:
		~JointLimitParameters();
	protected:
		!JointLimitParameters();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		virtual bool IsValid();
		bool IsSoft();

		/// <summary>
		/// Controls the amount of bounce when the joint hits a limit.
		/// </summary>
		property float Restitution
		{
			float get();
			void set(float value);
		}

		property float BounceThreshold
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// If greater than zero, the limit is soft, i.e. a spring pulls the joint back to the limit.
		/// </summary>
		property float Stiffness
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// If spring is greater than zero, this is the damping of the limit spring.
		/// </summary>
		property float Damping
		{
			float get();
			void set(float value);
		}

		/// <summary>
		/// The distance inside the limit value at which the limit will be considered to be active by the solver.
		/// </summary>
		property float ContactDistance
		{
			float get();
			void set(float value);
		}

		//

		property PxJointLimitParameters* UnmanagedPointer
		{
			PxJointLimitParameters* get();
		}
	};
};