using System;
using System.Collections.Generic;
using System.Linq;

namespace StillDesign.PhysX.Samples
{
	public class Notify : UserNotify
	{
		public Notify( MainSample demo )
		{

		}

		public override bool OnSleep( Actor[] actors )
		{
			foreach( Actor actor in actors )
			{
				Console.WriteLine( "Actor '{0}' Went to Sleep at {1}", actor.Name == null ? String.Empty : actor.Name, DateTime.Now.ToShortTimeString() );
			}

			return true;
		}

		public override bool OnJointBreak( float breakingForce, Joint brokenJoint )
		{
			return true;
		}

		public override bool OnWake( Actor[] actors )
		{
			return true;
		}
	}
}