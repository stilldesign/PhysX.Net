#pragma once

#include "Actor.h"

using namespace System;
UsingFrameworkNamespace

using namespace StillDesign::PhysX;

class NxContactReport;

namespace StillDesign
{
	namespace PhysX
	{
		ref class ContactPair;
		class InternalUserContactReport;
		
		public ref class UserContactReport abstract
		{
			private:
				InternalUserContactReport* _contactReport;
				
				StillDesign::PhysX::Scene^ _scene;
				
			protected:
				UserContactReport();
			public:
				~UserContactReport();
			protected:
				!UserContactReport();
				
			public:
				virtual void OnContactNotify( ContactPair^ contactInformation, ContactPairFlag events ) abstract;
				
			internal:
				property InternalUserContactReport* UnmanagedPointer
				{
					InternalUserContactReport* get();
				}
		};
		
		public ref class ContactPair
		{
			private:
				Actor^ _actorA;
				Actor^ _actorB;
				
				Vector3 _normalForce;
				Vector3 _frictionForce;
				
				bool _actorADeleted, _actorBDeleted;
			
			public:
				ContactPair( Actor^ actorA, Actor^ actorB, Vector3 normalForce, Vector3 frictionForce, bool actorADeleted, bool actorBDeleted );
			internal:
				ContactPair( NxContactPair* contactPair );
				
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
		
		class InternalUserContactReport : public NxUserContactReport
		{
			private:
				gcroot< StillDesign::PhysX::UserContactReport^ > _userContactReport;

			public:
				InternalUserContactReport( UserContactReport^ userContactReport );
				
				virtual void onContactNotify( NxContactPair& pair, NxU32 events );
		};
	};
};