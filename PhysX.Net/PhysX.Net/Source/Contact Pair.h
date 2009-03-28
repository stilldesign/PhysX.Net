#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Actor;
		
		public ref class ContactPair
		{
			private:
				Actor^ _actorA;
				Actor^ _actorB;
				
				Vector3 _normalForce;
				Vector3 _frictionForce;
				
				bool _actorADeleted, _actorBDeleted;
			
			internal:
				ContactPair();
			public:
				ContactPair( Actor^ actorA, Actor^ actorB, Vector3 normalForce, Vector3 frictionForce, bool actorADeleted, bool actorBDeleted );
				
			internal:
				static ContactPair^ FromUnmanagedPointer( NxContactPair* contactPair );
				
			public:
				/// <summary>Gets the the First Actor in the Contact</summary>
				property Actor^ ActorA
				{
					Actor^ get();
				}
				/// <summary>Gets the the Second Actor in the Contact</summary>
				property Actor^ ActorB
				{
					Actor^ get();
				}
				
				/// <summary>Gets the Total Contact Normal Force that was Applied for this Pair, to Maintain Nonpenetration Constraints</summary>
				property Vector3 NormalForce
				{
					Vector3 get();
				}
				/// <summary>Gets th Total Tangential Force that was Applied for this Pair</summary>
				property Vector3 FrictionForce
				{
					Vector3 get();
				}
				
				property bool IsActorADeleted
				{
					bool get();
				}
				property bool IsActorBDeleted
				{
					bool get();
				}
		};
	};
};