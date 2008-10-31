#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class ActorGroupPair
		{
			private:
				short _group0, _group1;
				unsigned int _flags;
				
			internal:
				static explicit operator ActorGroupPair( NxActorGroupPair actorGroupPair );
				static explicit operator NxActorGroupPair( ActorGroupPair actorGroupPair );
				
			public:
				property short Group0
				{
					short get();
					void set( short value );
				}
				property short Group1
				{
					short get();
					void set( short value );
				}
				property int Flags
				{
					int get();
					void set( int value );
				}
		};
	};
};