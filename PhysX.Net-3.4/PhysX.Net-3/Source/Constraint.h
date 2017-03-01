#pragma once

#include "ConstraintEnum.h"

namespace PhysX
{
	ref class Scene;
	ref class RigidActor;
	ref class Physics;
	ref class Serializable;

	public ref class Constraint : IDisposable
	{
	public:
		virtual event EventHandler^ OnDisposing;
		virtual event EventHandler^ OnDisposed;

	private:
		PxConstraint* _constraint;
		// Does this class own the unmanaged PxConstraint? If true, it is free to dispose of it, otherwise it should not dispose
		// of it and it will be disposed of by whoever created it initially (usually the parent PxJoint object).
		bool _unmanagedOwner;

	internal:
		Constraint(PxConstraint* constraint, IDisposable^ owner, bool unmanagedOwner);
	public:
		~Constraint();
	protected:
		!Constraint();

	public:
		property bool Disposed
		{
			virtual bool get();
		}

		void SetActors(PhysX::RigidActor^ actor0, PhysX::RigidActor^ actor1);

		void MarkDirty();

		void SetBreakForce(float linear, float angular);

		/// <summary>
		/// Gets an object which is responsible for serialization of this type.
		/// </summary>
		Serializable^ AsSerializable();

		//

		property PhysX::Scene^ Scene
		{
			PhysX::Scene^ get();
		}

		property PhysX::RigidActor^ Actor0
		{
			PhysX::RigidActor^ get();
			void set(PhysX::RigidActor^ value);
		}
		property PhysX::RigidActor^ Actor1
		{
			PhysX::RigidActor^ get();
			void set(PhysX::RigidActor^ value);
		}

		property ConstraintFlag Flags
		{
			ConstraintFlag get();
			void set(ConstraintFlag value);
		}

		property Vector3 LinearForce
		{
			Vector3 get();
		}
		property Vector3 AngularForce
		{
			Vector3 get();
		}

		property float LinearBreakForce
		{
			float get();
			void set(float value);
		}
		property float AngularBreakForce
		{
			float get();
			void set(float value);
		}

		//void *  getExternalReference (PxU32 &typeID)=0 
 
		//virtual void  setConstraintFunctions (PxConstraintConnector &connector, const PxConstraintShaderTable &shaders)=0 
	};
};