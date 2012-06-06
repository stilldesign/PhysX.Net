#pragma once

//#include <PxContactModifyCallback.h> 
//
//namespace PhysX
//{
//	/// <summary>
//	/// Per-ontact point solver inputs as used by contact modification.
//	/// </summary>
//	public value class ContactPointAux
//	{
//		internal:
//			static PxContactPointAux ToUnmanaged(ContactPointAux aux);
//			static ContactPointAux ToManaged(PxContactPointAux aux);
//
//		public:
//			/// <summary>
//			/// The desired target velocity at the contact point in the direction of the contact normal. For resting contact, this is zero, or positive to make the objects pop apart.
//			/// </summary>
//			property Vector3 TargetVelocity;
//
//			/// <summary>
//			/// The maximum impulse the solver is permitted to apply at the contact point in order to try to meet the targetVelocity requirement. If max impulse is zero, the solver is not able to apply any impulse at the contact, and as a result the contact will be ignored.
//			/// </summary>
//			property float MaxImpulse;
//	};
//};