using System;
using System.Collections.Generic;
using System.Linq;

namespace StillDesign.PhysX.Samples
{
	public class TriggerReport : UserTriggerReport
	{
		public TriggerReport()
		{

		}

		public override void OnTrigger(Shape triggerShape, Shape otherShape, TriggerFlag status)
		{
			// A trigger occured, just report the names the actors of the shapes that contacted
			Console.WriteLine(String.Format("'{0}' and '{1}' Triggered with Type '{2}'", triggerShape.Actor.Name, otherShape.Actor.Name, status));
		}
	}
}