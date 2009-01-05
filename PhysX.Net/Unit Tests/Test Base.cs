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
		private static Core _core;

		public TestBase()
		{

		}

		protected void CleanUp()
		{
			if( this.Core != null )
				this.Core.Dispose();

			this.Scene = null;
			this.Core = null;
		}

		protected Core CreateCoreAndScene()
		{
			//if( _core != null )
			//    CleanUp();

			if( _core != null || PhysX.Core.IsCoreCreated == true )
				throw new Exception( "Core is still created" );

			_core = this.Core = new Core();
			this.Core.OnDisposed += new EventHandler( Core_OnDisposed );

			this.Scene = this.Core.CreateScene();

			return this.Core;
		}

		void Core_OnDisposed( object sender, EventArgs e )
		{
			_core = this.Core = null;
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
			ActorDescription actorDesc = new ActorDescription()
			{
				BodyDescription = new BodyDescription( 20 ),
				GlobalPose = GraphicsLibraryWrapper.CreateTranslationMatrix( new Vector3( x, y, z ) ),
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