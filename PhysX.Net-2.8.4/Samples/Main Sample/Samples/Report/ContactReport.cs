using System;
using System.Collections.Generic;
using System.Linq;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.Samples
{
	public class ContactReport : UserContactReport
	{
		private Actor _contactReportActor;
		private List<ContactReportPair> _contactPairs;

		public ContactReport(Actor contactReportActor, Actor groundActor)
		{
			_contactReportActor = contactReportActor;

			// Associate the pairs with a function
			_contactPairs = new List<ContactReportPair>()
			{
				{ new ContactReportPair( contactReportActor, groundActor, CapsuleAndGroundPlaneContact ) }
			};
		}

		// PhysX calls OnContactNotify is the base class which you then provide the implementation for
		public override void OnContactNotify(ContactPair contactInformation, ContactPairFlag events)
		{
			Actor a = contactInformation.ActorA;
			Actor b = contactInformation.ActorB;

			// This shouldn't be O(n)
			foreach (ContactReportPair pair in _contactPairs)
			{
				if ((pair.ActorA == a || pair.ActorA == b) && (pair.ActorB == a || pair.ActorB == b))
				{
					pair.Callback(a, b, events);
				}
			}
		}

		private void CapsuleAndGroundPlaneContact(Actor a, Actor b, ContactPairFlag events)
		{
			// The capsule hit the ground, add some bounce
			// Can be done with materials, but this just an example to demonstrate contact report
			_contactReportActor.AddForce(new Vector3(0, 5000, 0), ForceMode.Force);
		}
	}
}