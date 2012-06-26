using System;
using System.Collections.Generic;
using System.Linq;

namespace PhysX.Samples
{
	public class MainSample : Sample
	{
		public MainSample()
		{
			Run();
		}

		protected override void LoadContent()
		{
			
		}

		protected override void LoadPhysics(Scene scene)
		{
			RigidActorsSample.StackOfBoxes(scene);
		}

		protected override void Update(TimeSpan elapsed)
		{
			
		}

		protected override void Draw()
		{
			
		}
	}
}