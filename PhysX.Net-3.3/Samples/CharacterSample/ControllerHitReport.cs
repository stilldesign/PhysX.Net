using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Samples.CharacterSample
{
	public class ControllerHitReport : UserControllerHitReport
	{
		public override void OnControllerHit(ControllersHit hit)
		{
			Console.WriteLine("Hit controller at " + hit.WorldPosition);
		}

		public override void OnObstacleHit(ControllerObstacleHit hit)
		{
			
		}

		public override void OnShapeHit(ControllerShapeHit hit)
		{
			
		}
	}
}