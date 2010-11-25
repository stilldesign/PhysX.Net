using System;
using System.Collections.Generic;
using System.Linq;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using StillDesign.PhysX;
using StillDesign.PhysX.MathPrimitives;

namespace StillDesign.PhysX.UnitTests
{
	[TestClass]
#if x86
	[DeploymentItem( @"Assemblies\x86\cudart32_30_9.dll" )]
	[DeploymentItem( @"Assemblies\x86\NxCharacter.dll" )]
	[DeploymentItem( @"Assemblies\x86\PhysXCooking.dll" )]
	[DeploymentItem( @"Assemblies\x86\PhysXCore.dll" )]
	[DeploymentItem( @"Assemblies\x86\PhysXDevice.dll" )]
	[DeploymentItem( @"Assemblies\x86\PhysXLoader.dll" )]
#elif x64
	[DeploymentItem( @"Assemblies\x64\cudart32_30_9.dll" )]
	[DeploymentItem( @"Assemblies\x64\NxCharacter.dll" )]
	[DeploymentItem( @"Assemblies\x64\PhysXCooking.dll" )]
	[DeploymentItem( @"Assemblies\x64\PhysXCore.dll" )]
	[DeploymentItem( @"Assemblies\x64\PhysXDevice.dll" )]
	[DeploymentItem( @"Assemblies\x64\PhysXLoader.dll" )]
#endif
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
				GlobalPose = Matrix.Translation( new Vector3( x, y, z ) ),
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