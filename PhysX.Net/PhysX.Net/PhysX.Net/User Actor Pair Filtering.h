#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		ref class Scene;
		class InternalUserActorPairFiltering;
		ref class ActorPairFiltering;
		ref class Actor;
		
		public ref class UserActorPairFiltering abstract
		{
			private:
				InternalUserActorPairFiltering* _internalUserActorPairFiltering;
				
			protected:
				UserActorPairFiltering();
			public:
				~UserActorPairFiltering();
			protected:
				!UserActorPairFiltering();
			
			public:
				virtual void OnActorPairs( array<ActorPairFiltering^>^ filterArray ) abstract;
				
			internal:
				property InternalUserActorPairFiltering* UnmanagedPointer
				{
					InternalUserActorPairFiltering* get();
				}
		};
		
		class InternalUserActorPairFiltering : public NxUserActorPairFiltering
		{
			private:
				gcroot<UserActorPairFiltering^> _userActorPairFiltering;
			
			public:
				InternalUserActorPairFiltering( gcroot<UserActorPairFiltering^> userActorPairFiltering );
				
				virtual void onActorPairs( NxActorPairFilter *filterArray, NxU32 arraySize );
		};
		
		public ref class ActorPairFiltering
		{
			private:
				Actor^ _actorA;
				Actor^ _actorB;
				bool _filtered;
			
			public:
				ActorPairFiltering( Actor^ actorA, Actor^ actorB, bool filtered );
				
				property Actor^ ActorA
				{
					Actor^ get();
				}
				property Actor^ ActorB
				{
					Actor^ get();
				}
				property bool Filtered
				{
					bool get();
					void set( bool value );
				}
		};
	};
};