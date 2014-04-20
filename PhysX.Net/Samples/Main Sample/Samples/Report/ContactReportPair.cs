using System;
using System.Collections.Generic;
using System.Linq;

namespace StillDesign.PhysX.Samples
{
	public class ContactReportPair
	{
		public ContactReportPair(Actor a, Actor b, ContactCallback callback)
		{
			this.ActorA = a;
			this.ActorB = b;
			this.Callback = callback;
		}

		public Actor ActorA { get; private set; }
		public Actor ActorB { get; private set; }
		public ContactCallback Callback { get; private set; }
	}
}