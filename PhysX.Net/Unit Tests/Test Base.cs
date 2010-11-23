using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
#if GRAPHICS_XNA31
using Microsoft.Xna.Framework;
#elif GRAPHICS_SLIMDX
using SlimDX;
#else
#error No Graphics Framework Defined
#endif

using StillDesign.PhysX;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
	public abstract class TestBase
	{
		public TestBase()
		{

		}

		[TestCleanup]
		public void CleanUp()
		{
			if( this.Core != null )
				this.Core.Dispose();

			this.Scene = null;
			this.Core = null;
		}

		protected Core CreateCore()
		{
			if( this.Core != null || PhysX.Core.IsCoreCreated )
				throw new Exception( "Core is still created" );

			this.Core = new Core();
			this.Core.OnDisposed += Core_OnDisposed;

			return this.Core;
		}
		protected Core CreateCoreAndScene()
		{
			CreateCore();

			this.Scene = this.Core.CreateScene();

			return this.Core;
		}

		void Core_OnDisposed( object sender, EventArgs e )
		{
			this.Core = this.Core = null;

			this.Scene = null;
		}

		protected void Update()
		{
			// Update Physics
			// Note: These 3 need to called together otherwise the unit test hosting process crashes
			this.Scene.Simulate( 1.0f / 60.0f );
			this.Scene.FlushStream();
			this.Scene.FetchResults( SimulationStatus.RigidBodyFinished, true );
		}

		protected Actor CreateBoxActor( float x, float y, float z )
		{
			return CreateBoxActor( x, y, z, "Box" );
		}
		protected Actor CreateBoxActor( float x, float y, float z, string name )
		{
			ActorDescription actorDesc = new ActorDescription()
			{
				Name = name,
				BodyDescription = new BodyDescription( 20 ),
				GlobalPose = GraphicsLibraryWrapper.CreateTranslationMatrix( new Vector3( x, y, z ) ),
				Shapes = 
				{
					new BoxShapeDescription( 5, 5, 5 )
					{
						Name = String.Format( "{0} Shape", name )
					}
				}
			};

			return this.Scene.CreateActor( actorDesc );
		}

		//

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