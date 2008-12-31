using System;
using System.Collections.Generic;
using System.Linq;

#if GRAPHICS_XNA2 || GRAPHICS_XNA3
using Microsoft.Xna.Framework;
#elif GRAPHICS_MDX
using Microsoft.DirectX;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

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
				GlobalPose = GraphicsLibraryWrapper.CreateTranslationMatrix( position ),
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