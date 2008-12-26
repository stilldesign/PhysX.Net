using System;
using System.Collections.Generic;
using System.Linq;

using Microsoft.Xna.Framework;

using StillDesign.PhysX;

namespace StillDesign.PhysX.UnitTests
{
	public abstract class TestBase
	{
		public TestBase()
		{

		}

		protected void CreateCoreAndScene()
		{
			this.Core = new Core();

			this.Scene = this.Core.CreateScene();
		}

		protected Actor CreateBoxActor( Vector3 position )
		{
			ActorDescription actorDesc = new ActorDescription()
			{
				BodyDescription = new BodyDescription( 20 ),
				GlobalPose = Matrix.CreateTranslation( position ),
				Shapes = { new BoxShapeDescription( 5, 5, 5 ) }
			};

			return this.Scene.CreateActor( actorDesc );
		}

		protected Core Core
		{
			get;
			private set;
		}
		protected Scene Scene
		{
			get;
			private set;
		}
	}
}