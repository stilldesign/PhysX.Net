using System;
using System.Collections.Generic;
using System.Linq;

namespace StillDesign.PhysX.Samples
{
	public class ControllerHitReport : UserControllerHitReport
	{
		public override ControllerAction OnControllerHit(ControllersHit hit)
		{
			return ControllerAction.None;
		}

		public override ControllerAction OnShapeHit(ControllerShapeHit hit)
		{
			return ControllerAction.None;
		}
	}
}