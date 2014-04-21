#pragma once

namespace StillDesign
{
	namespace PhysX
	{
		public value class ActorGroupPair
		{
			internal:
				static explicit operator ActorGroupPair( NxActorGroupPair actorGroupPair );
				static explicit operator NxActorGroupPair( ActorGroupPair actorGroupPair );
				
			public:
				property short Group0;
				property short Group1;
				property int Flags;
		};
	};
};