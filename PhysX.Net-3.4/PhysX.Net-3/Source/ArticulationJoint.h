#pragma once


namespace PhysX
{
	ref class Scene;
	ref class Serializable;

	/// <summary>
	/// 
	/// </summary>
	public ref class ArticulationJoint : IDisposable
	{
		public:
			virtual event EventHandler^ OnDisposing;
			virtual event EventHandler^ OnDisposed;

		private:
			PxArticulationJoint* _joint;
			PhysX::Scene^ _scene;

		internal:
			ArticulationJoint(PxArticulationJoint* joint, PhysX::Scene^ owner);
		public:
			~ArticulationJoint();
		protected:
			!ArticulationJoint();

		public:
			property bool Disposed
			{
				virtual bool get();
			}

			/// <summary>
			/// Gets an object which is responsible for serialization of this type.
			/// </summary>
			Serializable^ AsSerializable();

			//

			/// <summary>
			/// Gets the scene.
			/// </summary>
			property PhysX::Scene^ Scene
			{
				PhysX::Scene^ get();
			}

			/// <summary>
			/// Gets or sets the joint pose in the parent frame.
			/// </summary>
			property Matrix ParentPose
			{
				Matrix get();
				void set(Matrix value);
			}

			/// <summary>
			/// Gets or sets the joint pose in the child frame.
			/// </summary>
			property Matrix ChildPose
			{
				Matrix get();
				void set(Matrix value);
			}

			/// <summary>
			/// Gets or sets the target drive position.
			/// </summary>
			property Quaternion TargetOrientation
			{
				Quaternion get();
				void set(Quaternion value);
			}

			/// <summary>
			/// Gets or sets the target drive velocity.
			/// </summary>
			property Vector3 TargetVelocity
			{
				Vector3 get();
				void set(Vector3 value);
			}

			/// <summary>
			/// Gets or sets the drive strength of the joint acceleration spring.
			/// </summary>
			property float TangentialStiffness
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the damping of the joint acceleration spring.
			/// </summary>
			property float Damping
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the internal compliance.
			/// </summary>
			property float InternalCompliance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the external compliance.
			/// </summary>
			property float ExternalCompliance
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the extents for the swing limit cone.
			/// </summary>
			property float SwingLimitY
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets the extents for the swing limit cone.
			/// </summary>
			property float SwingLimitZ
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the flag which enables the swing limit.
			/// </summary>
			property bool SwingLimitEnabled
			{
				bool get();
				void set(bool value);
			}

			/// <summary>
			/// Gets or sets the bounds of the twist limit.
			/// </summary>
			property float TwistLimitLower
			{
				float get();
				void set(float value);
			}
			/// <summary>
			/// Gets or sets the bounds of the twist limit.
			/// </summary>
			property float TwistLimitUpper
			{
				float get();
				void set(float value);
			}

			/// <summary>
			/// Gets or sets the flag which enables the swing limit.
			/// </summary>
			property bool TwistLimitEnabled
			{
				bool get();
				void set(bool value);
			}

		internal:
			property PxArticulationJoint* UnmanagedPointer
			{
				PxArticulationJoint* get();
			}
	};
};